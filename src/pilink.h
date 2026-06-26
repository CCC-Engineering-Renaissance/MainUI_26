#pragma once
#include <QAbstractSocket>
#include <QByteArray>
#include <QHash>
#include <QObject>
#include <QString>
#include <QStringList>

class QTcpSocket;
class QTimer;
class QJsonObject;

// Client for the pi_launcher.py daemon: newline-delimited JSON over TCP.
// Poll-based — requests a status snapshot every 2 s plus incremental output
// tails per task, and reconnects automatically when the link drops.
class PiLink : public QObject {
  Q_OBJECT

public:
  explicit PiLink(QObject *parent = nullptr);

  void configure(const QString &host, quint16 port);
  bool isOnline() const { return m_online; }

  void startTask(const QString &task);
  void stopTask(const QString &task);

signals:
  void onlineChanged(bool online);
  void taskStateChanged(const QString &task, const QString &state, int exitCode);
  void taskOutput(const QString &task, const QString &line);
  void commandFailed(const QString &task, const QString &error);

private slots:
  void onConnected();
  void onDisconnected();
  void onSocketError(QAbstractSocket::SocketError error);
  void onReadyRead();
  void poll();

private:
  void sendJson(const QJsonObject &obj);
  void handleReply(const QJsonObject &obj);
  void setOnline(bool online);
  void scheduleReconnect();

  QTcpSocket *m_sock;
  QTimer     *m_pollTimer;       // 2 s status + tail
  QTimer     *m_reconnectTimer;  // 3 s retry
  QString     m_host;
  quint16     m_port = 5010;
  QByteArray  m_rx;
  QHash<QString, qint64> m_tailSeq;
  bool        m_online = false;
  bool        m_errorLogged = false;  // throttle error spam during reconnect loop

  const QStringList m_tasks{QStringLiteral("oneservo"),
                            QStringLiteral("camera"),
                            QStringLiteral("build")};
};
