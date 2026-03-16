#pragma once
#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>

class ColmapRunner : public QObject {
  Q_OBJECT

public:
  explicit ColmapRunner(QObject *parent = nullptr);

  void setColmapPath(const QString &path);
  void setWorkspacePath(const QString &path);
  void setImagePath(const QString &path);
  void setDenseEnabled(bool enabled);
  bool denseEnabled() const { return m_denseEnabled; }

  void runFullPipeline();
  void cancel();

  int totalSteps() const { return m_steps.size(); }

signals:
  void stepStarted(const QString &stepName);
  void progressOutput(const QString &line);
  void stepFinished(const QString &stepName, bool success);
  void pipelineFinished(bool success);
  void errorOccurred(const QString &error);

private slots:
  void onProcessOutput();
  void onProcessFinished(int exitCode, QProcess::ExitStatus status);

private:
  struct PipelineStep {
    QString     name;
    QString     exe;   // empty → use m_colmapPath
    QStringList args;
  };

  void runNextStep();
  void startStep(const PipelineStep &step);

  QProcess *m_process;
  QString m_colmapPath;
  QString m_workspacePath;
  QString m_imagePath;

  QList<PipelineStep> m_steps;
  int m_currentStep = 0;
  bool m_cancelled = false;
  bool m_denseEnabled = false;
};
