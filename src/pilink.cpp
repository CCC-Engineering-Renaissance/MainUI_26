#include "pilink.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>
#include <QTimer>

PiLink::PiLink(QObject *parent)
    : QObject(parent)
    , m_sock(new QTcpSocket(this))
    , m_pollTimer(new QTimer(this))
    , m_reconnectTimer(new QTimer(this))
{
    m_pollTimer->setInterval(2000);
    connect(m_pollTimer, &QTimer::timeout, this, &PiLink::poll);

    m_reconnectTimer->setSingleShot(true);
    m_reconnectTimer->setInterval(3000);
    connect(m_reconnectTimer, &QTimer::timeout, this, [this]() {
        if (!m_host.isEmpty() && m_sock->state() == QAbstractSocket::UnconnectedState)
            m_sock->connectToHost(m_host, m_port);
    });

    connect(m_sock, &QTcpSocket::connected,    this, &PiLink::onConnected);
    connect(m_sock, &QTcpSocket::disconnected, this, &PiLink::onDisconnected);
    connect(m_sock, &QTcpSocket::readyRead,    this, &PiLink::onReadyRead);
    connect(m_sock, &QTcpSocket::errorOccurred, this, &PiLink::onSocketError);
}

void PiLink::configure(const QString &host, quint16 port)
{
    m_host = host;
    m_port = port;
    m_tailSeq.clear();
    m_rx.clear();

    m_reconnectTimer->stop();
    m_pollTimer->stop();
    m_sock->abort();
    setOnline(false);

    if (!m_host.isEmpty())
        m_sock->connectToHost(m_host, m_port);
}

void PiLink::startTask(const QString &task)
{
    if (!m_online) {
        emit commandFailed(task, QStringLiteral("daemon offline"));
        return;
    }
    sendJson({{QStringLiteral("cmd"), QStringLiteral("start")},
              {QStringLiteral("task"), task}});
}

void PiLink::stopTask(const QString &task)
{
    if (!m_online) {
        emit commandFailed(task, QStringLiteral("daemon offline"));
        return;
    }
    sendJson({{QStringLiteral("cmd"), QStringLiteral("stop")},
              {QStringLiteral("task"), task}});
}

void PiLink::onConnected()
{
    setOnline(true);
    sendJson({{QStringLiteral("cmd"), QStringLiteral("status")}});
    m_pollTimer->start();
}

void PiLink::onDisconnected()
{
    setOnline(false);
    m_pollTimer->stop();
    scheduleReconnect();
}

void PiLink::onSocketError(QAbstractSocket::SocketError)
{
    setOnline(false);
    m_pollTimer->stop();
    scheduleReconnect();
}

void PiLink::onReadyRead()
{
    m_rx += m_sock->readAll();
    int idx;
    while ((idx = m_rx.indexOf('\n')) != -1) {
        const QByteArray line = m_rx.left(idx);
        m_rx.remove(0, idx + 1);
        const QJsonDocument doc = QJsonDocument::fromJson(line);
        if (doc.isObject())
            handleReply(doc.object());
    }
}

void PiLink::poll()
{
    sendJson({{QStringLiteral("cmd"), QStringLiteral("status")}});
    for (const QString &task : m_tasks) {
        sendJson({{QStringLiteral("cmd"), QStringLiteral("tail")},
                  {QStringLiteral("task"), task},
                  {QStringLiteral("since"), m_tailSeq.value(task, 0)}});
    }
}

void PiLink::sendJson(const QJsonObject &obj)
{
    if (m_sock->state() != QAbstractSocket::ConnectedState)
        return;
    m_sock->write(QJsonDocument(obj).toJson(QJsonDocument::Compact) + '\n');
}

void PiLink::handleReply(const QJsonObject &obj)
{
    const QString cmd  = obj.value(QStringLiteral("cmd")).toString();
    const QString task = obj.value(QStringLiteral("task")).toString();
    const bool ok      = obj.value(QStringLiteral("ok")).toBool();

    if (cmd == QLatin1String("status") && ok) {
        const QJsonObject tasks = obj.value(QStringLiteral("tasks")).toObject();
        for (auto it = tasks.begin(); it != tasks.end(); ++it) {
            const QJsonObject t = it.value().toObject();
            emit taskStateChanged(it.key(),
                                  t.value(QStringLiteral("state")).toString(),
                                  t.value(QStringLiteral("code")).toInt(0));
        }
    } else if (cmd == QLatin1String("tail") && ok) {
        const QJsonArray lines = obj.value(QStringLiteral("lines")).toArray();
        for (const auto &l : lines)
            emit taskOutput(task, l.toString());
        m_tailSeq[task] = static_cast<qint64>(
            obj.value(QStringLiteral("next")).toDouble(m_tailSeq.value(task, 0)));
    } else if ((cmd == QLatin1String("start") || cmd == QLatin1String("stop")) && !ok) {
        emit commandFailed(task, obj.value(QStringLiteral("error")).toString(
                                     QStringLiteral("unknown error")));
    }
}

void PiLink::setOnline(bool online)
{
    if (m_online == online)
        return;
    m_online = online;
    emit onlineChanged(online);
}

void PiLink::scheduleReconnect()
{
    if (!m_host.isEmpty() && !m_reconnectTimer->isActive())
        m_reconnectTimer->start();
}
