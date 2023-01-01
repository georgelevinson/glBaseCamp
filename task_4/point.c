#include "point.h" 

bool cmpr_pts(Point a, Point b)
{
    if(a.x == b.x && a.y == b.y)
    {
        return true;
    }
    else
    {
        return false;
    }
};