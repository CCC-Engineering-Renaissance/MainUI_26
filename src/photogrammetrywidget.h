#pragma once
#include "colmaprunner.h"
#include <QDir>
#include <QWidget>

class QCheckBox;
class QTextEdit;
class QPushButton;
class QProgressBar;
class QLabel;
class QListWidget;
class QSplitter;
class ModelViewer;

class PhotogrammetryWidget : public QWidget {
  Q_OBJECT

public:
  explicit PhotogrammetryWidget(QWidget *parent = nullptr);

private slots:
  // image management
  void onImportImagesClicked();
  void onImportVideoClicked();
  void onClearImagesClicked();

  // pipeline control
  void onRunClicked();
  void onCancelClicked();

  // runner signals
  void onStepStarted(const QString &step);
  void onProgressOutput(const QString &line);
  void onStepFinished(const QString &step, bool success);
  void onPipelineFinished(bool success);
  void onError(const QString &error);

  // viewer
  void onResetCameraClicked();
  void onLoadPlyClicked();
  void onScalePointsPicked(float measuredModelDist);

private:
  void setupUI();
  void setRunning(bool running);
  void refreshThumbnails();
  QString detectColmapPath();
  void convertAndLoadModel();

  ColmapRunner *m_runner;

  // workspace paths
  QString m_workspacePath;
  QString m_imagePath;

  // UI elements — left panel (images + controls)
  QListWidget *m_imageList;
  QPushButton *m_importImagesButton;
  QPushButton *m_importVideoButton;
  QPushButton *m_clearButton;
  QPushButton *m_runButton;
  QPushButton *m_cancelButton;
  QPushButton *m_resetCameraButton;
  QPushButton *m_loadPlyButton;
  QPushButton *m_scaleButton;
  QPushButton *m_measureButton;
  QCheckBox   *m_denseCheckBox;
  QProgressBar *m_progressBar;
  QLabel *m_statusLabel;

  // UI elements — right panel (viewer + log)
  ModelViewer *m_viewer;
  QTextEdit *m_logOutput;
  QSplitter *m_rightSplitter;
};
