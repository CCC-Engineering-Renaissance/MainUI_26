#pragma once
#include "colmaprunner.h"
#include <QWidget>

class QTextEdit;
class QPushButton;
class QProgressBar;
class QLabel;

class PhotogrammetryWidget : public QWidget {
  Q_OBJECT

public:
  explicit PhotogrammetryWidget(QWidget *parent = nullptr);

private slots:
  void onRunClicked();
  void onCancelClicked();
  void onStepStarted(const QString &step);
  void onProgressOutput(const QString &line);

  void onStepFinished(const QString &step, bool success);
  void onPipelineFinished(bool success);
  void onError(const QString &error);

private:
  void setupUI();
  void setRunning(bool running);

  ColmapRunner *m_runner;

  QPushButton *m_runButton;
  QPushButton *m_cancelButton;

  QProgressBar *m_progressBar;
  QLabel *m_statusLabel;
  QTextEdit *m_logOutput;
};
