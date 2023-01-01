#include <stdio.h>
#include "point.h"

typedef struct CrossingsStack CrossingsStack, *CrossingsStackPtr;
struct CrossingsStack
{
    Point top;
    CrossingsStackPtr next;
};

CrossingsStackPtr stack_init(Point top);
CrossingsStackPtr stack_pop(CrossingsStackPtr stack);
CrossingsStackPtr stack_push(CrossingsStackPtr stack, Point top);
CrossingsStackPtr stack_peek(CrossingsStackPtr stack); //??
