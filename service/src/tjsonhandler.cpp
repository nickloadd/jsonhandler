#include "tjsonhandler.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

using std::string;

/*===================================================
 * Конструктор класса
===================================================*/
TJsonHandler::TJsonHandler(QObject *parent) :
    QObject(parent)
{

}

/*===================================================
 * Метод принимает набор объектов .json-файла
 * json, обрабатывает его и возвращает результаты
 * обработки в формате t_jsonData
===================================================*/
t_jsonData TJsonHandler::parse(const QJsonDocument &json)
{
    t_jsonData jsonData = {};
    if(!json.isEmpty() && json.isObject())
    {
        jsonData.nodeList = TJsonHandler::getNodes(json.object()["nodes"].toArray());
        jsonData.linkList = TJsonHandler::getLinks(json.object()["links"].toArray());
        jsonData.simulationInfo = TJsonHandler::getSimInfo(json.object()["simulation"].toObject());
    }
    return jsonData;
}

/*===================================================
 * Метод возвращает данные о топологии сети в формате
 * QJsonArray
 * Аргументы:
 *  nodes - перечень данных об узлах сети;
 *  links - перечень данных о связях между узлами
===================================================*/
QJsonArray TJsonHandler::getGraph(const QVector<t_node> &nodes, const QVector<t_link> &links)
{

    QJsonObject object;
    QJsonArray nodeArray, linkArray;
    object.insert("nodes", nodeArray);
    object.insert("links", linkArray);
    QJsonArray array;
    array.append(object);

    foreach (t_node node, nodes)
    {
        QJsonObject nodeObj;
        nodeObj.insert("id", int(node.id));
        nodeObj.insert("group", 1);
        nodeArray.append(nodeObj);
    }

    foreach (t_link link, links)
    {
        QJsonObject linkObj;
        linkObj.insert("source", int(link.source));
        linkObj.insert("target", int(link.target));
        linkObj.insert("value", 1);
        linkArray.append(linkObj);
    }

//    object.insert("nodes", nodeArray);
//    object.insert("links", linkArray);
//    QJsonArray array;
//    array.append(object);
    return array;
}

/*===================================================
 * Метод возвращает перечень симуляций, загруженных в
 * оперативную память в формате QJsonArray.
 * Аргументы:
 *  simList - перечень назнваний загруженных симуля-
 *            ций
===================================================*/
QJsonArray TJsonHandler::getList(const QStringList &simList)
{
    QJsonArray array;
    foreach (QString simName, simList)
    {
        QJsonObject object;
        simName.remove(".json");
        object.insert("simulation_name", simName);
        array.append(object);
    }
    return array;
}

/*===================================================
 * Метод возвращает данные о симуляции в формате
 * QJsonArray.
 * Аргументы:
 *  simulation - данные о симуляции, хранящиеся в
 *               оперативной памяти программы
===================================================*/
QJsonArray TJsonHandler::getSim(const t_simulation &simulation)
{
    QJsonArray array;
    QJsonObject object;
    object.insert("simulation_time", int(simulation.time));
    object.insert("packet_size", int(simulation.packets.packetSize));
    array.append(object);
    return array;
}

/*===================================================
 * Метод возвращает физичекие параметры сети в форма-
 * те QJsonArray.
 * Аргументы:
 *  nodes - перечень данных об узлах сети
 *  links - перечень данных о связях между узлами се-
 *          ти.
===================================================*/
QJsonArray TJsonHandler::getNetwork(const QVector<t_node> nodes, const QVector<t_link> links)
{
    QJsonArray nodeArray, linkArray;
    QJsonObject object;
    foreach (t_node node, nodes)
    {
        QJsonObject nodeObj;
        nodeObj.insert("id", int(node.id));
        nodeObj.insert("mac_address", node.mac_address);
        nodeArray.append(nodeObj);
    }

    foreach (t_link link, links)
    {
        QJsonObject linkObj;
        linkObj.insert("source", int(link.source));
        linkObj.insert("target", int(link.target));
        linkObj.insert("cable_type", link.cableType);
        linkArray.append(linkObj);
    }

    object.insert("nodes", nodeArray);
    object.insert("links", linkArray);
    QJsonArray array;
    array.append(object);
    return array;
}

/*===================================================
 * Метод обрабатывает json-строку json, поступившую
 * от клиента, и формирует в соответствии с ней ко-
 * манду в формате t_command, которую должен выпол-
 * нить cервер
===================================================*/
t_command TJsonHandler::getCommand(const QJsonDocument &json)
{
    t_command cmd;
    if(json.isObject())
    {
        QJsonObject object = json.object();

        if(object.value(CMD) == CMD_NAME_GRAPH)
        {
            if(object.value(CMD_TYPE) == CMD_TYPE_GET)
            {
                cmd.cmdType = GET_GRAPH;
            }
        }
        if(object.value(CMD) == CMD_NAME_LIST)
        {
            if(object.value(CMD_TYPE) == CMD_TYPE_GET)
            {
                cmd.cmdType = GET_LIST;
            }
        }
        if(object.value(CMD) == CMD_NAME_SIMULATION)
        {
            if(object.value(CMD_TYPE) == CMD_TYPE_GET)
            {
                cmd.cmdType = GET_SIMULATION;
            }
        }
        if(object.value(CMD) == CMD_NAME_NETWORK)
        {
            if(object.value(CMD_TYPE) == CMD_TYPE_GET)
            {
                cmd.cmdType = GET_NETWORK;

            }
        }
        QJsonObject cmdParams = object.value(CMD_PARAM).toArray().at(0).toObject();
        cmd.parameters.insert(CMD_PARAM_SIMNAME, cmdParams.value(CMD_PARAM_SIMNAME).toString());
    }
    return cmd;
}

/*===================================================
 * Метод обрабатывает массив json-объектов nodes и
 * возвращает информацию об этом узле в виде структу-
 * ры t_node
===================================================*/
QVector<t_node> TJsonHandler::getNodes(const QJsonArray &nodes)
{
    QVector<t_node> nodeList;
    for(int i = 0; i < nodes.size(); ++i)
    {
        if(nodes.at(i).isObject())
        {
            t_node node;
            QJsonObject obj = nodes.at(i).toObject();
            node.id = obj["id"].toString().toInt();
            node.mac_address = obj["mac_address"].toString();
            node.pos.x = obj["position"].toObject()["x"].toString().toInt();
            node.pos.y = obj["position"].toObject()["y"].toString().toInt();
            node.pos.z = obj["position"].toObject()["z"].toString().toInt();
            nodeList.append(node);
        }
    }
    return nodeList;
}

/*===================================================
 * Метод обрабатывает массив json-объектов links и
 * возвращает информацию об этой связи в виде струк-
 * туры t_link
===================================================*/
QVector<t_link> TJsonHandler::getLinks(const QJsonArray &links)
{
    QVector <t_link> linkList;
    for(int i = 0; i < links.size(); ++i)
    {
        t_link link;
        QJsonObject obj = links.at(i).toObject();
        link.source = obj["source"].toString().toInt();
        link.target = obj["target"].toString().toInt();
        link.distance = obj["distance"].toString().toDouble();
        link.cableType = obj["cable_type"].toString();
        linkList.append(link);
    }
    return linkList;
}

/*===================================================
 * Метод  обрабатывает json-объект simObjectи возвра-
 * щает информацию о симуляции в виде структуры типа
 * t_simulation
===================================================*/
t_simulation TJsonHandler::getSimInfo(const QJsonObject &simObject)
{
    t_simulation simInfo;
    simInfo.time = simObject["time"].toVariant().toUInt();
    QJsonObject packetObj = simObject["packet_info"].toObject();
    simInfo.packets.packetSize = packetObj["size"].toVariant().toUInt();
    QJsonArray routesArray = simObject["routes"].toArray();
    simInfo.routes = TJsonHandler::getPaths(routesArray);
    return simInfo;
}

/*===================================================
 * Метод обрабатывает массив json-объектов paths и
 * возвращает информацию о кратчайших путях симуляции
 * в виде вектора структур типа t_shortestPaths
===================================================*/
QVector<t_shortestPath> TJsonHandler::getPaths(const QJsonArray &paths)
{
    QVector<t_shortestPath> routes;
    for(int i = 0; i < paths.size(); ++i)
    {
       t_shortestPath p;
       p.source = paths.at(i).toObject()["source"].toVariant().toUInt();
       p.target = paths.at(i).toObject()["target"].toVariant().toUInt();
       QJsonArray route = paths.at(i).toObject()["path"].toArray();
       for(int j = 0; j < route.size(); ++j)
       {
           p.path.append(route.at(j).toObject()["node"].toVariant().toUInt());
       }
       routes.append(p);
    }
    return routes;
}


