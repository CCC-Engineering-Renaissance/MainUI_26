#include "rovsetuppage.h"
#include "pilink.h"

#include <QComboBox>
#include <QCoreApplication>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QProcess>
#include <QPushButton>
#include <QRegularExpression>
#include <QSettings>
#include <QSpinBox>
#include <QStandardPaths>
#include <QVBoxLayout>

namespace {

const char *kOneServo = "oneservo";
const char *kCamera   = "camera";
const char *kBuild    = "build";

QString dotStyle(const QString &color)
{
    return QStringLiteral("color: %1; font-size: 16px;").arg(color);
}

QString lookColor(int look)
{
    switch (look) {
    case 2: case 3: return QStringLiteral("#00ff88");  // Running / Ok
    case 4:         return QStringLiteral("#ff4444");  // Failed
    case 1:         return QStringLiteral("#00ccff");  // Busy
    default:        return QStringLiteral("#888888");  // Idle / Offline
    }
}

} // namespace

RovSetupPage::RovSetupPage(QWidget *parent)
    : QWidget(parent)
{
    m_detect   = new TaskRunner(TaskRunner::Mode::OneShot,     this);
    m_thruster = new TaskRunner(TaskRunner::Mode::LongRunning, this);
    m_axis     = new TaskRunner(TaskRunner::Mode::LongRunning, this);
    m_pytest   = new TaskRunner(TaskRunner::Mode::OneShot,     this);
    m_piLink   = new PiLink(this);

    buildUi();
    loadSettings();

    // ── Local task rows ───────────────────────────────────────────────────
    wireLocalTask(m_detect,   &m_rowDetect,   QStringLiteral("detect"),
                  QStringLiteral("Scan"));
    wireLocalTask(m_thruster, &m_rowThruster, QStringLiteral("thruster"),
                  QStringLiteral("Start"));
    wireLocalTask(m_axis,     &m_rowAxis,     QStringLiteral("axistest"),
                  QStringLiteral("Start"));
    wireLocalTask(m_pytest,   &m_rowPytest,   QStringLiteral("pytest"),
                  QStringLiteral("Run"));

    // Detect: collect "  [0] Name | GUID: ..." lines, fill combos on success
    connect(m_detect, &TaskRunner::outputLine, this, [this](const QString &l) {
        static const QRegularExpression rx(
            QStringLiteral("^\\s*\\[(\\d+)\\]\\s+(.+?)\\s*(?:\\|.*)?$"));
        const auto m = rx.match(l);
        if (m.hasMatch())
            m_detectedPads.append({m.captured(1).toInt(), m.captured(2)});
    });
    connect(m_detect, &TaskRunner::stateChanged, this,
            [this](TaskRunner::State s, const QString &) {
        if (s == TaskRunner::State::Succeeded)
            populatePadCombos();
    });

    connect(m_rowDetect.button, &QPushButton::clicked, this, [this]() {
        if (m_detect->isActive())
            return;
        m_detectedPads.clear();
        startScript(m_detect, {QStringLiteral("test_controllers.py")},
                    QStringLiteral("detect"));
    });

    connect(m_rowThruster.button, &QPushButton::clicked, this, [this]() {
        if (m_thruster->isActive()) {
            m_thruster->stop();
            return;
        }
        const int rov  = m_rovCombo->currentData().toInt();
        const int claw = m_clawCombo->currentData().toInt();
        startScript(m_thruster,
                    {QStringLiteral("thruster.py"),
                     QStringLiteral("--rov-index"),  QString::number(rov),
                     QStringLiteral("--claw-index"), QString::number(claw)},
                    QStringLiteral("thruster"));
    });

    connect(m_rowAxis.button, &QPushButton::clicked, this, [this]() {
        if (m_axis->isActive())
            m_axis->stop();
        else
            startScript(m_axis, {QStringLiteral("axistest.py")},
                        QStringLiteral("axistest"));
    });

    connect(m_rowPytest.button, &QPushButton::clicked, this, [this]() {
        if (m_pytest->isActive())
            return;
        startScript(m_pytest,
                    {QStringLiteral("-m"), QStringLiteral("pytest"),
                     QStringLiteral("tests/"), QStringLiteral("-v")},
                    QStringLiteral("pytest"));
    });

    // ── Pi daemon rows ────────────────────────────────────────────────────
    connect(m_piLink, &PiLink::onlineChanged,
            this, &RovSetupPage::onPiOnlineChanged);
    connect(m_piLink, &PiLink::taskStateChanged,
            this, &RovSetupPage::onPiTaskState);
    connect(m_piLink, &PiLink::taskOutput,
            this, [this](const QString &task, const QString &line) {
        appendLog(task, line);
    });
    connect(m_piLink, &PiLink::commandFailed,
            this, [this](const QString &task, const QString &error) {
        appendLog(task.isEmpty() ? QStringLiteral("pi") : task,
                  QStringLiteral("error: %1").arg(error));
    });

    connect(m_rowOneServo.button, &QPushButton::clicked, this, [this]() {
        if (piTaskRunning(kOneServo)) {
            m_piLink->stopTask(kOneServo);
        } else {
            appendLog(kOneServo,
                      QStringLiteral("note: telemetry target IP is hardcoded as "
                                     "kTopsideIP in MAIN_CODE/src/main_One_Servo.cpp — "
                                     "if your laptop IP differs, edit it and run "
                                     "Build Firmware"));
            m_piLink->startTask(kOneServo);
        }
    });
    connect(m_rowCamera.button, &QPushButton::clicked, this, [this]() {
        if (piTaskRunning(kCamera))
            m_piLink->stopTask(kCamera);
        else
            m_piLink->startTask(kCamera);
    });
    connect(m_rowBuild.button, &QPushButton::clicked, this, [this]() {
        if (!piTaskRunning(kBuild))
            m_piLink->startTask(kBuild);
    });

    connect(m_sshButton, &QPushButton::clicked,
            this, &RovSetupPage::openSshTerminal);

    onPiOnlineChanged(false);
    refreshLocalGating();
    applyConnection();
}

void RovSetupPage::shutdownAll()
{
    saveSettings();
    for (TaskRunner *r : {m_detect, m_thruster, m_axis, m_pytest})
        if (r->isActive())
            r->stop();
    // TaskRunner destructors wait for the children when the page is destroyed.
}

// ─────────────────────────────────────────────────────────────────────────────
// UI construction
// ─────────────────────────────────────────────────────────────────────────────

void RovSetupPage::buildUi()
{
    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(12, 4, 12, 12);
    root->setSpacing(10);

    auto *title = new QLabel(QStringLiteral("ROV Setup"));
    QFont titleFont = title->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    title->setFont(titleFont);
    root->addWidget(title);

    auto *columns = new QHBoxLayout();
    columns->setSpacing(14);
    root->addLayout(columns, 1);

    // ── Left column ───────────────────────────────────────────────────────
    auto *left = new QVBoxLayout();
    columns->addLayout(left, 1);

    auto *padsBox  = new QGroupBox(QStringLiteral("Controllers"));
    auto *padsGrid = new QGridLayout(padsBox);
    m_rowDetect = addTaskRow(padsGrid, 0, QStringLiteral("Detect Controllers"),
                             QStringLiteral("Scan"));
    m_rovCombo  = new QComboBox();
    m_clawCombo = new QComboBox();
    m_rovCombo->setPlaceholderText(QStringLiteral("scan first"));
    m_clawCombo->setPlaceholderText(QStringLiteral("scan first"));
    padsGrid->addWidget(new QLabel(QStringLiteral("ROV pad:")),  1, 0);
    padsGrid->addWidget(m_rovCombo,  1, 1, 1, 3);
    padsGrid->addWidget(new QLabel(QStringLiteral("Claw pad:")), 2, 0);
    padsGrid->addWidget(m_clawCombo, 2, 1, 1, 3);
    left->addWidget(padsBox);

    auto *localBox  = new QGroupBox(QStringLiteral("Local Tasks"));
    auto *localGrid = new QGridLayout(localBox);
    m_rowThruster = addTaskRow(localGrid, 0,
                               QStringLiteral("Thruster Control (thruster.py)"),
                               QStringLiteral("Start"));
    m_rowAxis     = addTaskRow(localGrid, 1,
                               QStringLiteral("Axis Test (axistest.py)"),
                               QStringLiteral("Start"));
    m_rowPytest   = addTaskRow(localGrid, 2,
                               QStringLiteral("Unit Tests (pytest)"),
                               QStringLiteral("Run"));
    left->addWidget(localBox);
    left->addStretch(1);

    // ── Right column ──────────────────────────────────────────────────────
    auto *right = new QVBoxLayout();
    columns->addLayout(right, 1);

    auto *piBox  = new QGroupBox(QStringLiteral("Raspberry Pi"));
    auto *piVBox = new QVBoxLayout(piBox);

    auto *daemonRow = new QHBoxLayout();
    daemonRow->addWidget(new QLabel(QStringLiteral("Daemon:")));
    m_daemonDot = new QLabel(QStringLiteral("●"));
    m_daemonDot->setStyleSheet(dotStyle(QStringLiteral("#ff4444")));
    m_daemonStatus = new QLabel(QStringLiteral("Offline"));
    daemonRow->addWidget(m_daemonDot);
    daemonRow->addWidget(m_daemonStatus);
    daemonRow->addStretch(1);
    piVBox->addLayout(daemonRow);

    auto *piGrid = new QGridLayout();
    m_rowOneServo = addTaskRow(piGrid, 0,
                               QStringLiteral("Thruster Firmware (OneServo)"),
                               QStringLiteral("Start"));
    m_rowCamera   = addTaskRow(piGrid, 1,
                               QStringLiteral("Camera Server (camera_server.py)"),
                               QStringLiteral("Start"));
    m_rowBuild    = addTaskRow(piGrid, 2,
                               QStringLiteral("Build Firmware (make OneServo)"),
                               QStringLiteral("Run"));
    piVBox->addLayout(piGrid);

    m_sshButton = new QPushButton(QStringLiteral("Open SSH Terminal"));
    piVBox->addWidget(m_sshButton, 0, Qt::AlignLeft);
    right->addWidget(piBox);

    auto *connBox  = new QGroupBox(QStringLiteral("Connection Settings"));
    auto *connForm = new QFormLayout(connBox);
    m_piHost     = new QLineEdit();
    m_piUser     = new QLineEdit();
    m_remotePath = new QLineEdit();
    m_daemonPort = new QSpinBox();
    m_daemonPort->setRange(1024, 65535);
    m_localPath  = new QLineEdit();
    m_python     = new QLineEdit();
    m_python->setPlaceholderText(QStringLiteral("(auto)"));

    auto *localPathRow = new QHBoxLayout();
    localPathRow->addWidget(m_localPath, 1);
    auto *browse = new QPushButton(QStringLiteral("Browse…"));
    localPathRow->addWidget(browse);
    connect(browse, &QPushButton::clicked, this, [this]() {
        const QString dir = QFileDialog::getExistingDirectory(
            this, QStringLiteral("Select Control-Systems-Code folder"),
            m_localPath->text());
        if (!dir.isEmpty()) {
            m_localPath->setText(dir);
            refreshLocalGating();
        }
    });

    connForm->addRow(QStringLiteral("Pi host:"),       m_piHost);
    connForm->addRow(QStringLiteral("Pi user:"),       m_piUser);
    connForm->addRow(QStringLiteral("Remote path:"),   m_remotePath);
    connForm->addRow(QStringLiteral("Daemon port:"),   m_daemonPort);
    connForm->addRow(QStringLiteral("Local scripts:"), localPathRow);
    connForm->addRow(QStringLiteral("Python:"),        m_python);

    auto *apply = new QPushButton(QStringLiteral("Apply && Reconnect"));
    connForm->addRow(QString(), apply);
    connect(apply, &QPushButton::clicked, this, [this]() {
        applyConnection();
        refreshLocalGating();
        appendLog(QStringLiteral("setup"),
                  QStringLiteral("settings applied — connecting to %1:%2")
                      .arg(m_piHost->text().trimmed())
                      .arg(m_daemonPort->value()));
    });

    right->addWidget(connBox);
    right->addStretch(1);

    // ── Shared log pane ───────────────────────────────────────────────────
    m_log = new QPlainTextEdit();
    m_log->setReadOnly(true);
    m_log->setMaximumBlockCount(2000);
    m_log->setMinimumHeight(140);
    m_log->setStyleSheet(QStringLiteral(
        "QPlainTextEdit { background-color: #0a1420; color: #cfe8ff;"
        " font-family: monospace; font-size: 11px; }"));
    root->addWidget(m_log);
}

RovSetupPage::TaskRow RovSetupPage::addTaskRow(QGridLayout *grid, int row,
                                               const QString &title,
                                               const QString &buttonText)
{
    TaskRow r;
    auto *name = new QLabel(title);
    r.button = new QPushButton(buttonText);
    r.button->setMinimumWidth(90);
    r.dot    = new QLabel(QStringLiteral("●"));
    r.dot->setStyleSheet(dotStyle(QStringLiteral("#888888")));
    r.status = new QLabel(QStringLiteral("idle"));
    r.status->setMinimumWidth(110);

    grid->addWidget(name,     row, 0);
    grid->addWidget(r.button, row, 1);
    grid->addWidget(r.dot,    row, 2);
    grid->addWidget(r.status, row, 3);
    grid->setColumnStretch(0, 1);
    return r;
}

void RovSetupPage::setRow(const TaskRow &row, Look look, const QString &text,
                          const QString &buttonText, bool buttonEnabled)
{
    row.dot->setStyleSheet(dotStyle(lookColor(static_cast<int>(look))));
    row.status->setText(text);
    row.button->setText(buttonText);
    row.button->setEnabled(buttonEnabled);
}

void RovSetupPage::appendLog(const QString &tag, const QString &line)
{
    m_log->appendPlainText(QStringLiteral("[%1] %2").arg(tag, line));
}

void RovSetupPage::wireLocalTask(TaskRunner *runner, TaskRow *row,
                                 const QString &tag,
                                 const QString &idleButtonText)
{
    connect(runner, &TaskRunner::outputLine, this,
            [this, tag](const QString &l) { appendLog(tag, l); });

    connect(runner, &TaskRunner::stateChanged, this,
            [this, row, idleButtonText](TaskRunner::State s, const QString &d) {
        switch (s) {
        case TaskRunner::State::Idle:
            setRow(*row, Look::Idle, d.isEmpty() ? QStringLiteral("idle") : d,
                   idleButtonText, true);
            break;
        case TaskRunner::State::Starting:
            setRow(*row, Look::Busy, QStringLiteral("starting…"),
                   idleButtonText, false);
            break;
        case TaskRunner::State::Running:
            setRow(*row, Look::Running, QStringLiteral("running"),
                   QStringLiteral("Stop"), true);
            break;
        case TaskRunner::State::Stopping:
            setRow(*row, Look::Busy, QStringLiteral("stopping…"),
                   QStringLiteral("Stop"), false);
            break;
        case TaskRunner::State::Succeeded:
            setRow(*row, Look::Ok, QStringLiteral("ok"),
                   idleButtonText, true);
            break;
        case TaskRunner::State::Failed:
            setRow(*row, Look::Failed,
                   d.isEmpty() ? QStringLiteral("failed") : d,
                   idleButtonText, true);
            break;
        }
        refreshLocalGating();
    });
}

// ─────────────────────────────────────────────────────────────────────────────
// Local script launching
// ─────────────────────────────────────────────────────────────────────────────

bool RovSetupPage::startScript(TaskRunner *runner, const QStringList &scriptArgs,
                               const QString &tag)
{
    if (!scriptsDirValid()) {
        appendLog(tag, QStringLiteral("set a valid Control-Systems-Code folder "
                                      "in Connection Settings first"));
        return false;
    }
    QStringList pre;
    const QString prog = pythonProgram(&pre);
    if (prog.isEmpty()) {
        appendLog(tag, QStringLiteral("no Python interpreter found — set one in "
                                      "Connection Settings"));
        return false;
    }
    runner->setWorkingDirectory(scriptsDir());
    runner->setCommand(prog, pre + QStringList{QStringLiteral("-u")} + scriptArgs);
    return runner->start();
}

QString RovSetupPage::pythonProgram(QStringList *preArgs) const
{
    preArgs->clear();
    const QString overridePath = m_python->text().trimmed();
    if (!overridePath.isEmpty())
        return overridePath;

    // Prefer a relocatable Python runtime bundled next to the binary (so the
    // scripts run with no system Python install); fall back to system Python.
    const QString appDir = QCoreApplication::applicationDirPath();
#if defined(Q_OS_WIN)
    const QString bundledPy = QDir(appDir).filePath(QStringLiteral("python/python.exe"));
#else
    const QString bundledPy = QDir(appDir).filePath(QStringLiteral("python/bin/python3"));
#endif
    if (QFileInfo(bundledPy).isExecutable())
        return bundledPy;

#if defined(Q_OS_WIN)
    const QString py = QStandardPaths::findExecutable(QStringLiteral("py"));
    if (!py.isEmpty()) {
        *preArgs << QStringLiteral("-3");
        return py;
    }
    return QStandardPaths::findExecutable(QStringLiteral("python"));
#else
    const QString p3 = QStandardPaths::findExecutable(QStringLiteral("python3"));
    if (!p3.isEmpty())
        return p3;
    return QStandardPaths::findExecutable(QStringLiteral("python"));
#endif
}

QString RovSetupPage::scriptsDir() const
{
    // A developer-configured checkout that actually contains the scripts wins;
    // otherwise fall back to the copy bundled next to the binary.
    const QString configured = m_localPath->text().trimmed();
    if (!configured.isEmpty()
        && QFileInfo(QDir(configured).filePath(QStringLiteral("thruster.py"))).isFile())
        return configured;

    const QString bundled =
        QDir(QCoreApplication::applicationDirPath()).filePath(QStringLiteral("scripts"));
    if (QFileInfo(QDir(bundled).filePath(QStringLiteral("thruster.py"))).isFile())
        return bundled;

    return configured;
}

bool RovSetupPage::scriptsDirValid() const
{
    return QFileInfo(QDir(scriptsDir()).filePath(QStringLiteral("thruster.py")))
        .isFile();
}

void RovSetupPage::refreshLocalGating()
{
    const bool dirOk = scriptsDirValid();
    const auto gate = [&](TaskRunner *r, const TaskRow &row, bool extra = true) {
        if (!r->isActive())
            row.button->setEnabled(dirOk && extra);
    };
    gate(m_detect, m_rowDetect);
    gate(m_axis,   m_rowAxis);
    gate(m_pytest, m_rowPytest);

    const bool padsOk = m_rovCombo->count() > 0 && m_clawCombo->count() > 0 &&
                        m_rovCombo->currentIndex() >= 0 &&
                        m_clawCombo->currentIndex() >= 0 &&
                        m_rovCombo->currentData() != m_clawCombo->currentData();
    gate(m_thruster, m_rowThruster, padsOk);
}

void RovSetupPage::populatePadCombos()
{
    m_rovCombo->clear();
    m_clawCombo->clear();
    for (const auto &pad : m_detectedPads) {
        const QString label = QStringLiteral("%1: %2").arg(pad.first).arg(pad.second);
        m_rovCombo->addItem(label, pad.first);
        m_clawCombo->addItem(label, pad.first);
    }

    const int rovAt  = m_rovCombo->findData(m_savedRovIdx);
    const int clawAt = m_clawCombo->findData(m_savedClawIdx);
    if (rovAt >= 0)
        m_rovCombo->setCurrentIndex(rovAt);
    if (clawAt >= 0 && clawAt != m_rovCombo->currentIndex())
        m_clawCombo->setCurrentIndex(clawAt);
    else if (m_clawCombo->count() > 1)
        m_clawCombo->setCurrentIndex(m_rovCombo->currentIndex() == 1 ? 0 : 1);

    if (m_detectedPads.isEmpty())
        appendLog(QStringLiteral("detect"),
                  QStringLiteral("no controllers found — plug pads in and scan "
                                 "again"));
    refreshLocalGating();
}

// ─────────────────────────────────────────────────────────────────────────────
// Settings
// ─────────────────────────────────────────────────────────────────────────────

void RovSetupPage::loadSettings()
{
    QSettings s;
    s.beginGroup(QStringLiteral("rovsetup"));
    m_piHost->setText(s.value(QStringLiteral("piHost"),
                              QStringLiteral("192.168.8.128")).toString());
    m_piUser->setText(s.value(QStringLiteral("piUser"),
                              QStringLiteral("pi")).toString());
    m_remotePath->setText(s.value(QStringLiteral("piRemotePath"),
                                  QStringLiteral("~/Control-Systems-Code")).toString());
    m_daemonPort->setValue(s.value(QStringLiteral("daemonPort"), 5010).toInt());

    QString defaultLocal = QDir::homePath() + QStringLiteral("/Projects/Control-Systems-Code");
    if (!QFileInfo::exists(defaultLocal))
        defaultLocal.clear();
    m_localPath->setText(s.value(QStringLiteral("localScriptsPath"),
                                 defaultLocal).toString());
    m_python->setText(s.value(QStringLiteral("pythonOverride")).toString());
    m_savedRovIdx  = s.value(QStringLiteral("rovIndex"),  -1).toInt();
    m_savedClawIdx = s.value(QStringLiteral("clawIndex"), -1).toInt();
    s.endGroup();

    connect(m_rovCombo,  &QComboBox::currentIndexChanged, this, [this](int) {
        if (m_rovCombo->currentIndex() >= 0)
            m_savedRovIdx = m_rovCombo->currentData().toInt();
        refreshLocalGating();
    });
    connect(m_clawCombo, &QComboBox::currentIndexChanged, this, [this](int) {
        if (m_clawCombo->currentIndex() >= 0)
            m_savedClawIdx = m_clawCombo->currentData().toInt();
        refreshLocalGating();
    });
}

void RovSetupPage::saveSettings()
{
    QSettings s;
    s.beginGroup(QStringLiteral("rovsetup"));
    s.setValue(QStringLiteral("piHost"),           m_piHost->text().trimmed());
    s.setValue(QStringLiteral("piUser"),           m_piUser->text().trimmed());
    s.setValue(QStringLiteral("piRemotePath"),     m_remotePath->text().trimmed());
    s.setValue(QStringLiteral("daemonPort"),       m_daemonPort->value());
    s.setValue(QStringLiteral("localScriptsPath"), m_localPath->text().trimmed());
    s.setValue(QStringLiteral("pythonOverride"),   m_python->text().trimmed());
    s.setValue(QStringLiteral("rovIndex"),         m_savedRovIdx);
    s.setValue(QStringLiteral("clawIndex"),        m_savedClawIdx);
    s.endGroup();
}

void RovSetupPage::applyConnection()
{
    saveSettings();
    m_piLink->configure(m_piHost->text().trimmed(),
                        static_cast<quint16>(m_daemonPort->value()));
}

// ─────────────────────────────────────────────────────────────────────────────
// SSH terminal fallback
// ─────────────────────────────────────────────────────────────────────────────

void RovSetupPage::openSshTerminal()
{
    const QString target = m_piUser->text().trimmed() + QLatin1Char('@') +
                           m_piHost->text().trimmed();
#if defined(Q_OS_WIN)
    const bool ok = QProcess::startDetached(
        QStringLiteral("cmd.exe"),
        {QStringLiteral("/c"), QStringLiteral("start"), QString(),
         QStringLiteral("ssh"), target});
#elif defined(Q_OS_MACOS)
    const bool ok = QProcess::startDetached(
        QStringLiteral("osascript"),
        {QStringLiteral("-e"),
         QStringLiteral("tell application \"Terminal\" to do script \"ssh %1\"")
             .arg(target),
         QStringLiteral("-e"),
         QStringLiteral("tell application \"Terminal\" to activate")});
#else
    bool ok = false;
    struct Candidate { const char *exe; QStringList args; };
    const QList<Candidate> candidates = {
        {"x-terminal-emulator", {QStringLiteral("-e"),
                                 QStringLiteral("ssh %1").arg(target)}},
        {"gnome-terminal",      {QStringLiteral("--"), QStringLiteral("ssh"),
                                 target}},
        {"konsole",             {QStringLiteral("-e"), QStringLiteral("ssh"),
                                 target}},
        {"xfce4-terminal",      {QStringLiteral("-e"),
                                 QStringLiteral("ssh %1").arg(target)}},
        {"xterm",               {QStringLiteral("-e"), QStringLiteral("ssh"),
                                 target}},
    };
    for (const Candidate &c : candidates) {
        const QString exe =
            QStandardPaths::findExecutable(QString::fromLatin1(c.exe));
        if (!exe.isEmpty()) {
            ok = QProcess::startDetached(exe, c.args);
            if (ok)
                break;
        }
    }
#endif
    appendLog(QStringLiteral("ssh"),
              ok ? QStringLiteral("opened terminal: ssh %1").arg(target)
                 : QStringLiteral("could not launch a terminal emulator — run "
                                  "\"ssh %1\" manually").arg(target));
}

// ─────────────────────────────────────────────────────────────────────────────
// Pi daemon state → UI
// ─────────────────────────────────────────────────────────────────────────────

void RovSetupPage::onPiOnlineChanged(bool online)
{
    m_daemonDot->setStyleSheet(dotStyle(online ? QStringLiteral("#00ff88")
                                               : QStringLiteral("#ff4444")));
    m_daemonStatus->setText(online ? QStringLiteral("Online")
                                   : QStringLiteral("Offline"));
    if (!online) {
        m_piState.clear();
        for (const QString task : {kOneServo, kCamera, kBuild})
            setRow(*piRow(task), Look::Offline, QStringLiteral("offline"),
                   piIdleButtonText(task), false);
    }
    // When the daemon comes online, the next status poll repopulates the rows.
}

void RovSetupPage::onPiTaskState(const QString &task, const QString &state,
                                 int exitCode)
{
    TaskRow *row = piRow(task);
    if (!row)
        return;
    m_piState[task] = state;

    if (state == QLatin1String("running")) {
        setRow(*row, Look::Running, QStringLiteral("running"),
               QStringLiteral("Stop"), true);
    } else if (state == QLatin1String("idle")) {
        setRow(*row, Look::Idle, QStringLiteral("idle"),
               piIdleButtonText(task), true);
    } else if (state == QLatin1String("exited")) {
        if (task == QLatin1String(kBuild)) {
            if (exitCode == 0)
                setRow(*row, Look::Ok, QStringLiteral("ok"),
                       QStringLiteral("Run again"), true);
            else
                setRow(*row, Look::Failed,
                       QStringLiteral("exit %1").arg(exitCode),
                       piIdleButtonText(task), true);
        } else {
            if (exitCode == 0)
                setRow(*row, Look::Idle, QStringLiteral("stopped"),
                       piIdleButtonText(task), true);
            else
                setRow(*row, Look::Failed,
                       QStringLiteral("exited (%1)").arg(exitCode),
                       piIdleButtonText(task), true);
        }
    }
}

RovSetupPage::TaskRow *RovSetupPage::piRow(const QString &task)
{
    if (task == QLatin1String(kOneServo)) return &m_rowOneServo;
    if (task == QLatin1String(kCamera))   return &m_rowCamera;
    if (task == QLatin1String(kBuild))    return &m_rowBuild;
    return nullptr;
}

QString RovSetupPage::piIdleButtonText(const QString &task) const
{
    return task == QLatin1String(kBuild) ? QStringLiteral("Run")
                                         : QStringLiteral("Start");
}

bool RovSetupPage::piTaskRunning(const QString &task) const
{
    return m_piState.value(task) == QLatin1String("running");
}
