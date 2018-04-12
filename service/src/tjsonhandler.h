#ifndef TJSONPARSER_H
#define TJSONPARSER_H

#include "types.h"
#include <QObject>
#include <QVector>
#include <QStringList>
#include <QJsonDocument>

/*=========================================
* Класс TJsonParser обрабатывает поступаю-
* щие .json_файлы и возвращает структуру
* данных о файле, загружаемую в оператив-
* ную память
=========================================*/
class TJsonHandler : public QObject
{
    Q_OBJECT
public:
    explicit                TJsonHandler(QObject *parent = 0);          //конструктор
    static t_jsonData       parse       (const QJsonDocument & json);   //обработка .json-файла
    //static QJsonArray       generate    (const t_jsonData & data);      //генерация в виде JSON-строки конкретной симуляции
    //static QJsonArray       generate    (const QStringList & simList);  //генерация в виде JSON-строки списка симуляций
    static QJsonArray       getGraph    (const QVector <t_node> & nodes,
                                         const QVector <t_link> & links);   //
    static QJsonArray       getList     (const QStringList & simList);      //
    static QJsonArray       getSim      (const t_simulation & simulation);  //
    static QJsonArray       getNetwork  (const QVector <t_node> nodes,
                                         const QVector <t_link> links);     //
    static t_command        getCommand  (const QJsonDocument & json);       //получение типа команды для сервера от клиента

signals:

public slots:

private:
    static
    QVector <t_node>        getNodes    (const QJsonArray & nodes);         //получние данных об узлах графа
    static
    QVector <t_link>        getLinks    (const QJsonArray & links);         //получение данных о ребрах графа
    static t_simulation     getSimInfo  (const QJsonObject & simObject);    //получение данных о симуляции
    static
    QVector<t_shortestPath> getPaths(const QJsonArray & paths);             //получение данных о кратчайших путях
};

#endif // TJSONPARSER_H
