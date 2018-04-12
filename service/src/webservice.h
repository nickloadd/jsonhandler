#ifndef WEBSERVICE_H
#define WEBSERVICE_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include <QtCore/QMap>
#include <QtCore/QUuid>
#include <QtCore/QJsonDocument>
#include <QtCore/QVariant>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class WebService : public QObject
{
    Q_OBJECT
public:
    explicit WebService(quint16 port, bool debug = false, QObject *parent = Q_NULLPTR);
    ~WebService();

public slots:
    void sendTextMessage(QString uid, QJsonDocument data);
    void sendTextMessageAll(QJsonDocument data);

signals:
    void closed();
    void haveData(QString uid, QJsonDocument data);

private slots:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QMap<QString, QWebSocket *> m_clients;
    bool m_debug;
    QString generateUID();
};

#endif //WEBSERVICE_H
