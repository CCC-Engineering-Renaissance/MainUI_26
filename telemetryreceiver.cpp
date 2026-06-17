#include "telemetryreceiver.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkDatagram>

TelemetryReceiver::TelemetryReceiver(QObject *parent) : QObject(parent)
{
    m_socket = new QUdpSocket(this);
    connect(m_socket, &QUdpSocket::readyRead, this, &TelemetryReceiver::onReadyRead);
}

void TelemetryReceiver::startListening(quint16 port)
{
    if (m_socket->state() != QAbstractSocket::UnconnectedState)
        m_socket->close();
    m_socket->bind(QHostAddress::AnyIPv4, port,
                   QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
}

void TelemetryReceiver::stopListening()
{
    m_socket->close();
}

void TelemetryReceiver::onReadyRead()
{
    while (m_socket->hasPendingDatagrams()) {
        QByteArray data = m_socket->receiveDatagram().data();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isNull() || !doc.isObject())
            continue;

        QJsonObject o = doc.object();
        TelemetryData t;
        t.depth         = (float)o["depth"].toDouble();
        t.temp          = (float)o["temp"].toDouble();
        t.pitch         = (float)o["pitch"].toDouble();
        t.yaw           = (float)o["yaw"].toDouble();
        t.roll          = (float)o["roll"].toDouble();
        t.depthSetpoint = (float)o["depth_setpoint"].toDouble();
        t.als           = o["als"].toBool();
        t.yawKp         = (float)o["yaw_kp"].toDouble();
        t.yawKi         = (float)o["yaw_ki"].toDouble();
        t.yawKd         = (float)o["yaw_kd"].toDouble();
        t.pitchKp       = (float)o["pitch_kp"].toDouble();
        t.pitchKi       = (float)o["pitch_ki"].toDouble();
        t.pitchKd       = (float)o["pitch_kd"].toDouble();
        t.rollKp        = (float)o["roll_kp"].toDouble();
        t.rollKi        = (float)o["roll_ki"].toDouble();
        t.rollKd        = (float)o["roll_kd"].toDouble();
        t.depthKp       = (float)o["depth_kp"].toDouble();
        t.depthKi       = (float)o["depth_ki"].toDouble();
        t.depthKd       = (float)o["depth_kd"].toDouble();

        emit telemetryReceived(t);
    }
}
