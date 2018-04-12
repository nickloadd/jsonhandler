#ifndef TSERVER_H
#define TSERVER_H

#include <QTcpServer>
#include <QObject>
#include <QString>
#include <QStringList>
#include "tfilemanager.h"

/*===================================================
 * Класс управляет серверной частью визуализатора:
 * устанавливает сетевые соединения и передает клиен-
 * ту необходимый набор данных в формате JSON.
===================================================*/
class TServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit    TServer     (quint16 port = 9090, QString workDir = "./", QTcpServer *parent = 0);    //конструктор
    int         getPort     ();     //получение порта сервера

signals:
    void        servClose   ();                                 //сигнал на завершение работы сервера
    void        send        (QString id, QJsonDocument data);   //сигнал на отправку данных одному клиенту
    void        send        (QJsonDocument data);               //сигнал на отправку данных всем клиентам

public slots:
    void        onRadyRead  (QString id, QJsonDocument data);   //чтение данных, получаемых от клиента

private:
//Методы

    QJsonDocument&  execCmd     (QJsonDocument &json);                      //выполнение запрашиваемой команды

//Поля
    quint16         m_port;         //номер порта
    TFileManager    m_FManager;     //объект по работе с файлами
    t_command       m_command;      //команда, которую необходимо выполнить
};

#endif // TSERVER_H
