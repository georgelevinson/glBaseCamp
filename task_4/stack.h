#include "point.h"

typedef struct Crossing
{
    Point coord;
    bool north;
    bool east;
    bool south;
    bool west;
} Crossing;

typedef struct CrossingsStack CrossingsStack, *CrossingsStackPtr;
struct CrossingsStack
{
    Crossing top;
    CrossingsStackPtr next;
};

CrossingsStackPtr stack_init(Point top);
CrossingsStackPtr stack_pop(CrossingsStackPtr stack);
CrossingsStackPtr stack_push(CrossingsStackPtr stack, Point top);
CrossingsStackPtr stack_peek(CrossingsStackPtr stack); //??
