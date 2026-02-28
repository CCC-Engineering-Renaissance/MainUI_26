#pragma once
#include <QObject>

#include <QProcess>
#include <QString>

class ColmapRunner : public QObject
{
    Q_OBJECT

public:
    explicit ColmapRunner(QObject *parent = nullptr);

    void setColmapPath(const QString &path);    // path to colmap.exe
    void setWorkspacePath(const QString &path); // where db + sparse/ will be written
    void setImagePath(const QString &path);     // where your images are

    void runFullPipeline(); // runs all steps sequentially
    void cancel();

signals:
    void stepStarted(const QString &stepName);
    void progressOutput(const QString &line); // raw stdout/stderr per line
    void stepFinished(const QString &stepName, bool success);
    void pipelineFinished(bool success);
    void errorOccurred(const QString &error);

private slots:
    void onProcessOutput();
    void onProcessFinished(int exitCode, QProcess::ExitStatus status);

private:
    void runNextStep();
    void startStep(const QString &stepName, const QStringList &args);

    QProcess *m_process;
    QString m_colmapPath;
    QString m_workspacePath;
    QString m_imagePath;

    QList<QPair<QString, QStringList>> m_steps; // name + args for each step
    int m_currentStep = 0;
    bool m_cancelled = false;
};
