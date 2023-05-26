#include "apartment.h"

apartment::apartment()
{
    rooms = 0;
    square = 0;
    cost = 0;
    locate = "";
}

apartment::apartment(int _rooms, float _square, float _cost, QString _locate)
{
    rooms = _rooms;
    square = _square;
    cost = _cost;
    locate = _locate;
}

apartment::~apartment()
{
}
