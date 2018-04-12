#include <QCoreApplication>
#include <stdlib.h>
#include "tserver.h"
#include "webservice.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TServer *server;
    switch(argc)
    {
        case 2:
        {
            server = new TServer(atoi(argv[1]));
            break;
        }
        case 3:
        {
            server = new TServer(atoi(argv[1]), argv[2]);
            break;
        }
        default:
        {
            server = new TServer();
            break;
        }
    }

    WebService  *webService = new WebService(server->getPort(), true);

    QObject::connect(webService, SIGNAL(closed()), server, SIGNAL(servClose()));
    QObject::connect(webService, SIGNAL(haveData(QString,QJsonDocument)),
                     server, SLOT(onRadyRead(QString,QJsonDocument)));
    QObject::connect(server, &TServer::servClose, &a, &QCoreApplication::quit);
    QObject::connect(server, SIGNAL(send(QJsonDocument)),
                     webService, SLOT(sendTextMessageAll(QJsonDocument)));
    QObject::connect(server, SIGNAL(send(QString,QJsonDocument)),
                     webService, SLOT(sendTextMessage(QString,QJsonDocument)));
    return a.exec();
}

