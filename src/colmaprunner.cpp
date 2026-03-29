#include "colmaprunner.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcessEnvironment>

ColmapRunner::ColmapRunner(QObject *parent)
    : QObject(parent), m_process(new QProcess(this)) {
  connect(m_process, &QProcess::readyReadStandardOutput, this,
          &ColmapRunner::onProcessOutput);
  connect(m_process, &QProcess::readyReadStandardError, this,
          &ColmapRunner::onProcessOutput);
  connect(m_process,
          QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
          &ColmapRunner::onProcessFinished);
}

void ColmapRunner::setColmapPath(const QString &path) { m_colmapPath = path; }
void ColmapRunner::setWorkspacePath(const QString &path) {
  m_workspacePath = path;
}
void ColmapRunner::setImagePath(const QString &path) { m_imagePath = path; }
void ColmapRunner::setDenseEnabled(bool enabled) { m_denseEnabled = enabled; }

bool ColmapRunner::supportsOption(const QString &command, const QString &option) {
  const QString cacheKey = command + "|" + option;
  if (m_supportedOptions.contains(cacheKey))
    return true;
  if (m_unsupportedOptions.contains(cacheKey))
    return false;

  QProcess probe;
  probe.setProcessChannelMode(QProcess::MergedChannels);
  probe.start(m_colmapPath, {command, "-h"});
  if (!probe.waitForStarted(5000) || !probe.waitForFinished(5000)) {
    m_unsupportedOptions.insert(cacheKey);
    return false;
  }

  const QString output = QString::fromUtf8(probe.readAll());
  const bool supported = output.contains(option);
  (supported ? m_supportedOptions : m_unsupportedOptions).insert(cacheKey);
  return supported;
}

void ColmapRunner::maybeAppendOption(QStringList &args, const QString &command,
                                     const QString &option,
                                     const QString &value) {
  if (supportsOption(command, option)) {
    args << option << value;
  }
}

void ColmapRunner::runFullPipeline() {
  m_cancelled = false;
  m_currentStep = 0;

  QString dbPath = m_workspacePath + "/database.db";
  QString sparsePath = m_workspacePath + "/sparse";
  QString densePath = m_workspacePath + "/dense";
  QDir(sparsePath).removeRecursively();
  QDir(densePath).removeRecursively();
  QDir().mkpath(sparsePath);
  QDir().mkpath(densePath);
  QFile::remove(dbPath);
  QFile::remove(m_workspacePath + "/model.ply");

  QStringList featureArgs = {
      "feature_extractor", "--database_path", dbPath, "--image_path",
      m_imagePath, "--ImageReader.single_camera", "1",
      "--ImageReader.camera_model", "PINHOLE",
      "--SiftExtraction.max_num_features", "8192"};
  maybeAppendOption(featureArgs, "feature_extractor",
                    "--SiftExtraction.use_gpu", "1");
  maybeAppendOption(featureArgs, "feature_extractor",
                    "--SiftExtraction.gpu_index", "0");

  QStringList matchingArgs = {
      "sequential_matcher", "--database_path", dbPath,
      "--SequentialMatching.overlap", "10",
      "--SequentialMatching.loop_detection", "1"};
  maybeAppendOption(matchingArgs, "sequential_matcher",
                    "--SiftMatching.use_gpu", "1");
  maybeAppendOption(matchingArgs, "sequential_matcher",
                    "--SiftMatching.gpu_index", "0");

  m_steps = {
      {"Feature Extraction",
       "",
       featureArgs},

      {"Feature Matching",
       "",
       matchingArgs},

      {"Sparse Reconstruction",
       "",
       {"mapper", "--database_path", dbPath, "--image_path", m_imagePath,
        "--output_path", sparsePath}},
  };

#if defined(Q_OS_WIN)
  if (m_denseEnabled) {
    QStringList denseStereoArgs = {
        "patch_match_stereo", "--workspace_path", densePath,
        "--workspace_format", "COLMAP",
        "--PatchMatchStereo.geom_consistency", "1"};
    maybeAppendOption(denseStereoArgs, "patch_match_stereo",
                      "--PatchMatchStereo.use_gpu", "1");
    maybeAppendOption(denseStereoArgs, "patch_match_stereo",
                      "--PatchMatchStereo.gpu_index", "0");

    m_steps.append({"Image Undistortion",
                    "",
                    {"image_undistorter", "--image_path", m_imagePath,
                     "--input_path", sparsePath + "/0", "--output_path",
                     densePath, "--output_type", "COLMAP"}});

    m_steps.append({"Dense Stereo (CUDA)",
                    "",
                    denseStereoArgs});

    m_steps.append({"Stereo Fusion",
                    "",
                    {"stereo_fusion", "--workspace_path", densePath,
                     "--workspace_format", "COLMAP", "--input_type",
                     "geometric", "--output_path", densePath + "/fused.ply"}});
  }
#else
  if (m_denseEnabled) {
    QString mvsPath = m_workspacePath + "/scene.mvs";

    m_steps.append({"Prepare OpenMVS Input",
                    "sh",
                    {"-c", QString("cp %1/0/* %1/").arg(sparsePath)}});

    m_steps.append(
        {"Convert to OpenMVS",
         "InterfaceCOLMAP",
         {"--input-file", m_workspacePath, "--image-folder", m_imagePath,
          "--output-file", mvsPath, "--working-folder", m_workspacePath}});

    // Remove stale depth maps from previous runs (size mismatch causes heap
    // corruption if resolution-level differs between runs)
    m_steps.append({"Clean Old Depth Maps",
                    "sh",
                    {"-c", QString("rm -f %1/depth*.dmap %1/dense*.mvs %1/*.ply")
                         .arg(m_workspacePath)}});

    m_steps.append({"Dense Reconstruction (CPU)",
                    "DensifyPointCloud",
                    {"--input-file", mvsPath, "--output-file",
                     m_workspacePath + "/dense.mvs", "--resolution-level", "1",
                     "--working-folder", m_workspacePath}});
  }
#endif

  runNextStep();
}

void ColmapRunner::runNextStep() {
  if (m_cancelled || m_currentStep >= m_steps.size()) {
    emit pipelineFinished(!m_cancelled);
    return;
  }
  startStep(m_steps[m_currentStep]);
}

void ColmapRunner::startStep(const PipelineStep &step) {
  emit stepStarted(step.name);

  if (step.name == "Sparse Reconstruction") {
    emit progressOutput(
        "[info] COLMAP mapper is CPU-only. GPU acceleration applies to SIFT "
        "extraction/matching and dense stereo.");
  } else if (step.name == "Stereo Fusion") {
    emit progressOutput(
        "[info] stereo_fusion is CPU-bound even when dense stereo used CUDA.");
  }

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

#ifdef Q_OS_WIN
  // On Windows, prefer the actual COLMAP executable directory first so an
  // externally selected build does not accidentally load mismatched DLLs from
  // the app bundle.
  {
    QString exe = step.exe.isEmpty() ? m_colmapPath : step.exe;
    QString exeDir = QFileInfo(exe).absolutePath();
    QString existingPath = env.value("PATH");
    QStringList pathEntries;
    if (!exeDir.isEmpty())
      pathEntries << QDir::toNativeSeparators(exeDir);
    if (QDir(toolsBase).exists())
      pathEntries << QDir::toNativeSeparators(toolsBase);
    if (!existingPath.isEmpty())
      pathEntries << existingPath;
    env.insert("PATH", pathEntries.join(';'));
  }
#else
  QString libPath = toolsBase + "/lib";
  if (QDir(libPath).exists()) {
    QString existing = env.value(libVar);
    env.insert(libVar, libPath + (existing.isEmpty() ? "" : ":" + existing));
  }
  QString binPath = toolsBase + "/bin";
  if (QDir(binPath).exists()) {
    QString existingPath = env.value("PATH");
    env.insert("PATH", binPath + (existingPath.isEmpty() ? "" : ":" + existingPath));
  }
#endif

  QString pluginPath = toolsBase + "/plugins";
  if (QDir(pluginPath).exists())
    env.insert("QT_PLUGIN_PATH", pluginPath);

  m_process->setProcessEnvironment(env);

  QString exe = step.exe.isEmpty() ? m_colmapPath : step.exe;
  emit progressOutput(QString("[cmd] %1 %2").arg(exe, step.args.join(' ')));
  m_process->start(exe, step.args);

  if (!m_process->waitForStarted(5000)) {
    emit errorOccurred(
        QString("Failed to start '%1': %2")
            .arg(exe, m_process->errorString()));
    emit pipelineFinished(false);
  }
}

void ColmapRunner::onProcessOutput() {
  QString out = QString::fromUtf8(m_process->readAllStandardOutput());
  QString err = QString::fromUtf8(m_process->readAllStandardError());

  if (!out.isEmpty())
    for (const QString &line : out.split('\n', Qt::SkipEmptyParts))
      emit progressOutput(line);

  if (!err.isEmpty())
    for (const QString &line : err.split('\n', Qt::SkipEmptyParts))
      emit progressOutput("[stderr] " + line);
}

void ColmapRunner::onProcessFinished(int exitCode,
                                     QProcess::ExitStatus status) {
  const QString &name = m_steps[m_currentStep].name;
  bool success = (status == QProcess::NormalExit && exitCode == 0);

  emit stepFinished(name, success);

  if (!success) {
    emit errorOccurred(
        QString("Step '%1' failed with exit code %2").arg(name).arg(exitCode));
    emit pipelineFinished(false);
    return;
  }

  m_currentStep++;
  runNextStep();
}

void ColmapRunner::cancel() {
  m_cancelled = true;
  if (m_process->state() != QProcess::NotRunning)
    m_process->kill();
}
