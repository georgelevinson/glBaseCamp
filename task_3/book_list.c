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
int delete_nth(ListPtr list, unsigned int index)
{
    ElementPtr nth = get_nth(list, index);

    if(nth == NULL)
    {
        printf("\ndelete_nth has failed: index out of range.\n");
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
int insert_elements(ListPtr src, ListPtr dest, unsigned int dest_index)
{
    if(src == NULL)
    {
        printf("Invalid src list passed to merge_lists.\n");
        return 0;
    }

    ElementPtr prev = get_nth(dest, dest_index - 1);
    ElementPtr joint = get_nth(dest, dest_index);

    if(joint == NULL && prev == NULL)
    {
        printf("Invalid destination list or an out of range index passed to merge_lists.\n");
        return 0;
    }
    
    src->first->prev = prev;

    if(prev != NULL)
    {
        prev->next = src->first;
    }
    else
    {
        dest->first = src->first;
    }

    src->last->next = joint;

    if(joint != NULL)
    {
        joint->prev = src->last;
    }
    else
    {
        dest->last = src->last;
    }

    dest->length += src->length;

    free(src);
    return 1;
};
int append_elements(ListPtr src, ListPtr dest)
{
    return insert_elements(src, dest, dest->length);
};
char * bookdata_tostring(Value value)
{
    char * result = (char*)calloc(MAX_BOOKDATA_STRLEN, sizeof(char));

    sprintf(result, "\n\r\n\rBook Name: %s;\n\rPublication year: %i;\n\rNo.Pages: %i;\n\rLanguage: %s;\n\rBook Price: %f;\n\rBook Weight: %f;", value.name, value.year, value.pages, value.lang, value.price_GBP, value.weight_kg);

    return (char*)realloc(result, sizeof(char) * (strlen(result) + 1));
}
void print_list(ListPtr list)
{
    printf("\n\nCURRENT LIST\n\n");

    if(list == NULL)
    {
        printf("\n\n [ NULL ] \n\n");
    }

    ElementPtr curr = list->first;

    printf("\n");

    for (int i = 0; i < list->length; i++)
    {
        if(curr == NULL)
        {
            break;
        }

        char * curr_str = bookdata_tostring(curr->value);

        printf("[(%s) %s (%s)]  ", curr->prev == NULL ? "NULL" : curr->prev->value.name, curr_str, curr->next == NULL ? "NULL" : curr->next->value.name);

        free(curr_str);

        curr = curr->next;
    }
    printf("\nLIST LENGTH: %i", list->length);
    printf("\n\n");
};