#ifndef POLYGON_H
#define POLYGON_H
#include "Point.h"
#include <vector>

using namespace std;

struct Polygon
{
public:
    vector<Point> points;
    vector<Point>::iterator k;
};

#endif // POLYGON_H
