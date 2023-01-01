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
        print_row(m.arr[i], m.width);
    }
    
}
bool find_recursive(MazePtr maze, MapPtr map, int offset)
{
    // offset parameter is used to 'memorize' current direction and try it again on each successive iteration
    // this greatly improves efficiency by reducing the amount of calls to the function (you turn less than procees in the same direction)

    // void * fptr = ((void*)map + sizeof(void*) * offset);
    // Move * move_north = (Move *) (fptr);
    // Move move = *move_north;

    // three lines above are equivalent to the conditions below, left for readability and debug
    // this code calls relevant move functions by pointer based on a given offset

    if(!(map->crossings == map->curr) && is_crossroads())
    {
        
    }
    if((*(Move *)((void*)map + sizeof(void*) * offset))(maze, map))
    {
        return find_recursive(maze, map, offset);
    }
    
    for(int i = 0; i < 4; i++)
    {
        // NON_ALIGNED_DIRECTIONS condition holds when index points to a direction that's non-alligned
        // with the direction pointed to by offset parameter, thus avoiding a redundant call in the offset
        // direction (made earlier) and going back the way we came
        if(NON_ALIGNED_DIRECTIONS(offset, i) && ((*(Move *)((void*)map + sizeof(void*) * i))(maze, map)))
        {
            return find_recursive(maze, map, i);
        }
    }

    switch (map->base_direction)
    {

    case NORTH:
        map->north = true;
        (map->base_direction)++;
        stack_pop(map->crossings);

        return find_recursive(maze, map, EAST);
        break;

    case EAST:
        map->east = true;
        (map->base_direction)++;
        stack_pop(map->crossings);

        return find_recursive(maze, map, SOUTH);
        break;

    case SOUTH:
        map->south = true;
        (map->base_direction)++;
        stack_pop(map->crossings);
        
        return find_recursive(maze, map, WEST);
        break;

    default:
        return false;
        break;
    }
}

bool move_north(MazePtr maze, MapPtr map)
{
    return false;
}
bool move_south(MazePtr maze, MapPtr map)
{
    return false;    
    
}
bool move_east(MazePtr maze, MapPtr map)
{
    return false;    
}
bool move_west(MazePtr maze, MapPtr map)
{
    return false;    
    
}

// wrapper-function for find_recursive()
// finds exit from a maze and assigns it's coordinates to the struct pointed to by the position parameter
// returns 1 on success and 0 on failure
bool find_exit(MazePtr maze, PointPtr position)
{
    Point current = *position;
    Point base = *position;
    Map map = { NULL, NULL, NULL, NULL, &current, &base, false, false, false, false, NORTH };
    map.move_north = move_north;
    map.move_south = move_south;
    map.move_east = move_east;
    map.move_west = move_west;

    return find_recursive(maze, &map, 0);
}