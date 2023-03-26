#include "levelchecker.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QFile>

LevelChecker::LevelChecker(QObject *parent) : QObject(parent)
{

}

LevelChecker::~LevelChecker()
{

}

int LevelChecker::setPathToFile(const QString &personalFileDataPath)
{
    _personalFileDataPath = personalFileDataPath;
    QFile file(personalFileDataPath);
    if(!file.exists())
        return ANOTHER_ERROR;
    return NO_ERROR;
}

void LevelChecker::setPass(const QString &pass)
{
    _pass = pass;
}

int LevelChecker::startReadFile()
{
    if(_personalFileDataPath.isEmpty())
        return READ_ERROR;

    QFile file(_personalFileDataPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return READ_ERROR;
    }

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());

    if(!doc.isObject()) {
        qCritical() << "Входные данные не являются JSON'ом";
        qDebug() << "Error: " << error.errorString() << error.offset << error.error;
        return JSON_ERROR;
    }

    file.close();

    QSharedPointer<QHash<QString,QString>> pointer(new QHash<QString,QString>());

    QJsonObject json = doc.object();
    QJsonArray array = json["persons"].toArray();

    for(int i = 0; i < array.count(); i++) {
        QJsonObject obj = array.at(i).toObject();
        QString name = obj["person"].toString();
        QString pass = obj["pass"].toString();

        pointer->insert(name, pass);
    }

    if(pointer->key(_pass).isEmpty())
        _pass = "";

    _level = pointer->key(_pass);

    emit sendLevel(_level);

    return NO_ERROR;
}

void LevelChecker::run()
{
    int res = startReadFile();
    if(res) {
        qCritical() << "Код ошибки:" << res;
        return;
    }

    emit finished();

    return;
}
