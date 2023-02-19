#include <stdlib.h>
#include <stdio.h>
#include "maze.h"

CrossingsStackPtr stack_init(Point top)
{
    CrossingsStackPtr result = calloc(1, sizeof(CrossingsStack));
    (*result).top = top;
    // (*result).next = NULL; - calloc should allocate zeroed-out memory anyway

    return result;
};
CrossingsStackPtr stack_pop(CrossingsStackPtr stack)
{
    if(stack == NULL)
        return stack;

    CrossingsStackPtr top = stack->next;
    free(stack);
    return top;
};
bool stack_push(MapPtr map)
{
    if(map == NULL || map->crossings == NULL)
    {
        printf("\n\nInvalid data passed to stack_push()\n\n");
        return false;
    }
    
    CrossingsStackPtr result = stack_init(map->curr);
    result->next = map->crossings;
    map->crossings = result;

    return true;
};
CrossingsStackPtr stack_peek(CrossingsStackPtr stack)
{

};
