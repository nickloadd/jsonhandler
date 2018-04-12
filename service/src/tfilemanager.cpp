#include "tfilemanager.h"
#include <QDir>
#include <QDebug>
#include <QFile>

/*===================================================
 * Конструктор класса.
 * Аргументы:
 *  workDirectory - путь к рабочей директории
===================================================*/
TFileManager::TFileManager(QString workDirectory, QObject *parent) :
    QObject(parent), m_start(false)
{
    m_WDir = workDirectory;
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(checkWDir()));
}


/*===================================================
 * Метод возвращает флаг запуска файлового менеджера
===================================================*/
bool TFileManager::isStarted() const
{
    return m_start;
}

/*===================================================
 * Метод изменяет забочую директорию на значение
 * workDirectory
===================================================*/
void TFileManager::changeWDir(QString workDirectory)
{
    m_WDir = workDirectory;
    m_fileList.clear();
    m_jsonData.clear();
    checkWDir();
}

/*===================================================
 * Метод возвращает перечень загруженных в опертивную
 * память симуляций
===================================================*/
QStringList TFileManager::getSimulationList() const
{
    return m_fileList;
}

/*===================================================
 * Метод возвращает данные о симуляции с именем
 * simulationName
===================================================*/
t_jsonData TFileManager::getSimulation(QString simulationName) const
{
    t_jsonData data;
    return m_jsonData.value(simulationName, data);
}

/*===================================================
 * Метод проверяет наличие в директории новых .json-
 * файлов
===================================================*/
void TFileManager::checkWDir()
{
    QDir dir(m_WDir);
    QStringList fileList = dir.entryList(QStringList("*.json"));

    foreach (QString filename, fileList)
    {
        qDebug()<<filename;
        if(!m_fileList.contains(filename))
        {
            m_fileList.append(filename);
            m_jsonData.insert(filename, TJsonHandler::parse(getWDData(filename)));
        }
    }
}

/*===================================================
 * Метод возвращает данные из файла filename в виде
 * набора Json-объектов
===================================================*/
QJsonDocument TFileManager::getWDData(const QString &filename) const
{
    QJsonDocument json;
    QFile file(filename);
    file.open(QFile::ReadOnly);
    return json.fromJson(file.readAll());
}

/*===================================================
 * Метод запускает файловый менеджер
===================================================*/
void TFileManager::start()
{
    m_start = true;
    checkWDir();
    m_timer.start(M_TIME);
}

/*===================================================
 * Метод останавливает файловый менеджер
===================================================*/
void TFileManager::stop()
{
    m_start = false;
    m_timer.stop();
}

