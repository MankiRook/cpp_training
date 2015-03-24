#ifndef POINT_H
#define POINT_H

using namespace std;

struct Point
{

public:
    //Memberinitialisierung im Konstruktor
    Point() : x(0), y(0) {};
    Point(float x, float y) : x(x), y(y) {};
    float x, y;
};

#endif // POINT_H
