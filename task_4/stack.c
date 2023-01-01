#include <stdlib.h>
#include "stack.h"

CrossingsStackPtr stack_init(Point top)
{
    CrossingsStackPtr result = calloc(1, sizeof(CrossingsStack));
    (*result).top = top;
    (*result).next = NULL;

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
CrossingsStackPtr stack_push(CrossingsStackPtr stack, Point top)
{
    if(stack == NULL)
    {
        printf("Empty stack passed to stack_push()");
        return NULL;
    }
    
    CrossingsStackPtr result = stack_init(top);
    result->next = stack;

    return result;
};
CrossingsStackPtr stack_peek(CrossingsStackPtr stack)
{

};
