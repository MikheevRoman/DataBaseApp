#ifndef APARTMENT_H
#define APARTMENT_H

#include <QString>

//stroka sost
class apartment
{
public:
    apartment();
    apartment(int,float,float,QString);
    ~apartment();

    void setRooms(int _rooms) {rooms = _rooms;}
    void setSquare(double _square) {square = _square;}
    void setCost(double _cost) {cost = _cost;}
    void setLocate(QString _loc) {locate = _loc;}

    int getRooms() {return rooms;}
    double getSquare(){return square;}
    double getCost(){return cost;}
    QString getLocate(){return locate;}

private:
    int rooms;
    double square;
    double cost;
    QString locate;
};

#endif // APARTMENT_H
