#ifndef DATABASE_H
#define DATABASE_H

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QMessageBox>
#include <QVariantMap>
#include <QString>
#include <QVector>

#include "apartment.h"

class dataBase
{
public:
    dataBase();
    void setPath(QString);
    void read();
    QVector<apartment> getDb();
    void write();
    void add(int, double, double, QString);
    void removeData(int);
    void changeData(int,int,QString);

private:
    QVector<apartment> db;
    QFile db_file;
    QJsonDocument dbJsonDoc;
    QJsonArray jsonArray;
};

#endif // DATABASE_H
