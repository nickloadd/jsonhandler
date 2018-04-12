#include "tserver.h"
#include <QDebug>
#include <QTcpSocket>
#include <QDataStream>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>

/*===================================================
 * Конструктор класса
 * Ангументы:
 *  port    - номер порта сервера
 *  workDir - путь к рабочей директории
===================================================*/
TServer::TServer(quint16 port, QString workDir, QTcpServer *parent) :
    QTcpServer(parent), m_port(port), m_FManager(workDir)
{
    qDebug() << "[ ] Server is started";
    qDebug() << "Port: " << port;
    qDebug() << "Work directory: " << workDir;
    m_FManager.start();
}

/*===================================================
 * Метод возвращает номер порта для подключения к
 * серверу
===================================================*/
int TServer::getPort()
{
    return m_port;
}

/*===================================================
 * Метод обрабатывает команду cmd, полученную от
 * клиента и возвращает данныед
===================================================*/
QJsonDocument & TServer::execCmd(QJsonDocument &json)
{
    QJsonObject dataForJson = json.object();
    QJsonArray array;
    QString simName = m_command.parameters.value(CMD_PARAM_SIMNAME) + ".json";
    t_jsonData info = m_FManager.getSimulation(simName);

    switch (m_command.cmdType)
    {
        case GET_GRAPH: //результатом обработки команды будут данные о конкретном графе
        {
            array = TJsonHandler::getGraph(info.nodeList, info.linkList);
            break;
        }
        case GET_LIST:  //результатом обработки команды будет перечень загруженных симуляций
        {
            array = TJsonHandler::getList(m_FManager.getSimulationList());
            break;
        }
        case GET_SIMULATION:
        {
            array = TJsonHandler::getSim(info.simulationInfo);
            break;
        }
        case GET_NETWORK:
        {
            array = TJsonHandler::getNetwork(info.nodeList, info.linkList);
            break;
        }
        default:
        {
            break;
        }
    }
    dataForJson.insert("data", array);
    json.setObject(dataForJson);
    return json;
}

/*===================================================
 * Метод считывает и обрабатывает данные, передавае-
 * мые клиентом
===================================================*/
void TServer::onRadyRead(QString id, QJsonDocument data)
{
    qDebug() << "[ ] Server received data: " << data;
    m_command = TJsonHandler::getCommand(data);
    execCmd(data);
    emit send(id, data);
}

