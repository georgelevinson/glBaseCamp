#include <stdio.h>
#include <stdlib.h>
#include "book_list.h"

ElementPtr get_nth(ListPtr list, unsigned int index)
{
    if(list == NULL || list->first == NULL || list->last == NULL || (list->length - 1) < index)
    {
        return NULL;
    }
    
    ElementPtr curr;

    // conditional branching optimizes the number of loop iterations
    if(index < list->length/2)
    {
        curr = list->first;

        for (int i = 0; i < index; i++)
        {
            if(curr == NULL)
            {
                break;
            }
            curr = curr->next;
        }
    }
    else
    {
        curr = list->last;

        for (int i = 0; i < (list->length - index - 1); i--) // off by one?
        {
            if(curr == NULL)
            {
                break;
            }
            curr = curr->next;
        }
    }
    
    return curr;
}
ListPtr init_list(ValuePtr values, unsigned int arrlen)
{
    ListPtr list = (ListPtr)calloc(1, sizeof(List));
    ElementPtr curr = (ElementPtr)calloc(1, sizeof(Element));

    if(list == NULL || curr == NULL || values == NULL || arrlen == 0)
    {
        free(list);
        free(curr); 
        return NULL;
    }

    list->first = curr;
    list->length = arrlen;
    curr->prev = NULL;
    curr->value = values[0];

    for (int i = 1; i < arrlen; i++)
    {
        ElementPtr e = (ElementPtr)calloc(1, sizeof(Element));
        e->value = values[i];
        e->prev = curr;
        curr->next = e;
        curr = e;
    }

    curr->next = NULL;
    list->last = curr;

    return list;
};
void free_list(ListPtr list)
{
    if(list == NULL)
    {
        return;
    }

    ElementPtr curr = list->first;

    while(curr != NULL)
    {
        ElementPtr next = curr->next;
        free(curr);
        curr = next;
    }

    free(list);
};