#include "camerareceiver.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
CameraReceiver::CameraReceiver(QObject *parent)
    : QObject(parent)
{
    m_streamSocket = new QTcpSocket(this);
    m_commandSocket = new QTcpSocket(this);

    connect(m_streamSocket, &QTcpSocket::connected, this, &CameraReceiver::onStreamConnected);
    connect(m_streamSocket, &QTcpSocket::disconnected, this, &CameraReceiver::onStreamDisconnected);
    connect(m_streamSocket, &QTcpSocket::readyRead, this, &CameraReceiver::onStreamReadyRead);
    connect(m_streamSocket, &QAbstractSocket::errorOccurred, this, &CameraReceiver::onStreamError);
    m_fpsTimer = new QTimer(this);
    m_fpsTimer->setInterval(1000);
    connect(m_fpsTimer, &QTimer::timeout, this, &CameraReceiver::onFpsTimerTick);

    m_udpSocket = new QUdpSocket(this);

    m_udpSocket->bind(QHostAddress::Any, 5006);

    connect(m_udpSocket, &QUdpSocket::readyRead, this, &CameraReceiver::readTelemetry);
}

void CameraReceiver::connectToHost(const QString &host, quint16 streamPort, quint16 commandPort)
{
    m_host = host;
    m_streamPort = streamPort;
    m_commandPort = commandPort;

    m_buffer.clear();
    m_pendingBytes = -1;

    m_streamSocket->connectToHost(host, streamPort);
    m_commandSocket->connectToHost(host, commandPort);

    qDebug() << "CameraReceiver: connecting to" << host << "stream=" << streamPort
             << "commands=" << commandPort;
}

void CameraReceiver::disconnectFromHost()
{
    m_streamSocket->disconnectFromHost();
    m_commandSocket->disconnectFromHost();
    m_fpsTimer->stop();
    m_buffer.clear();
    m_pendingBytes = -1;
}

void CameraReceiver::switchCamera(const QString &cameraName)
{
    if (m_commandSocket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "CameraReceiver: command socket not connected – cannot switch";
        return;
    }
    const QByteArray cmd = QStringLiteral("CMD:%1\n").arg(cameraName.toLower()).toUtf8();
    m_commandSocket->write(cmd);
    m_commandSocket->flush();
    qDebug() << "CameraReceiver: sent" << cmd.trimmed();
}

void CameraReceiver::setMode(const QString &modeName)
{
    if (m_commandSocket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "CameraReceiver: command socket not connected – cannot set mode";
        return;
    }
    const QByteArray cmd = QStringLiteral("MODE:%1\n").arg(modeName.toLower()).toUtf8();
    m_commandSocket->write(cmd);
    m_commandSocket->flush();
    qDebug() << "CameraReceiver: sent" << cmd.trimmed();
}

bool CameraReceiver::isConnected() const
{
    return m_streamSocket->state() == QAbstractSocket::ConnectedState;
}

// ---------------------------------------------------------------------------
// Private slots
// ---------------------------------------------------------------------------

void CameraReceiver::onStreamConnected()
{
    qDebug() << "CameraReceiver: stream socket connected";
    m_frameCount = 0;
    m_fpsTimer->start();
    emit connected();
}

void CameraReceiver::onStreamDisconnected()
{
    qDebug() << "CameraReceiver: stream socket disconnected";
    m_fpsTimer->stop();
    m_buffer.clear();
    m_pendingBytes = -1;
    emit disconnected();
}

void CameraReceiver::onStreamReadyRead()
{
    m_buffer.append(m_streamSocket->readAll());

    // Parse every complete frame in the buffer, but keep only the most recent
    // one. Decoding and painting each frame on the GUI thread can't keep up
    // with a 30 fps stream of full-resolution JPEGs, so stale frames are
    // discarded here to bound latency — we always display the newest frame
    // rather than letting a backlog build up (which otherwise drags the
    // displayed rate down to ~1 fps over time).
    QByteArray latestJpeg;

    while (true) {
        // -- Step 1: read 4-byte big-endian length header --
        if (m_pendingBytes == -1) {
            if (m_buffer.size() < 4)
                break;

            const auto *d = reinterpret_cast<const uchar *>(m_buffer.constData());
            const quint32 len = (quint32(d[0]) << 24) | (quint32(d[1]) << 16) | (quint32(d[2]) << 8)
                                | quint32(d[3]);

            m_buffer.remove(0, 4);
            m_pendingBytes = static_cast<qint32>(len);
        }

        // -- Step 2: wait until the full JPEG payload has arrived --
        if (m_buffer.size() < m_pendingBytes)
            break;

        latestJpeg = m_buffer.left(m_pendingBytes);
        m_buffer.remove(0, m_pendingBytes);
        m_pendingBytes = -1;
    }

    // Decode + display only the newest complete frame from this batch.
    if (!latestJpeg.isEmpty()) {
        QImage img;
        if (img.loadFromData(latestJpeg, "JPEG")) {
            ++m_frameCount;
            emit frameReady(img);
        }
    }
}

void CameraReceiver::onStreamError(QAbstractSocket::SocketError error)
{
    qDebug() << "CameraReceiver stream error:" << error << m_streamSocket->errorString();
}

void CameraReceiver::onFpsTimerTick()
{
    emit fpsUpdated(m_frameCount);
    m_frameCount = 0;
}
void CameraReceiver::readTelemetry()
{
    // Loop through all incoming network packets on port 5006
    while (m_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        m_udpSocket->readDatagram(datagram.data(), datagram.size());

        // Parse the incoming string as a JSON Document
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(datagram, &error);

        // If the JSON is valid, extract the depth number
        if (error.error == QJsonParseError::NoError && doc.isObject()) {
            QJsonObject json = doc.object();

            // Check if the JSON contains our "depth" key
            if (json.contains("depth")) {
                m_currentDepth = json["depth"].toDouble();
                qDebug() << "Received Live Depth:" << m_currentDepth;

                // Broadcast the live depth to the UI
                emit depthUpdated(m_currentDepth);
            }
            if (json.contains("pressure")) {
                m_currentPressure = json["pressure"].toDouble();
            }
            if (json.contains("depth") || json.contains("pressure")) {
                emit telemetryUpdated(m_currentDepth, m_currentPressure);
            }
            if (json.contains("als")) {
                m_alsEnabled = json["als"].toBool();
                m_alsPitch = json.value("pitch").toDouble();
                m_alsYaw = json.value("yaw").toDouble();
                emit alsUpdated(m_alsEnabled, m_alsPitch, m_alsYaw);
            }
            // Handle the X/Y coordinate logic
            if (json.contains("x") && json.contains("y")) {
                double icebergX = json["x"].toDouble();
                double icebergY = json["y"].toDouble();

                qDebug() << "Received Iceberg Coordinates - X:" << icebergX << " Y:" << icebergY;
                emit icebergMoved(icebergX, icebergY);
            }
        } else {
            qDebug() << "JSON Parse Error on Port 5006:" << error.errorString();
        }
    }
}

double CameraReceiver::getLiveDepth() const
{
    return m_currentDepth;
}

double CameraReceiver::getPressure() const
{
    return m_currentPressure;
}
