#pragma once

#include <QAbstractSocket>
#include <QByteArray>
#include <QImage>
#include <QObject>
#include <QTcpSocket>
#include <QTimer>

/**
 * CameraReceiver
 * ==============
 * Connects to the ROV Pi camera server over two TCP sockets:
 *   - Stream socket  (Pi → GUI): receives length-prefixed JPEG frames
 *   - Command socket (GUI → Pi): sends camera-switch commands
 *
 * Stream protocol (server → client):
 *   [4-byte big-endian uint32: JPEG byte count][JPEG bytes]   (loops forever)
 *
 * Command protocol (client → server):
 *   "CMD:<name>\n"  where <name> is one of: front, left, right, bot, back
 *
 * Default Pi IP / ports:
 *   Change PI_DEFAULT_HOST below to match your ROV's Ethernet address.
 *   Ports 5000 (stream) and 5001 (commands) must match camera_server.py.
 */

// ---------------------------------------------------------------------------
// ROV network configuration – adjust to match your setup
// ---------------------------------------------------------------------------
static constexpr char PI_DEFAULT_HOST[] = "192.168.8.128";
static constexpr quint16 CAM_STREAM_PORT = 5000;
static constexpr quint16 CAM_COMMAND_PORT = 5001;
// ---------------------------------------------------------------------------

class CameraReceiver : public QObject {
  Q_OBJECT

public:
  explicit CameraReceiver(QObject *parent = nullptr);

  /** Connect to the Pi camera server. */
  void connectToHost(const QString &host = PI_DEFAULT_HOST,
                     quint16 streamPort = CAM_STREAM_PORT,
                     quint16 commandPort = CAM_COMMAND_PORT);

  /** Gracefully disconnect from the Pi. */
  void disconnectFromHost();

  /** Send a camera-switch command ("front" | "left" | "right" | "bot" |
   * "back"). */
  void switchCamera(const QString &cameraName);

  bool isConnected() const;

signals:
  /** Emitted for every decoded frame – safe to use directly in the GUI thread.
   */
  void frameReady(const QImage &image);

  void connected();
  void disconnected();

  /** Emitted once per second with the number of frames received that second. */
  void fpsUpdated(int fps);

private slots:
  void onStreamConnected();
  void onStreamDisconnected();
  void onStreamReadyRead();
  void onStreamError(QAbstractSocket::SocketError error);
  void onFpsTimerTick();

private:
  QTcpSocket *m_streamSocket = nullptr;
  QTcpSocket *m_commandSocket = nullptr;

  QByteArray m_buffer;
  qint32 m_pendingBytes = -1; // -1 = waiting for 4-byte header

  QString m_host;
  quint16 m_streamPort = CAM_STREAM_PORT;
  quint16 m_commandPort = CAM_COMMAND_PORT;

  QTimer *m_fpsTimer = nullptr;
  int m_frameCount = 0;
};
