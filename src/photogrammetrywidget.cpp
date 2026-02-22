#include "photogrammetrywidget.h"

#include <QVBoxLayout>

#include <QHBoxLayout>

#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QTextEdit>
#include <QScrollBar>
#include <QTCore>


PhotogrammetryWidget::PhotogrammetryWidget(QWidget *parent)
    : QWidget(parent), m_runner(new ColmapRunner(this)) {
  setupUI();
    QString base = QCoreApplication::applicationDirPath();

  // Wire up runner signals
  connect(m_runner, &ColmapRunner::stepStarted, this,
          &PhotogrammetryWidget::onStepStarted);
  connect(m_runner, &ColmapRunner::progressOutput, this,
          &PhotogrammetryWidget::onProgressOutput);
  connect(m_runner, &ColmapRunner::stepFinished, this,
          &PhotogrammetryWidget::onStepFinished);
  connect(m_runner, &ColmapRunner::pipelineFinished, this,
          &PhotogrammetryWidget::onPipelineFinished);
  connect(m_runner, &ColmapRunner::errorOccurred, this,
          &PhotogrammetryWidget::onError);

  // Point to your COLMAP binary and working paths
  // In production you'd make these configurable in the UI or a settings file
  m_runner->setColmapPath(base + "./tools/COLMAP.bat");
  m_runner->setWorkspacePath(base + "./workspace");
  m_runner->setImagePath(base + "./workspace/images");
}

void PhotogrammetryWidget::setupUI() {
  auto *mainLayout = new QVBoxLayout(this);

  m_statusLabel = new QLabel("Ready", this);
  mainLayout->addWidget(m_statusLabel);

  m_progressBar = new QProgressBar(this);
  m_progressBar->setRange(0, 3); // 3 steps
  m_progressBar->setValue(0);
  mainLayout->addWidget(m_progressBar);

  m_logOutput = new QTextEdit(this);
  m_logOutput->setReadOnly(true);
  m_logOutput->setFontFamily("Courier"); // monospace for log output

  mainLayout->addWidget(m_logOutput);

  auto *buttonLayout = new QHBoxLayout();
  m_runButton = new QPushButton("Run Photogrammetry", this);
  m_cancelButton = new QPushButton("Cancel", this);
  m_cancelButton->setEnabled(false);
  buttonLayout->addWidget(m_runButton);
  buttonLayout->addWidget(m_cancelButton);
  mainLayout->addLayout(buttonLayout);

  connect(m_runButton, &QPushButton::clicked, this,
          &PhotogrammetryWidget::onRunClicked);
  connect(m_cancelButton, &QPushButton::clicked, this,
          &PhotogrammetryWidget::onCancelClicked);
}

void PhotogrammetryWidget::onRunClicked() {
  m_logOutput->clear();

  m_progressBar->setValue(0);

  setRunning(true);
  m_runner->runFullPipeline();
}

void PhotogrammetryWidget::onCancelClicked() {

  m_runner->cancel();
  setRunning(false);
  m_statusLabel->setText("Cancelled.");
}

void PhotogrammetryWidget::onStepStarted(const QString &step) {
  m_statusLabel->setText("Running: " + step);
  m_logOutput->append("\n=== " + step + " ===");
}

void PhotogrammetryWidget::onProgressOutput(const QString &line) {
  m_logOutput->append(line);
  // Auto-scroll to bottom
  m_logOutput->verticalScrollBar()->setValue(
      m_logOutput->verticalScrollBar()->maximum());
}

void PhotogrammetryWidget::onStepFinished(const QString &step, bool success) {
  m_progressBar->setValue(m_progressBar->value() + 1);
  m_logOutput->append(success ? "✓ " + step + " complete."
                              : "✗ " + step + " failed.");
}

void PhotogrammetryWidget::onPipelineFinished(bool success) {
  setRunning(false);
  m_statusLabel->setText(success ? "Pipeline complete!"
                                 : "Pipeline failed. Check log.");
}

void PhotogrammetryWidget::onError(const QString &error) {
  m_logOutput->append("\n[ERROR] " + error);
}

void PhotogrammetryWidget::setRunning(bool running) {
  m_runButton->setEnabled(!running);
  m_cancelButton->setEnabled(running);
}
