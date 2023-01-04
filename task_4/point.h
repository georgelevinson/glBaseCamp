#include <stdbool.h>

typedef struct Point
{
    unsigned short x;
    unsigned short y;
} Point, *PointPtr;

bool cmpr_pts(Point a, Point b);
void print_point(Point p);