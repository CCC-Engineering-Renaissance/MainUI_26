#ifndef CRABDETECTOR_H
#define CRABDETECTOR_H

#include <QImage>
#include <QRect>
#include <QString>
#include <QVector>

#include <onnxruntime_cxx_api.h>
#include <opencv2/opencv.hpp>

// Runs YOLOv8 model exported to ONNX

class CrabDetector
{
public:
    struct Detection
    {
        QRect box;
        QString species;
        float confidence;
    };

    // Construction
    CrabDetector();
    ~CrabDetector() = default;

    CrabDetector(const CrabDetector &) = delete;
    CrabDetector &operator=(const CrabDetector &) = delete;

    // Configuration
    bool loadModel(const QString &modelPath);
    bool isLoaded() const { return m_loaded; }

    void setConfidenceThreshold(float t) { m_confThreshold = t; }
    void setNmsThreshold(float t) { m_nmsThreshold = t; }

    // Run
    QVector<Detection> detect(const QImage &image);

private:
    // Process
    cv::Mat preprocess(const cv::Mat &src, float &scaleX, float &scaleY, int &padLeft, int &padTop) const;

    QVector<Detection> postprocess(const float *data,
                                   int64_t numAnchors,
                                   float scaleX,
                                   float scaleY,
                                   int padLeft,
                                   int padTop,
                                   int origW,
                                   int origH) const;

    // ONNX Runtime
    Ort::Env  m_env;
    Ort::SessionOptions m_sessionOptions;
    Ort::Session m_session { nullptr };

    // Model
    QVector<QString> m_classNames = {
        "Atlantic-Rock-Crabs", // class 0
        "European-Green-Crabs",  // class 1
        "Jonah-Crabs"  // class 2
    };

    // Dimensions
    int m_inputWidth  = 640;
    int m_inputHeight = 640;

    // Detection thresholds
    float m_confThreshold = 0.35f;
    float m_nmsThreshold  = 0.45f;

    bool m_loaded = false;
};

#endif // CRABDETECTOR_H
