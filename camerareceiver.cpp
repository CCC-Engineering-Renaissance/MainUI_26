#include "camerareceiver.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDebug>
CameraReceiver::CameraReceiver(QObject *parent)
    : QObject(parent)
{
    m_streamSocket  = new QTcpSocket(this);
    m_commandSocket = new QTcpSocket(this);

    connect(m_streamSocket, &QTcpSocket::connected,
            this, &CameraReceiver::onStreamConnected);
    connect(m_streamSocket, &QTcpSocket::disconnected,
            this, &CameraReceiver::onStreamDisconnected);
    connect(m_streamSocket, &QTcpSocket::readyRead,
            this, &CameraReceiver::onStreamReadyRead);
    connect(m_streamSocket, &QAbstractSocket::errorOccurred,
            this, &CameraReceiver::onStreamError);
    m_fpsTimer = new QTimer(this);
    m_fpsTimer->setInterval(1000);
    connect(m_fpsTimer, &QTimer::timeout, this, &CameraReceiver::onFpsTimerTick);

    m_udpSocket = new QUdpSocket(this);

    m_udpSocket->bind(QHostAddress::Any, 5006);

    connect(m_udpSocket, &QUdpSocket::readyRead, this, &CameraReceiver::readTelemetry);
}

void CameraReceiver::connectToHost(const QString &host,
                                   quint16 streamPort,
                                   quint16 commandPort)
{
    m_host        = host;
    m_streamPort  = streamPort;
    m_commandPort = commandPort;

    m_buffer.clear();
    m_pendingBytes = -1;

    m_streamSocket->connectToHost(host, streamPort);
    m_commandSocket->connectToHost(host, commandPort);

    qDebug() << "CameraReceiver: connecting to" << host
             << "stream=" << streamPort
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
    const QByteArray cmd =
        QStringLiteral("CMD:%1\n").arg(cameraName.toLower()).toUtf8();
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
    const QByteArray cmd =
        QStringLiteral("MODE:%1\n").arg(modeName.toLower()).toUtf8();
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

    // Parse as many complete frames as are buffered
    while (true) {
        // -- Step 1: read 4-byte big-endian length header --
        if (m_pendingBytes == -1) {
            if (m_buffer.size() < 4)
                break;

            const auto *d = reinterpret_cast<const uchar *>(m_buffer.constData());
            const quint32 len =
                (quint32(d[0]) << 24) | (quint32(d[1]) << 16) |
                (quint32(d[2]) <<  8) |  quint32(d[3]);

            m_buffer.remove(0, 4);
            m_pendingBytes = static_cast<qint32>(len);
        }

        // -- Step 2: wait until the full JPEG payload has arrived --
        if (m_buffer.size() < m_pendingBytes)
            break;

        const QByteArray jpeg = m_buffer.left(m_pendingBytes);
        m_buffer.remove(0, m_pendingBytes);
        m_pendingBytes = -1;

        QImage img;
        if (img.loadFromData(jpeg, "JPEG")) {
            ++m_frameCount;
            emit frameReady(img);
        }
    }
}

void CameraReceiver::onStreamError(QAbstractSocket::SocketError error)
{
    qDebug() << "CameraReceiver stream error:" << error
             << m_streamSocket->errorString();
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
            }
        } else {
            qDebug() << "JSON Parse Error on Port 5006:" << error.errorString();
        }
    }
}

// Return the most recent depth when the Keel Page asks for it
double CameraReceiver::getLiveDepth() const
{
    return m_currentDepth;
}
