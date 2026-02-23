#include "colmaprunner.h"

#include <QDir>

ColmapRunner::ColmapRunner(QObject *parent)
    : QObject(parent)

    , m_process(new QProcess(this))
{
    connect(m_process, &QProcess::readyReadStandardOutput, this, &ColmapRunner::onProcessOutput);

    connect(m_process, &QProcess::readyReadStandardError, this, &ColmapRunner::onProcessOutput);
    connect(m_process,
            QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this,
            &ColmapRunner::onProcessFinished);
}

void ColmapRunner::setColmapPath(const QString &path)
{
    m_colmapPath = path;
}
void ColmapRunner::setWorkspacePath(const QString &path)
{
    m_workspacePath = path;
}

void ColmapRunner::setImagePath(const QString &path)
{
    m_imagePath = path;
}

void ColmapRunner::runFullPipeline()
{
    m_cancelled = false;
    m_currentStep = 0;

    QString dbPath = m_workspacePath + "/database.db";
    QString sparsePath = m_workspacePath + "/sparse";
    QDir().mkpath(sparsePath);

    // Define the pipeline steps
    m_steps = {{"Feature Extraction",
                {"feature_extractor", "--database_path", dbPath, "--image_path", m_imagePath}},
               {"Feature Matching",
                {"exhaustive_matcher", // or sequential_matcher for ordered image sets
                 "--database_path",
                 dbPath}},
               {"Sparse Reconstruction",
                {"mapper",
                 "--database_path",
                 dbPath,
                 "--image_path",
                 m_imagePath,
                 "--output_path",
                 sparsePath}}

    };

    runNextStep();
}

void ColmapRunner::runNextStep()
{
    if (m_cancelled || m_currentStep >= m_steps.size()) {
        emit pipelineFinished(!m_cancelled);
        return;
    }

    auto [name, args] = m_steps[m_currentStep];
    startStep(name, args);
}

void ColmapRunner::startStep(const QString &stepName, const QStringList &args)
{
    emit stepStarted(stepName);

    m_process->start(m_colmapPath, args);

    if (!m_process->waitForStarted(3000)) {
        emit errorOccurred("Failed to start COLMAP. Check path: " + m_colmapPath);
        emit pipelineFinished(false);
    }
}

void ColmapRunner::onProcessOutput()
{
    // Read both stdout and stderr
    QString out = QString::fromUtf8(m_process->readAllStandardOutput());
    QString err = QString::fromUtf8(m_process->readAllStandardError());

    if (!out.isEmpty())
        for (const QString &line : out.split('\n', Qt::SkipEmptyParts))
            emit progressOutput(line);

    if (!err.isEmpty())
        for (const QString &line : err.split('\n', Qt::SkipEmptyParts))
            emit progressOutput("[stderr] " + line);
}

void ColmapRunner::onProcessFinished(int exitCode, QProcess::ExitStatus status)
{
    auto [name, args] = m_steps[m_currentStep];
    bool success = (status == QProcess::NormalExit && exitCode == 0);

    emit stepFinished(name, success);

    if (!success) {
        emit errorOccurred(QString("Step '%1' failed with exit code %2").arg(name).arg(exitCode));
        emit pipelineFinished(false);
        return;
    }

    m_currentStep++;

    runNextStep();
}

void ColmapRunner::cancel()
{
    m_cancelled = true;
    if (m_process->state() != QProcess::NotRunning)
        m_process->kill();
}
