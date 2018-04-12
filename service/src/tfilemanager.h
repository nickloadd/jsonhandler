#ifndef TFILEMANAGER_H
#define TFILEMANAGER_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include <QString>
#include <QTimer>
#include <QJsonDocument>
#include "tjsonhandler.h"

/*===================================================
 * Класс предназначен для отслеживания и загрузки в
 * оперативную память новых .json-файлов, добавляемых
 * в рабочую директорию
===================================================*/
class TFileManager : public QObject
{
    Q_OBJECT
public:
    explicit    TFileManager        (QString workDirectory = "./", QObject *parent = 0);    //конструктор
    bool        isStarted           () const;                           //получение флага запуска файлового менеджера
    void        changeWDir          (QString workDirectory = "./");     //смена рабочей директории
    QStringList getSimulationList   () const;                           //получение перечня симуляций
    t_jsonData  getSimulation       (QString simulationName) const;     //получение конкретной симуляции

signals:

public slots:
    void    start       (); //запуск файлового менеджера
    void    stop        (); //остановка файлового менеджера

private:
//поля
    QMap <QString,
    t_jsonData>             m_jsonData;     //список данных из загруженных .json_файлов
    QStringList             m_fileList;     //список имен загруженных файлов
    bool                    m_start;        //флаг запуска файлового менеджера
    QString                 m_WDir;         //путь к рабочей директории
    QTimer                  m_timer;        //таймер для проверки рабочей директории
    static const int        M_TIME = 60000; //период времени, через которыйрабочая директория проверяется на наличие новых файлов

//методы
    QJsonDocument   getWDData   (const QString & filename) const;          //получение дерева данных из файла.

private slots:
    void    checkWDir   (); //проверка рабочей директории
};

#endif // TFILEMANAGER_H
