#include "webservice.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>

#define UID_PROP "uid_soc"

QT_USE_NAMESPACE

WebService::WebService(quint16 port, bool debug, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Anim Service"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_debug(debug)
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug) {
            qDebug() << "WebAnimService listening on port " << port;
        }
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &WebService::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &WebService::closed);
    }
}

WebService::~WebService()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients);
    m_clients.clear();
}

void WebService::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &WebService::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WebService::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &WebService::socketDisconnected);
    QString uid = generateUID();
    pSocket->setProperty(UID_PROP,QVariant(uid));
    m_clients.insert(uid,pSocket);
    if (m_debug) {
        qDebug() << "Have new connection: " << pSocket->origin();
        qDebug() << "Total connections: " << m_clients.size();
    }
}

void WebService::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    QString uid = pClient->property(UID_PROP).toString();
    if (m_debug) {
        qDebug() << "Message received: " << message;
        qDebug() << "Client uid: " << uid;
    }
    if (pClient) {
        emit haveData(uid,QJsonDocument::fromJson(message.toLatin1()));
    }
}

void WebService::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug) {
        qDebug() << "Binary Message received: " << message;
    }
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}

void WebService::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    QString uid = pClient->property(UID_PROP).toString();
    if (m_debug) {
        qDebug() << "socketDisconnected: " << pClient;
        qDebug() << "Client uid: " << uid;
    }
    if (pClient) {
        m_clients.take(uid);
        pClient->deleteLater();
    }
}

void WebService::sendTextMessage(QString uid,QJsonDocument data)
{
    QString strJson(data.toJson(QJsonDocument::Compact));
    if (m_debug) {
        qDebug() << "Send message: " << data;
        qDebug() << "Client uid: " << uid;
    }
    if(m_clients.value(uid)) {
        m_clients.value(uid)->sendTextMessage(strJson);
    }
}

void WebService::sendTextMessageAll(QJsonDocument data)
{
    QString strJson(data.toJson(QJsonDocument::Compact));
    if (m_debug) {
        qDebug() << "Send message for all: " << data;
    }
    for (auto const& pClient : m_clients) {
        if(pClient) {
            pClient->sendTextMessage(strJson);
        }
    }
}


QString WebService::generateUID()
{
    QString uid  =  "[_"    +
                    QUuid::createUuid().toString() +
                    "_"     +
                    QString::number((int) QDateTime::currentDateTime().toMSecsSinceEpoch()) +
                    "_]";
    return uid;
}
