#include "taskrunner.h"

#include <QTimer>

TaskRunner::TaskRunner(Mode mode, QObject *parent)
    : QObject(parent)
    , m_process(new QProcess(this))
    , m_killTimer(new QTimer(this))
    , m_mode(mode)
{
    m_process->setProcessChannelMode(QProcess::MergedChannels);

    m_killTimer->setSingleShot(true);
    m_killTimer->setInterval(3000);
    connect(m_killTimer, &QTimer::timeout, this, [this]() {
        if (m_process->state() != QProcess::NotRunning)
            m_process->kill();
    });

    connect(m_process, &QProcess::started,
            this, &TaskRunner::onStarted);
    connect(m_process, &QProcess::readyReadStandardOutput,
            this, &TaskRunner::onReadyRead);
    connect(m_process, &QProcess::finished,
            this, &TaskRunner::onFinished);
    connect(m_process, &QProcess::errorOccurred,
            this, &TaskRunner::onErrorOccurred);
}

TaskRunner::~TaskRunner()
{
    // Don't emit state changes into a half-destroyed owner.
    m_process->disconnect();
    if (m_process->state() != QProcess::NotRunning) {
        m_process->terminate();
        if (!m_process->waitForFinished(1500)) {
            m_process->kill();
            m_process->waitForFinished(500);
        }
    }
}

void TaskRunner::setCommand(const QString &program, const QStringList &args)
{
    m_program = program;
    m_args    = args;
}

void TaskRunner::setWorkingDirectory(const QString &dir)
{
    m_workDir = dir;
}

bool TaskRunner::start()
{
    if (isActive() || m_program.isEmpty())
        return false;

    m_buffer.clear();
    setState(State::Starting);
    m_process->setWorkingDirectory(m_workDir);
    m_process->start(m_program, m_args);
    return true;
}

void TaskRunner::stop()
{
    if (m_state != State::Starting && m_state != State::Running)
        return;

    setState(State::Stopping);
    m_process->terminate();
    m_killTimer->start();
}

void TaskRunner::onStarted()
{
    setState(State::Running);
}

void TaskRunner::onReadyRead()
{
    m_buffer += m_process->readAll();
    int idx;
    while ((idx = m_buffer.indexOf('\n')) != -1) {
        QByteArray line = m_buffer.left(idx);
        if (line.endsWith('\r'))
            line.chop(1);
        m_buffer.remove(0, idx + 1);
        emit outputLine(QString::fromUtf8(line));
    }
}

void TaskRunner::onFinished(int exitCode, QProcess::ExitStatus status)
{
    m_killTimer->stop();
    onReadyRead();
    flushBuffer();

    const bool cleanExit  = (status == QProcess::NormalExit && exitCode == 0);
    const bool wasStopped = (m_state == State::Stopping);

    if (m_mode == Mode::OneShot) {
        if (wasStopped)
            setState(State::Idle, QStringLiteral("cancelled"));
        else if (cleanExit)
            setState(State::Succeeded, QStringLiteral("exit 0"));
        else if (status == QProcess::CrashExit)
            setState(State::Failed, QStringLiteral("crashed"));
        else
            setState(State::Failed, QStringLiteral("exit %1").arg(exitCode));
    } else {
        if (wasStopped)
            setState(State::Idle, QStringLiteral("stopped"));
        else if (cleanExit)
            setState(State::Idle, QStringLiteral("exited"));
        else if (status == QProcess::CrashExit)
            setState(State::Failed, QStringLiteral("crashed"));
        else
            setState(State::Failed,
                     QStringLiteral("exited unexpectedly (code %1)").arg(exitCode));
    }
}

void TaskRunner::onErrorOccurred(QProcess::ProcessError error)
{
    // Crash/abnormal-exit cases are reported through onFinished.
    if (error != QProcess::FailedToStart)
        return;

    m_killTimer->stop();
    setState(State::Failed,
             QStringLiteral("failed to start: %1").arg(m_process->errorString()));
}

void TaskRunner::setState(State s, const QString &detail)
{
    if (m_state == s && detail.isEmpty())
        return;
    m_state = s;
    emit stateChanged(s, detail);
}

void TaskRunner::flushBuffer()
{
    if (m_buffer.isEmpty())
        return;
    QByteArray line = m_buffer;
    if (line.endsWith('\r'))
        line.chop(1);
    m_buffer.clear();
    emit outputLine(QString::fromUtf8(line));
}
