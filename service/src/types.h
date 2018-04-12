#ifndef TYPES
#define TYPES

#include <QVector>
#include <QMap>
#include <QString>
/*=========================================
* структура описывает координаты узла
* в трехмерном пространстве
=========================================*/
typedef struct
{
    int x;
    int y;
    int z;
}t_position;

/*=========================================
* структура, описывает содержимое узла
=========================================*/
typedef struct
{
    unsigned int id;
    QString      mac_address;
    t_position   pos;
}t_node;

/*=========================================
* Структура описывает связь между узлами
=========================================*/
typedef struct
{
    unsigned int source;
    unsigned int target;
    double       distance;
    QString      cableType;
}t_link;

/*=========================================
* структура содержит данные о пакетах симу-
* ляции
=========================================*/
typedef struct
{
    unsigned int    packetSize;
    unsigned int    total;
    unsigned int    lost;
}t_packetInfo;

/*=========================================
* структура содержит данные о кратчайших
* путях
=========================================*/
typedef struct
{
    unsigned int    source;
    unsigned int    target;
    QVector
    <unsigned int>  path;
}t_shortestPath;

/*=========================================
* структура содержит данные о симуляции
=========================================*/
typedef struct
{
    unsigned int    time;
    t_packetInfo    packets;
    QVector
    <t_shortestPath>routes;
}t_simulation;

/*=========================================
* структура описывает содержимое обработан-
* ного .json-файла
=========================================*/
typedef struct
{
    QVector <t_node> nodeList;
    QVector <t_link> linkList;
    t_simulation     simulationInfo;
}t_jsonData;

/*=========================================
* Перечислитель содержит перечень типов вы-
* полняемых сервером команд
=========================================*/
enum e_cmd
{
    GET_LIST,       //отправка списка имеющихся симиуляций
    GET_GRAPH,      //отправка конкретного графа симуляции
    GET_SIMULATION, //отправка данных о симуляции
    GET_NETWORK     //отправка данных о сети
};

/*=========================================
* Тип описывает команду, полученную от клиента
=========================================*/
typedef struct
{
    e_cmd               cmdType;    //тип команды
    QMap
    <QString, QString>  parameters; //параметры команды
}t_command;

/*======================= Константы ===================================*/
const QString CMD               = "command";        //тип поля запроса "команда"
const QString CMD_TYPE          = "command_type";   //тип поля запроса "тип команды"
const QString CMD_PARAM         = "parameters";     //тип поля запроса "параметры"

const QString CMD_TYPE_GET      = "get";    //значение типа команды "get"
const QString CMD_TYPE_SET      = "set";    //значение типа команды "set"

const QString CMD_NAME_LIST         = "list";       //значение имени команды "list"
const QString CMD_NAME_GRAPH        = "graph";      //значение имени команды "graph"
const QString CMD_NAME_SIMULATION   = "simulation"; //значение имени команды "siulation"
const QString CMD_NAME_NETWORK      = "network";    //значениеимени команды "network"

const QString CMD_PARAM_SIMNAME = "simulation_name"; //значение элемента поля параметров "simulation_name"

#endif // TYPES

