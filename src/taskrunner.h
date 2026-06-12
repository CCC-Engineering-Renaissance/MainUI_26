#pragma once
#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>

class QTimer;

// Generic wrapper around a single external process (python script, etc.)
// with a small state machine suitable for driving a start/stop button and
// a status indicator. Modeled on ColmapRunner.
class TaskRunner : public QObject {
  Q_OBJECT

public:
  enum class Mode  { LongRunning, OneShot };
  enum class State { Idle, Starting, Running, Stopping, Succeeded, Failed };
  Q_ENUM(State)

  explicit TaskRunner(Mode mode, QObject *parent = nullptr);
  ~TaskRunner() override;

  void setCommand(const QString &program, const QStringList &args);
  void setWorkingDirectory(const QString &dir);

  bool start();   // refuses (returns false) while active
  void stop();    // terminate() now, kill() after 3 s

  State state() const { return m_state; }
  bool isActive() const {
    return m_state == State::Starting || m_state == State::Running ||
           m_state == State::Stopping;
  }

signals:
  void stateChanged(TaskRunner::State state, const QString &detail);
  void outputLine(const QString &line);   // merged stdout+stderr, per line

private slots:
  void onStarted();
  void onReadyRead();
  void onFinished(int exitCode, QProcess::ExitStatus status);
  void onErrorOccurred(QProcess::ProcessError error);

private:
  void setState(State s, const QString &detail = QString());
  void flushBuffer();

  QProcess   *m_process;
  QTimer     *m_killTimer;
  Mode        m_mode;
  State       m_state = State::Idle;
  QString     m_program;
  QStringList m_args;
  QString     m_workDir;
  QByteArray  m_buffer;
};
