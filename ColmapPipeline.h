// ColmapPipeline.h
#pragma once
#include <QObject>
#include <QProcess>
#include <QQueue>
#include <functional>

struct PipelineStep
{
    QString name;
    QStringList args;
};

class ColmapPipeline : public QObject
{
    Q_OBJECT
public:
    explicit ColmapPipeline(QObject *parent = nullptr);

    void setWorkspace(const QString &workspace);
    void setImagePath(const QString &imagePath);
    void runFullPipeline();
    void cancel();

signals:
    void stepStarted(const QString &stepName);
    void logOutput(const QString &text);
    void stepFinished(const QString &stepName, bool success);
    void pipelineFinished(bool success);
    void progressUpdated(int stepIndex, int totalSteps);

private slots:
    void runNextStep();

private:
    QQueue<PipelineStep> m_steps;
    QProcess *m_process = nullptr;
    QString m_workspace;
    QString m_imagePath;
    QString m_databasePath;
    int m_currentStep = 0;
    int m_totalSteps = 0;

    void buildSteps();
};
