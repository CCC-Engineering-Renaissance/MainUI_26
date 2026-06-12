#pragma once
#include <QHash>
#include <QList>
#include <QPair>
#include <QWidget>

#include "taskrunner.h"

class PiLink;
class QComboBox;
class QGridLayout;
class QLabel;
class QLineEdit;
class QPlainTextEdit;
class QPushButton;
class QSpinBox;

// "ROV Setup" submenu page: one row per setup task (local python scripts via
// TaskRunner, Pi-side tasks via the pi_launcher.py daemon through PiLink),
// each with a start/stop button and a colored status indicator, plus
// connection settings and a shared log pane.
class RovSetupPage : public QWidget {
  Q_OBJECT

public:
  explicit RovSetupPage(QWidget *parent = nullptr);

  // Stop local child processes (called on GUI exit). Pi-side tasks are
  // deliberately left running so the ROV survives a GUI restart mid-mission.
  void shutdownAll();

private:
  struct TaskRow {
    QPushButton *button = nullptr;
    QLabel      *dot    = nullptr;
    QLabel      *status = nullptr;
  };
  enum class Look { Idle, Busy, Running, Ok, Failed, Offline };

  void buildUi();
  TaskRow addTaskRow(QGridLayout *grid, int row, const QString &title,
                     const QString &buttonText);
  void setRow(const TaskRow &row, Look look, const QString &text,
              const QString &buttonText, bool buttonEnabled);
  void appendLog(const QString &tag, const QString &line);
  void wireLocalTask(TaskRunner *runner, TaskRow *row, const QString &tag,
                     const QString &idleButtonText);

  bool startScript(TaskRunner *runner, const QStringList &scriptArgs,
                   const QString &tag);
  QString pythonProgram(QStringList *preArgs) const;
  QString scriptsDir() const;
  bool scriptsDirValid() const;
  void refreshLocalGating();
  void populatePadCombos();

  void loadSettings();
  void saveSettings();
  void applyConnection();
  void openSshTerminal();

  void onPiOnlineChanged(bool online);
  void onPiTaskState(const QString &task, const QString &state, int exitCode);
  TaskRow *piRow(const QString &task);
  QString piIdleButtonText(const QString &task) const;
  bool piTaskRunning(const QString &task) const;

  // Local task runners
  TaskRunner *m_detect   = nullptr;
  TaskRunner *m_thruster = nullptr;
  TaskRunner *m_axis     = nullptr;
  TaskRunner *m_pytest   = nullptr;

  // Task rows
  TaskRow m_rowDetect, m_rowThruster, m_rowAxis, m_rowPytest;
  TaskRow m_rowOneServo, m_rowCamera, m_rowBuild;

  // Pi daemon link
  PiLink *m_piLink       = nullptr;
  QLabel *m_daemonDot    = nullptr;
  QLabel *m_daemonStatus = nullptr;
  QPushButton *m_sshButton = nullptr;
  QHash<QString, QString> m_piState;

  // Controllers
  QComboBox *m_rovCombo  = nullptr;
  QComboBox *m_clawCombo = nullptr;
  QList<QPair<int, QString>> m_detectedPads;
  int m_savedRovIdx  = -1;
  int m_savedClawIdx = -1;

  // Connection settings
  QLineEdit *m_piHost     = nullptr;
  QLineEdit *m_piUser     = nullptr;
  QLineEdit *m_remotePath = nullptr;
  QSpinBox  *m_daemonPort = nullptr;
  QLineEdit *m_localPath  = nullptr;
  QLineEdit *m_python     = nullptr;

  QPlainTextEdit *m_log = nullptr;
};
