#include "crabdetector.h"

#include <QDebug>
#include <QFile>

#include <algorithm>
#include <cstring>
#include <vector>

// ─────────────────────────────────────────────────────────────────────────────
// Construction
// ─────────────────────────────────────────────────────────────────────────────

CrabDetector::CrabDetector() : m_env(ORT_LOGGING_LEVEL_WARNING, "CrabDetector")
{
    m_sessionOptions.SetIntraOpNumThreads(1);
    m_sessionOptions.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);
}

// ─────────────────────────────────────────────────────────────────────────────
// Load Model
// ─────────────────────────────────────────────────────────────────────────────

bool CrabDetector::loadModel(const QString &modelPath)
{
    m_loaded = false;

    QByteArray modelBytes;
    if (modelPath.startsWith(":/"))
    {
        QFile f(modelPath);
        if (!f.open(QIODevice::ReadOnly))
        {
            qWarning() << "CrabDetector: cannot open resource" << modelPath;
            return false;
        }
        modelBytes = f.readAll();
    }

    try
    {
        if (!modelBytes.isEmpty())
        {
            m_session = Ort::Session(
                m_env,
                reinterpret_cast<const void *>(modelBytes.constData()),
                static_cast<size_t>(modelBytes.size()),
                m_sessionOptions);
        }
        else
        {

#ifdef _WIN32
            m_session = Ort::Session(
                m_env,
                modelPath.toStdWString().c_str(),
                m_sessionOptions);
#else
            m_session = Ort::Session(
                m_env,
                modelPath.toUtf8().constData(),
                m_sessionOptions);
#endif
        }

        m_loaded = true;
        qDebug() << "CrabDetector: model loaded from" << modelPath;
        return true;
    }
    catch (const Ort::Exception &e)
    {
        qWarning() << "CrabDetector: ONNX Runtime error:" << e.what();
        return false;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Public inference entry-point
// ─────────────────────────────────────────────────────────────────────────────

QVector<CrabDetector::Detection> CrabDetector::detect(const QImage &image)
{
    if (!m_loaded || image.isNull())
        return {};

    QImage bgr = image.convertToFormat(QImage::Format_BGR888);
    cv::Mat src(bgr.height(), bgr.width(), CV_8UC3,
                const_cast<uchar *>(bgr.bits()),
                static_cast<size_t>(bgr.bytesPerLine()));


    float scaleX, scaleY;
    int   padLeft, padTop;
    cv::Mat blob = preprocess(src, scaleX, scaleY, padLeft, padTop);

    std::array<int64_t, 4> inputShape{
                                      1, 3,
                                      static_cast<int64_t>(m_inputHeight),
                                      static_cast<int64_t>(m_inputWidth)};


    auto memInfo = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);

    Ort::Value inputTensor = Ort::Value::CreateTensor<float>(
        memInfo,
        reinterpret_cast<float *>(blob.data),
        static_cast<size_t>(m_inputHeight * m_inputWidth * 3),
        inputShape.data(),
        inputShape.size());


    Ort::AllocatorWithDefaultOptions allocator;

    auto inputNamePtr  = m_session.GetInputNameAllocated(0, allocator);
    auto outputNamePtr = m_session.GetOutputNameAllocated(0, allocator);
    const char *inputNames[]  = { inputNamePtr.get() };
    const char *outputNames[] = { outputNamePtr.get() };

    std::vector<Ort::Value> outputTensors;
    try
    {
        outputTensors = m_session.Run(
            Ort::RunOptions{ nullptr },
            inputNames, &inputTensor, 1,
            outputNames, 1);
    }
    catch (const Ort::Exception &e)
    {
        qWarning() << "CrabDetector: inference error:" << e.what();
        return {};
    }


    auto &outTensor = outputTensors[0];
    auto  outShape = outTensor.GetTensorTypeAndShapeInfo().GetShape();

    // YOLOv8 output
    int64_t numAnchors = outShape[2];

    const float *data = outTensor.GetTensorData<float>();
    return postprocess(data, numAnchors,
                       scaleX, scaleY,
                       padLeft, padTop,
                       src.cols, src.rows);
}

// ─────────────────────────────────────────────────────────────────────────────
// Pre-processing
// ─────────────────────────────────────────────────────────────────────────────

cv::Mat CrabDetector::preprocess(const cv::Mat &src,
                                 float &scaleX, float &scaleY,
                                 int &padLeft,  int &padTop) const
{
    float sw = static_cast<float>(m_inputWidth) / static_cast<float>(src.cols);
    float sh = static_cast<float>(m_inputHeight) / static_cast<float>(src.rows);
    float scale = std::min(sw, sh);

    scaleX = scale;
    scaleY = scale;

    int newW = static_cast<int>(std::round(src.cols * scale));
    int newH = static_cast<int>(std::round(src.rows * scale));

    padLeft = (m_inputWidth  - newW) / 2;
    padTop  = (m_inputHeight - newH) / 2;


    cv::Mat resized;
    cv::resize(src, resized, { newW, newH }, 0, 0, cv::INTER_LINEAR);

    cv::Mat letterboxed(m_inputHeight, m_inputWidth, CV_8UC3, cv::Scalar(114, 114, 114));
    resized.copyTo(letterboxed(cv::Rect(padLeft, padTop, newW, newH)));

    cv::Mat rgb;
    cv::cvtColor(letterboxed, rgb, cv::COLOR_BGR2RGB);

    cv::Mat floatImg;
    rgb.convertTo(floatImg, CV_32FC3, 1.0 / 255.0);

    std::vector<cv::Mat> channels(3);
    cv::split(floatImg, channels);

    cv::Mat blob(1, 3 * m_inputHeight * m_inputWidth, CV_32F);
    int planeSize = m_inputHeight * m_inputWidth;
    for (int c = 0; c < 3; ++c)
        std::memcpy(blob.ptr<float>() + c * planeSize,
                    channels[c].ptr<float>(),
                    static_cast<size_t>(planeSize) * sizeof(float));

    return blob;
}

// ─────────────────────────────────────────────────────────────────────────────
// Post-processing
// ─────────────────────────────────────────────────────────────────────────────

QVector<CrabDetector::Detection>
CrabDetector::postprocess(const float *data,
                          int64_t numAnchors,
                          float scaleX,
                          float scaleY,
                          int padLeft,
                          int padTop,
                          int origW,
                          int origH) const
{
    const int numClasses = static_cast<int>(m_classNames.size());

    std::vector<cv::Rect>  rawBoxes;
    std::vector<float>     rawScores;
    std::vector<int>       rawClassIds;

    for (int64_t a = 0; a < numAnchors; ++a)
    {
        float cx = data[0 * numAnchors + a];
        float cy = data[1 * numAnchors + a];
        float w  = data[2 * numAnchors + a];
        float h  = data[3 * numAnchors + a];

        // Find best class
        float bestConf  = 0.f;
        int   bestClass = 0;
        for (int c = 0; c < numClasses; ++c)
        {
            float score = data[(4 + c) * numAnchors + a];
            if (score > bestConf)
            {
                bestConf  = score;
                bestClass = c;
            }
        }

        if (bestConf < m_confThreshold) continue;

        float x1 = (cx - w * 0.5f - static_cast<float>(padLeft)) / scaleX;
        float y1 = (cy - h * 0.5f - static_cast<float>(padTop))  / scaleY;
        float bw = w / scaleX;
        float bh = h / scaleY;

        x1 = std::max(0.f, std::min(x1, static_cast<float>(origW - 1)));
        y1 = std::max(0.f, std::min(y1, static_cast<float>(origH - 1)));
        bw = std::min(bw, static_cast<float>(origW)  - x1);
        bh = std::min(bh, static_cast<float>(origH) - y1);

        rawBoxes.emplace_back(static_cast<int>(x1), static_cast<int>(y1),
                              static_cast<int>(bw), static_cast<int>(bh));
        rawScores.push_back(bestConf);
        rawClassIds.push_back(bestClass);
    }

    if (rawBoxes.empty()) return {};

    std::vector<int> indices;
    cv::dnn::NMSBoxes(rawBoxes, rawScores,
                      m_confThreshold, m_nmsThreshold,
                      indices);

    QVector<Detection> result;
    result.reserve(static_cast<int>(indices.size()));
    for (int idx : indices)
    {
        Detection d;
        d.box = QRect(rawBoxes[idx].x,  rawBoxes[idx].y,
                      rawBoxes[idx].width, rawBoxes[idx].height);
        d.confidence = rawScores[idx];
        d.species = (rawClassIds[idx] < m_classNames.size())
                     ? m_classNames[rawClassIds[idx]] : "Unknown";
        result.push_back(d);
    }

    return result;
}


