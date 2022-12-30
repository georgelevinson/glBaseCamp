#include <stdlib.h>
#include <stdio.h>
#include "maze.h"

unsigned short bit_presence_check(unsigned int row, unsigned short bigend_position)
{
    return (row & (UINT32_LAST_BIT >> bigend_position)) ? 1 : 0;
}
void print_row(unsigned int row, unsigned short len)
{
    if(!len)
        len = UINT32_BIT_LEN;
        
    printf("\n\n");
    for (int i = 0; i < len; i++)
    {
        if(i%4 == 0)
        {
            printf("  ");
        }
        
        printf("%i", bit_presence_check(row, len));
    }
    printf("\n\n"); 
}
void print_maze(MazePtr maze)
{
    Maze m = *maze;

    for (short i = 0; i < m.height; i++)
    {
        print_row(m.arr, m.width);
    }
    
}
