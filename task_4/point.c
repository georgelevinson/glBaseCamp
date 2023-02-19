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
void print_point(Point p)
{
    printf("\n\nx: %i; y: %i\n\n", p.x, p.y);
}