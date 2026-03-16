// ColmapPipeline.cpp
#include "ColmapPipeline.h"
#include <QDir>

ColmapPipeline::ColmapPipeline(QObject* parent) : QObject(parent) {}

void ColmapPipeline::setWorkspace(const QString& workspace) {
    m_workspace = workspace;
    m_databasePath = workspace + "/database.db";
    QDir().mkpath(workspace + "/sparse");
    QDir().mkpath(workspace + "/dense");
}

void ColmapPipeline::setImagePath(const QString& path) {
    m_imagePath = path;
}

void ColmapPipeline::buildSteps() {
    m_steps.clear();

    // Step 1: Feature extraction
    m_steps.enqueue({"Feature Extraction", {
                                               "feature_extractor",
                                               "--database_path", m_databasePath,
                                               "--image_path", m_imagePath,
                                               "--ImageReader.single_camera", "1",
                                               "--ImageReader.camera_model", "OPENCV",
                                               // underwater images often have radial distortion
                                               "--SiftExtraction.max_num_features", "8192"
                                           }});

    // Step 2: Sequential matching (ideal for ROV video frames)
    m_steps.enqueue({"Feature Matching", {
                                             "sequential_matcher",
                                             "--database_path", m_databasePath,
                                             "--SequentialMatching.overlap", "10",
                                             "--SequentialMatching.loop_detection", "1"
                                         }});

    // Step 3: Sparse reconstruction
    m_steps.enqueue({"Sparse Reconstruction", {
                                                  "mapper",
                                                  "--database_path", m_databasePath,
                                                  "--image_path", m_imagePath,
                                                  "--output_path", m_workspace + "/sparse"
                                              }});

    // Step 4: Undistort images for dense recon
    m_steps.enqueue({"Image Undistortion", {
                                               "image_undistorter",
                                               "--image_path", m_imagePath,
                                               "--input_path", m_workspace + "/sparse/0",
                                               "--output_path", m_workspace + "/dense",
                                               "--output_type", "COLMAP"
                                           }});

    // Step 5: Dense stereo (CUDA required)
    m_steps.enqueue({"Dense Stereo", {
                                         "patch_match_stereo",
                                         "--workspace_path", m_workspace + "/dense",
                                         "--PatchMatchStereo.geom_consistency", "true"
                                     }});

    // Step 6: Fusion into point cloud
    m_steps.enqueue({"Point Cloud Fusion", {
                                               "stereo_fusion",
                                               "--workspace_path", m_workspace + "/dense",
                                               "--output_path", m_workspace + "/dense/fused.ply"
                                           }});
}

void ColmapPipeline::runFullPipeline() {
    buildSteps();
    m_currentStep = 0;
    m_totalSteps = m_steps.size();
    runNextStep();
}

void ColmapPipeline::runNextStep() {
    if (m_steps.isEmpty()) {
        emit pipelineFinished(true);
        return;
    }

    PipelineStep step = m_steps.dequeue();
    m_currentStep++;
    emit stepStarted(step.name);
    emit progressUpdated(m_currentStep, m_totalSteps);

    m_process = new QProcess(this);

    connect(m_process, &QProcess::readyReadStandardOutput, [this]() {
        emit logOutput(QString::fromUtf8(m_process->readAllStandardOutput()));
    });
    connect(m_process, &QProcess::readyReadStandardError, [this]() {
        emit logOutput(QString::fromUtf8(m_process->readAllStandardError()));
    });

    connect(m_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [this, stepName = step.name](int exitCode, QProcess::ExitStatus) {
                bool ok = (exitCode == 0);
                emit stepFinished(stepName, ok);
                m_process->deleteLater();
                m_process = nullptr;

                if (ok) {
                    runNextStep();
                } else {
                    emit pipelineFinished(false);
                }
            });

    m_process->start("colmap", step.args);
}

void ColmapPipeline::cancel() {
    m_steps.clear();
    if (m_process && m_process->state() == QProcess::Running) {
        m_process->kill();
    }
}
