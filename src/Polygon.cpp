#include "Polygon.h"

Polygon::Polygon()
{

}

Polygon::Polygon(Point A, Polygon B, Polygon C)
{
    points.push_back (A);
    points.push_back (B);
    points.push_back (C);

}

Polygon::Polygon(Point A, Polygon B, Polygon C, Polygon D)
{
    points.push_back (A);
    points.push_back (B);
    points.push_back (C);
    points.push_back (D);
}

