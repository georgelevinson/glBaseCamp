#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_list.h"

#define MAX_BOOKDATA_STRLEN 350

ElementPtr get_nth(ListPtr list, unsigned int index)
{
    if(list == NULL || list->first == NULL || list->last == NULL || (list->length - 1) < index)
    {
        return NULL;
    }
    
    ElementPtr curr = NULL;

    // conditional branching optimizes the number of loop iterations
    if(index <= list->length/2)
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

        for (int i = 0; i < (list->length - index - 1); i++) // off by one?
        {
            if(curr == NULL)
            {
                break;
            }
            curr = curr->prev;
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
void free_list(ListPtr * list)
{
    if(*list == NULL)
    {
        return;
    }

    ElementPtr curr = (*list)->first;

    while(curr != NULL)
    {
        ElementPtr next = curr->next;
        free(curr);
        curr = next;
    }

    free(*list);
    *list = NULL;
};
int delete_nth(ListPtr list, unsigned int index)
{
    ElementPtr nth = get_nth(list, index);

    if(nth == NULL)
    {
        printf("\n\rdelete_nth has failed: index out of range.\n\r");
        return 0;
    }

    if(nth->prev == NULL)
    {
        list->first = nth->next;
    }
    else
    {
        nth->prev->next = nth->next;
    }
    if(nth->next == NULL)
    {
        list->last = nth->prev;
    }
    else
    {
        nth->next->prev = nth->prev;
    }

    --(list->length);

    free(nth);

    return 1;
};
// this function sews two lists at a given joint element, thus src->first becomes [dest_index]`th element of dest list,
// while the rest of dest (meaning elements starting with the original [dest_index]`th element) gets appended to the end of resulting list
int insert_elements(ListPtr * src_ptr, ListPtr dest, unsigned int dest_index)
{
    if((*src_ptr) == NULL)
    {
        printf("Invalid src list passed to merge_lists.\n\r");
        return 0;
    }

    ElementPtr prev = get_nth(dest, dest_index - 1);
    ElementPtr joint = get_nth(dest, dest_index);

    if(joint == NULL && prev == NULL)
    {
        printf("Invalid destination list or an out of range index passed to merge_lists.\n\r");
        return 0;
    }
    
    (*src_ptr)->first->prev = prev;

    if(prev != NULL)
    {
        prev->next = (*src_ptr)->first;
    }
    else
    {
        dest->first = (*src_ptr)->first;
    }

    (*src_ptr)->last->next = joint;

    if(joint != NULL)
    {
        joint->prev = (*src_ptr)->last;
    }
    else
    {
        dest->last = (*src_ptr)->last;
    }

    dest->length += (*src_ptr)->length;

    free(*src_ptr);
    *src_ptr = NULL;

    return 1;
};
int append_elements(ListPtr * src_ptr, ListPtr dest)
{
    return insert_elements(src_ptr, dest, dest->length);
};
char * bookdata_tostring(Value value)
{
    char * result = (char*)calloc(MAX_BOOKDATA_STRLEN, sizeof(char));

    sprintf(result, "\n\rBook Name: %s;\n\rPublication year: %i;\n\rNo.Pages: %i;\n\rLanguage: %s;\n\rBook Price: %f;\n\rBook Weight: %f;\n\r", value.name, value.year, value.pages, value.lang, value.price_GBP, value.weight_kg);

    return (char*)realloc(result, sizeof(char) * (strlen(result) + 1));
}
void print_list(ListPtr list)
{
    printf("\n\r\n\rCURRENT LIST\n\r\n\r");

    if(list == NULL)
    {
        printf("[ NULL ] \n\r\n\r");
        return;
    }

    ElementPtr curr = list->first;

    for (int i = 0; i < list->length; i++)
    {
        if(curr == NULL)
        {
            break;
        }

        char * curr_str = bookdata_tostring(curr->value);

        printf("[(Previous element: %s) %s (Next element: %s)]  \n\r\n\r", curr->prev == NULL ? "NULL" : curr->prev->value.name, curr_str, curr->next == NULL ? "NULL" : curr->next->value.name);

        free(curr_str);

        curr = curr->next;
    }
    printf("\n\rLIST LENGTH: %i", list->length);
    printf("\n\r\n\r");
};