#pragma once
#include <QObject>
#include <QUdpSocket>

static constexpr quint16 TELEM_PORT = 5006;

struct TelemetryData {
    float depth        = 0.f;
    float temp         = 0.f;
    float pitch        = 0.f;
    float yaw          = 0.f;
    float roll         = 0.f;
    float depthSetpoint = 0.f;
    bool  als          = false;

    float yawKp   = 0.f, yawKi   = 0.f, yawKd   = 0.f;
    float pitchKp = 0.f, pitchKi = 0.f, pitchKd = 0.f;
    float rollKp  = 0.f, rollKi  = 0.f, rollKd  = 0.f;
    float depthKp = 0.f, depthKi = 0.f, depthKd = 0.f;
};

class TelemetryReceiver : public QObject {
    Q_OBJECT
public:
    explicit TelemetryReceiver(QObject *parent = nullptr);

    void startListening(quint16 port = TELEM_PORT);
    void stopListening();

signals:
    void telemetryReceived(const TelemetryData &data);

private slots:
    void onReadyRead();

private:
    QUdpSocket *m_socket = nullptr;
};
