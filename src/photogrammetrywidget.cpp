#include "photogrammetrywidget.h"
#include "modelviewer.h"

#include <QCoreApplication>
#include <QDesktopServices>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QCheckBox>
#include <QPixmap>
#include <QProcess>
#include <QProgressBar>
#include <QPushButton>
#include <QScrollBar>
#include <QSplitter>
#include <QTextEdit>
#include <QInputDialog>
#include <QUrl>
#include <QVBoxLayout>

PhotogrammetryWidget::PhotogrammetryWidget(QWidget *parent)
    : QWidget(parent), m_runner(new ColmapRunner(this)) {
  // Set up workspace relative to the application binary
  QString base = QCoreApplication::applicationDirPath();
  m_workspacePath = base + "/workspace";
  m_imagePath = m_workspacePath + "/images";
  QDir().mkpath(m_imagePath);

  setupUI();

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

  // Configure runner paths
  m_runner->setColmapPath(detectColmapPath());
  m_runner->setWorkspacePath(m_workspacePath);
  m_runner->setImagePath(m_imagePath);

  // Scale / measure tool connections
  connect(m_viewer, &ModelViewer::scalePointsPicked,
          this, &PhotogrammetryWidget::onScalePointsPicked);

  connect(m_viewer, &ModelViewer::scaleApplied,
          [this](float w, float h, float d) {
              m_statusLabel->setText(
                  QString("Scale set \u2014 W:%1 m  H:%2 m  D:%3 m")
                  .arg(w,0,'f',3).arg(h,0,'f',3).arg(d,0,'f',3));
              m_scaleButton->setChecked(false);
          });

  connect(m_viewer, &ModelViewer::measurementReady,
          [this](float total, float dx, float dy, float dz) {
              m_statusLabel->setText(
                  QString("A\u2192B: %1 m    \u0394X:%2  \u0394Y:%3  \u0394Z:%4")
                  .arg(total,0,'f',3).arg(dx,0,'f',3).arg(dy,0,'f',3).arg(dz,0,'f',3));
              m_measureButton->setChecked(false);
          });

  connect(m_scaleButton, &QPushButton::toggled, [this](bool on) {
      if (on) { m_measureButton->setChecked(false); m_viewer->enterScaleMode(); }
      else      m_viewer->exitPickMode();
  });

  connect(m_measureButton, &QPushButton::toggled, [this](bool on) {
      if (on) { m_scaleButton->setChecked(false); m_viewer->enterMeasureMode(); }
      else      m_viewer->exitPickMode();
  });

  // Load any images already sitting in the workspace
  refreshThumbnails();
}

QString PhotogrammetryWidget::detectColmapPath() {
  QString base = QCoreApplication::applicationDirPath();

#ifdef Q_OS_WIN
  QString winPath = base + "/tools/win64/colmap.exe";
  if (QFileInfo::exists(winPath))
    return winPath;
#elif defined(Q_OS_MACOS)
  QString macPath = base + "/tools/macos/bin/colmap";
  if (QFileInfo::exists(macPath))
    return macPath;
#else
  QString linuxPath = base + "/tools/linux/bin/colmap";
  if (QFileInfo::exists(linuxPath))
    return linuxPath;
#endif

  return "colmap";
}


void PhotogrammetryWidget::setupUI() {
  auto *mainLayout = new QVBoxLayout(this);

  // --- Top bar: status + buttons ---
  m_statusLabel = new QLabel("Ready — import images to begin", this);
  mainLayout->addWidget(m_statusLabel);

  auto *buttonLayout = new QHBoxLayout();
  m_importImagesButton = new QPushButton("Import Images", this);
  m_importVideoButton = new QPushButton("Import Video", this);
  m_clearButton = new QPushButton("Clear", this);
  m_runButton = new QPushButton("Run Photogrammetry", this);
  m_cancelButton = new QPushButton("Cancel", this);
  m_resetCameraButton = new QPushButton("Reset View", this);
  m_loadPlyButton = new QPushButton("Open PLY...", this);
  m_cancelButton->setEnabled(false);
  m_runButton->setEnabled(false);

  m_scaleButton   = new QPushButton("Set Scale", this);
  m_measureButton = new QPushButton("Measure",   this);
  m_scaleButton->setCheckable(true);
  m_measureButton->setCheckable(true);
  m_scaleButton->setToolTip("Click two points of known distance to set real-world scale");
  m_measureButton->setToolTip("Click two points to measure the distance between them");

  m_denseCheckBox = new QCheckBox("Dense Reconstruction", this);
#if defined(Q_OS_WIN)
  m_denseCheckBox->setToolTip("Runs CUDA-accelerated patch_match_stereo + stereo_fusion after sparse reconstruction.\nRequires an NVIDIA GPU with CUDA.");
#else
  m_denseCheckBox->setToolTip("Runs CPU-based dense reconstruction via OpenMVS DensifyPointCloud.\nSlower than CUDA but works on any hardware.");
#endif

  buttonLayout->addWidget(m_importImagesButton);
  buttonLayout->addWidget(m_importVideoButton);
  buttonLayout->addWidget(m_clearButton);
  buttonLayout->addWidget(m_denseCheckBox);
  buttonLayout->addStretch();
  buttonLayout->addWidget(m_scaleButton);
  buttonLayout->addWidget(m_measureButton);
  buttonLayout->addWidget(m_loadPlyButton);
  buttonLayout->addWidget(m_resetCameraButton);
  buttonLayout->addWidget(m_runButton);
  buttonLayout->addWidget(m_cancelButton);
  mainLayout->addLayout(buttonLayout);

  // --- Progress bar ---
  m_progressBar = new QProgressBar(this);
  m_progressBar->setRange(0, 3);
  m_progressBar->setValue(0);
  m_progressBar->setTextVisible(true);
  m_progressBar->setFormat("Step %v / %m");
  mainLayout->addWidget(m_progressBar);

  // --- Main content area ---
  // Layout: [Image List] | [3D Viewer / Log]
  auto *mainSplitter = new QSplitter(Qt::Horizontal, this);

  // Left: image thumbnails
  m_imageList = new QListWidget(this);
  m_imageList->setViewMode(QListView::IconMode);
  m_imageList->setIconSize(QSize(120, 90));
  m_imageList->setResizeMode(QListView::Adjust);
  m_imageList->setSpacing(4);
  m_imageList->setMinimumWidth(180);
  m_imageList->setMaximumWidth(300);
  mainSplitter->addWidget(m_imageList);

  // Right: 3D viewer on top, log on bottom
  m_rightSplitter = new QSplitter(Qt::Vertical, this);

  m_viewer = new ModelViewer(this);
  m_viewer->setMinimumHeight(300);
  m_rightSplitter->addWidget(m_viewer);

  m_logOutput = new QTextEdit(this);
  m_logOutput->setReadOnly(true);
  m_logOutput->setFontFamily("Courier");
  m_logOutput->setMaximumHeight(200);
  m_rightSplitter->addWidget(m_logOutput);

  m_rightSplitter->setStretchFactor(0, 3); // viewer gets more space
  m_rightSplitter->setStretchFactor(1, 1); // log gets less

  mainSplitter->addWidget(m_rightSplitter);
  mainSplitter->setStretchFactor(0, 0); // image list stays narrow
  mainSplitter->setStretchFactor(1, 1); // viewer+log expands

  mainLayout->addWidget(mainSplitter, 1);

  // --- Connect buttons ---
  connect(m_importImagesButton, &QPushButton::clicked, this,
          &PhotogrammetryWidget::onImportImagesClicked);
  connect(m_importVideoButton, &QPushButton::clicked, this,
          &PhotogrammetryWidget::onImportVideoClicked);
  connect(m_clearButton, &QPushButton::clicked, this,
          &PhotogrammetryWidget::onClearImagesClicked);
  connect(m_runButton, &QPushButton::clicked, this,
          &PhotogrammetryWidget::onRunClicked);
  connect(m_cancelButton, &QPushButton::clicked, this,
          &PhotogrammetryWidget::onCancelClicked);
  connect(m_resetCameraButton, &QPushButton::clicked, this,
          &PhotogrammetryWidget::onResetCameraClicked);
  connect(m_loadPlyButton, &QPushButton::clicked, this,
          &PhotogrammetryWidget::onLoadPlyClicked);
}

// ─── Image Management ───────────────────────────────────────────────────────

void PhotogrammetryWidget::onImportImagesClicked() {
  QStringList files = QFileDialog::getOpenFileNames(
      this, "Import Images", QString(),
      "Images (*.jpg *.jpeg *.png *.tiff *.tif *.bmp)");

  if (files.isEmpty())
    return;

  QDir imgDir(m_imagePath);
  int imported = 0;

  for (const QString &src : files) {
    QFileInfo fi(src);
    QString dest = imgDir.filePath(fi.fileName());

    if (QFile::exists(dest)) {
      QString base = fi.baseName();
      QString ext = fi.suffix();
      int i = 1;
      while (QFile::exists(dest)) {
        dest = imgDir.filePath(QString("%1_%2.%3").arg(base).arg(i++).arg(ext));
      }
    }

    if (QFile::copy(src, dest))
      imported++;
  }

  m_statusLabel->setText(QString("Imported %1 images").arg(imported));
  refreshThumbnails();
}

void PhotogrammetryWidget::onImportVideoClicked() {
  QString videoPath =
      QFileDialog::getOpenFileName(this, "Import Video", QString(),
                                   "Video (*.mp4 *.avi *.mov *.mkv *.webm)");

  if (videoPath.isEmpty())
    return;

  m_statusLabel->setText("Extracting frames from video...");
  setRunning(true);

  QProcess *ffmpeg = new QProcess(this);
  QString outputPattern = m_imagePath + "/frame_%04d.jpg";

  QString filter = "select=not(mod(n\\,10))";

  ffmpeg->start("ffmpeg", {"-i", videoPath, "-vf", filter, "-vsync", "vfr",
                           "-q:v", "2", outputPattern});

  connect(ffmpeg, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
          [this, ffmpeg](int exitCode, QProcess::ExitStatus) {
            ffmpeg->deleteLater();
            setRunning(false);

            if (exitCode == 0) {
              refreshThumbnails();
              int count = QDir(m_imagePath)
                              .entryList({"*.jpg", "*.jpeg", "*.png", "*.tiff"},
                                         QDir::Files)
                              .count();
              m_statusLabel->setText(
                  QString("Extracted frames — %1 images ready").arg(count));
            } else {
              m_statusLabel->setText(
                  "Frame extraction failed. Is ffmpeg installed?");
              m_logOutput->append("[ERROR] ffmpeg exited with code " +
                                  QString::number(exitCode));
            }
          });

  if (!ffmpeg->waitForStarted(3000)) {
    ffmpeg->deleteLater();
    setRunning(false);
    m_statusLabel->setText(
        "Could not start ffmpeg. Make sure it's installed and on PATH.");
  }
}

void PhotogrammetryWidget::onClearImagesClicked() {
  QDir imgDir(m_imagePath);
  QStringList images = imgDir.entryList(
      {"*.jpg", "*.jpeg", "*.png", "*.tiff", "*.tif", "*.bmp"}, QDir::Files);

  if (images.isEmpty())
    return;

  auto answer = QMessageBox::question(
      this, "Clear Images",
      QString("Remove %1 images from workspace?").arg(images.count()));

  if (answer != QMessageBox::Yes)
    return;

  for (const QString &f : images)
    imgDir.remove(f);

  QDir(m_workspacePath + "/sparse").removeRecursively();
  QDir(m_workspacePath + "/dense").removeRecursively();
  QFile::remove(m_workspacePath + "/database.db");
  QFile::remove(m_workspacePath + "/model.ply");

  // Remove OpenMVS artifacts so stale depth maps can't corrupt a future run
  QDir wsDir(m_workspacePath);
  for (const QString &f : wsDir.entryList({"depth*.dmap", "scene*.mvs", "dense*.mvs", "*.ply"}, QDir::Files))
    wsDir.remove(f);

  m_viewer->clear();
  refreshThumbnails();
  m_statusLabel->setText("Workspace cleared");
  m_logOutput->clear();
  m_progressBar->setValue(0);
}

void PhotogrammetryWidget::refreshThumbnails() {
  m_imageList->clear();

  QDir imgDir(m_imagePath);
  QStringList images =
      imgDir.entryList({"*.jpg", "*.jpeg", "*.png", "*.tiff", "*.tif", "*.bmp"},
                       QDir::Files, QDir::Name);

  for (const QString &filename : images) {
    QPixmap pix(imgDir.filePath(filename));
    if (pix.isNull())
      continue;

    auto *item =
        new QListWidgetItem(QIcon(pix.scaled(120, 90, Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation)),
                            filename);
    m_imageList->addItem(item);
  }

  bool hasImages = !images.isEmpty();
  m_runButton->setEnabled(hasImages);

  if (hasImages)
    m_statusLabel->setText(QString("%1 images ready").arg(images.count()));
}

// ─── Pipeline Control ───────────────────────────────────────────────────────

void PhotogrammetryWidget::onRunClicked() {
  QDir imgDir(m_imagePath);
  int count =
      imgDir.entryList({"*.jpg", "*.jpeg", "*.png", "*.tiff"}, QDir::Files)
          .count();
  if (count < 3) {
    m_statusLabel->setText("Need at least 3 images to reconstruct");
    return;
  }

  m_logOutput->clear();
  m_progressBar->setValue(0);
  m_viewer->clear();
  setRunning(true);

  m_runner->setWorkspacePath(m_workspacePath);
  m_runner->setImagePath(m_imagePath);
  m_runner->setDenseEnabled(m_denseCheckBox->isChecked());
  m_runner->runFullPipeline();

  m_progressBar->setRange(0, m_runner->totalSteps());
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
  m_logOutput->verticalScrollBar()->setValue(
      m_logOutput->verticalScrollBar()->maximum());
}

void PhotogrammetryWidget::onStepFinished(const QString &step, bool success) {
  m_progressBar->setValue(m_progressBar->value() + 1);
  m_logOutput->append(success
                          ? QString::fromUtf8("\u2713 ") + step + " complete."
                          : QString::fromUtf8("\u2717 ") + step + " failed.");
}

void PhotogrammetryWidget::onPipelineFinished(bool success) {
  setRunning(false);

  if (success) {
    m_statusLabel->setText("Converting to point cloud...");
    convertAndLoadModel();
  } else {
    m_statusLabel->setText("Pipeline failed — check log for details");
  }
}

void PhotogrammetryWidget::onError(const QString &error) {
  m_logOutput->append("\n[ERROR] " + error);
}

void PhotogrammetryWidget::onResetCameraClicked() { m_viewer->resetCamera(); }

void PhotogrammetryWidget::onLoadPlyClicked() {
  QString path = QFileDialog::getOpenFileName(
      this, "Open PLY File", QString(), "PLY Files (*.ply)");
  if (path.isEmpty())
    return;
  m_viewer->loadPLY(path);
  m_statusLabel->setText("Loaded: " + QFileInfo(path).fileName());
}

// ─── Model Conversion & Loading ─────────────────────────────────────────────

void PhotogrammetryWidget::convertAndLoadModel() {
  if (m_denseCheckBox->isChecked()) {
#if defined(Q_OS_WIN)
    QString densePly = m_workspacePath + "/dense/fused.ply";
#else
    // OpenMVS DensifyPointCloud outputs a PLY alongside the .mvs file
    QString densePly = m_workspacePath + "/dense.ply";
#endif
    if (QFile::exists(densePly)) {
      m_logOutput->append("\n=== Loading Dense Model ===");
      m_viewer->loadPLY(densePly);
      m_statusLabel->setText(
          "Dense reconstruction complete — use mouse to orbit/pan/zoom");
      m_logOutput->append(QString::fromUtf8("\u2713 ") +
                          "Dense model loaded into viewer.");
      return;
    }
    m_logOutput->append("[WARN] Dense output not found — falling back to sparse.");
  }

  // Find the sparse reconstruction output — COLMAP puts it in sparse/0/
  QString sparsePath = m_workspacePath + "/sparse/0";
  if (!QDir(sparsePath).exists()) {
    // Try sparse/ directly in case there's no subdirectory
    sparsePath = m_workspacePath + "/sparse";
    if (!QDir(sparsePath).exists()) {
      m_statusLabel->setText("No reconstruction found in sparse/");
      return;
    }
  }

  QString plyPath = m_workspacePath + "/model.ply";

  // Use COLMAP's model_converter to export to PLY
  QProcess *converter = new QProcess(this);

  // Set up environment same as pipeline
  QString base = QCoreApplication::applicationDirPath();
  QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
  env.insert("QT_QPA_PLATFORM", "offscreen");
  env.insert("OPENBLAS_NUM_THREADS", "1");

#if defined(Q_OS_MACOS)
  QString toolsBase = base + "/tools/macos";
  QString libVar = "DYLD_LIBRARY_PATH";
#elif defined(Q_OS_WIN)
  QString toolsBase = base + "/tools/win64";
  QString libVar = "";
#else
  QString toolsBase = base + "/tools/linux";
  QString libVar = "LD_LIBRARY_PATH";
#endif

#ifndef Q_OS_WIN
  QString libPath = toolsBase + "/lib";
  if (QDir(libPath).exists()) {
    QString existing = env.value(libVar);
    env.insert(libVar, libPath + (existing.isEmpty() ? "" : ":" + existing));
  }
#endif

  QString pluginPath = toolsBase + "/plugins";
  if (QDir(pluginPath).exists()) {
    env.insert("QT_PLUGIN_PATH", pluginPath);
  }

  converter->setProcessEnvironment(env);

  connect(
      converter, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
      [this, converter, plyPath](int exitCode, QProcess::ExitStatus) {
        converter->deleteLater();

        if (exitCode == 0 && QFile::exists(plyPath)) {
          m_logOutput->append("\n=== Loading 3D Model ===");
          m_viewer->loadPLY(plyPath);
          m_statusLabel->setText(
              "Reconstruction complete — use mouse to orbit/pan/zoom");
          m_logOutput->append(QString::fromUtf8("\u2713 ") +
                              "Model loaded into viewer.");
        } else {
          m_statusLabel->setText("Model conversion failed");
          m_logOutput->append("[ERROR] model_converter failed with exit code " +
                              QString::number(exitCode));
          m_logOutput->append(
              QString::fromUtf8(converter->readAllStandardError()));
        }
      });

  QString colmapPath = detectColmapPath();
  converter->start(colmapPath,
                   {"model_converter", "--input_path", sparsePath,
                    "--output_path", plyPath, "--output_type", "PLY"});

  if (!converter->waitForStarted(5000)) {
    converter->deleteLater();
    m_statusLabel->setText("Failed to start model converter");
  }
}

void PhotogrammetryWidget::onScalePointsPicked(float /*measuredModelDist*/) {
  bool ok;
  double val = QInputDialog::getDouble(
      this, "Set Scale",
      "Real-world distance between the two selected points (metres):",
      0.1, 0.001, 10000.0, 4, &ok);
  if (ok && val > 0)
    m_viewer->applyScale(static_cast<float>(val));
  m_scaleButton->setChecked(false);
}

void PhotogrammetryWidget::setRunning(bool running) {
  m_runButton->setEnabled(!running);
  m_cancelButton->setEnabled(running);
  m_importImagesButton->setEnabled(!running);
  m_importVideoButton->setEnabled(!running);
  m_clearButton->setEnabled(!running);
}
