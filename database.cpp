#include "database.h"

dataBase::dataBase()
{
}

void dataBase::setPath(QString path)
{
    db_file.setFileName(path);
}

void dataBase::read()
{
    QJsonParseError jsonParseError;
    if (db_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        dbJsonDoc = QJsonDocument::fromJson(QByteArray(db_file.readAll()),&jsonParseError);
        db_file.close();
        if (jsonParseError.errorString().toInt() == QJsonParseError::NoError)
        {
            jsonArray = QJsonValue(dbJsonDoc.object().value("apartment")).toArray();
            for (int i = 0; i < jsonArray.count(); i++)
            {
                apartment temp_obj = apartment(jsonArray.at(i).toObject().value("rooms").toInt(),
                                               jsonArray.at(i).toObject().value("square").toDouble(),
                                               jsonArray.at(i).toObject().value("cost").toDouble(),
                                               jsonArray.at(i).toObject().value("location").toString());
                db.push_back(temp_obj);
            }
        }
        else
            QMessageBox::warning(nullptr,"Ошибка","Не удалось прочитать файл с базой данных (ошибка парсинга):\n"+jsonParseError.errorString());
    }
    else
        QMessageBox::warning(nullptr,"Ошибка","Не удалось открыть файл с базой данных");
}

QVector<apartment> dataBase::getDb()
{
    return db;
}

void dataBase::write()
{
    if (db_file.open(QIODevice::WriteOnly))
    {
        db_file.write("{\n\t\"apartment\":"+dbJsonDoc.toJson()+"}");
        db_file.close();
    }
    else
        QMessageBox::warning(nullptr,"Ошибка","Не удалось открыть файл на запись");
}

void dataBase::add(int _rooms, double _square, double _cost, QString _location)
{
    apartment temp(_rooms,_square,_cost,_location);
    db.push_back(temp);

    QVariantMap map;
    map.insert("rooms",_rooms);
    map.insert("square",_square);
    map.insert("cost",(int)_cost);
    map.insert("location",_location);
    QJsonObject newObj = QJsonObject::fromVariantMap(map);
    jsonArray.append(newObj);
    dbJsonDoc.setArray(jsonArray);
}

void dataBase::removeData(int index)
{
    db.removeAt(index);

    jsonArray.removeAt(index);
    dbJsonDoc.setArray(jsonArray);
}

void dataBase::changeData(int i, int j, QString newData)
{
    if (i == 0)
    {
        db[j].setRooms(newData.toInt());
        jsonArray.at(j).toObject().value("rooms") = QJsonValue(newData);
        dbJsonDoc.setArray(jsonArray);
    }
    else if (i == 1)
    {
        db[j].setSquare(newData.toDouble());
        jsonArray.at(j).toObject().value("square") = QJsonValue(newData);
        dbJsonDoc.setArray(jsonArray);
    }
    else if (i == 2)
    {
        db[j].setCost(newData.toInt());
        jsonArray.at(j).toObject().value("cost") = QJsonValue(newData);
        dbJsonDoc.setArray(jsonArray);
    }
    else if (i == 3)
    {
        db[j].setLocate(newData);
        jsonArray.at(j).toObject().value("locate") = QJsonValue(newData);
        dbJsonDoc.setArray(jsonArray);
    }
}
