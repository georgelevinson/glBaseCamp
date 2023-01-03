#include <stdlib.h>
#include <stdio.h>
#include "maze.h"

    // void * fptr = ((void*)map + sizeof(void*) * offset);
    // Move * move_north = (Move *) (fptr);
    // Move move = *move_north;

    // three lines above are equivalent to the #define below, left for readability and debug
    // this code calls move functions of map struct by pointer based on a given offset
    // offset parameter is used to 'memorize' current direction and try it again on each successive iteration
    // this greatly improves efficiency by reducing the amount of calls to the function (you turn less than procees in the same direction)

#define MOV_BY_PTR(maze, map, offset) (*(Move *)((void*)map + sizeof(void*) * offset))(maze, map)
#define GET_INT(maze, y) 
#define ARR_LAST_IDX 31

unsigned int get_row(MazePtr maze, int y)
{
    // this "flips" the row sequence such that we can index rows as if they are in the first quadrant of Decart coordinate system 

    // 32         (32,32)
    // ...
    // 5 0 0 0 0
    // 4 0 0 0 0
    // 3 0 0 X 0
    // 2 0 0 0 0
    // 1 2 3 4 5 ... 32

    // so bit X is considered to have coordinates of (4,3) while being the 4th BigEndian bit of integer at maze.arr[31-3]

    int row_no = ARR_LAST_IDX - y; 

    if(row_no < 1)
    {
        return 0;
    }

    return maze->arr[row_no];
}
unsigned short bit_presence_check(unsigned int row, unsigned short bigend_position)
{
    return (row & (UINT32_LAST_BIT >> bigend_position)) ? 1 : 0;
}
void print_row(unsigned int row, unsigned short len)
{
    if(!len)
        len = UINT32_BIT_LEN;
        
    for (int i = 0; i < len; i++)
    {
        printf("    %i", bit_presence_check(row, i));
    }
    printf("\n\n"); 
}
void print_maze(MazePtr maze)
{
    Maze m = *maze;

    for (short i = 0; i < m.height; i++)
    {
        printf("(%02d)", (m.height - i));
        print_row(m.arr[i], m.width);
    }

    printf("     ");

    for (short i = 1; i <= m.width; i++)
    {
        printf("  (%d)", (i%10));
    }

    printf("\n\n");
}

bool goes_north(MazePtr maze, Point position)
{
    if(bit_presence_check(get_row(maze, position.y + 1), position.x))
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool goes_east(MazePtr maze, Point position)
{
    if(bit_presence_check(get_row(maze, position.y), position.x + 1))
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool goes_south(MazePtr maze, Point position)
{
    if(bit_presence_check(get_row(maze, position.y - 1), position.x))
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool goes_west(MazePtr maze, Point position)
{
    if(bit_presence_check(get_row(maze, position.y), position.x - 1))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool is_crossroads(MazePtr maze, Point position)
{
    int result = goes_north(maze, position) + goes_east(maze, position) + goes_south(maze, position) + goes_west(maze, position);

    if(result > 1)
    {
        return true;   
    }
    else
    {
        return false;
    }
}

bool pop_or_drop(MazePtr maze, MapPtr map);

bool find_recursive(MazePtr maze, MapPtr map)
{
    if(map->curr.x == 0 || map->curr.x == (maze->width - 1) || map->curr.y == 0 || map->curr.y == (maze->height - 1))
    {
        return true;
    }
    
    if(!(cmpr_pts(map->crossings->top, map->curr)) && is_crossroads(maze, map->curr))
    {
        stack_push(map->crossings, map->curr);
    }

    if(MOV_BY_PTR(maze, map, map->base_direction))
    {
        return find_recursive(maze, map);
    }
    
    for(int i = 0; i < 4; i++)
    {
        // NON_ALIGNED_DIRECTIONS condition holds when index points to a direction that's non-alligned
        // with the direction pointed to by offset parameter, thus avoiding a redundant call in the offset
        // direction (made earlier) and going back the way we came
        if(NON_ALIGNED_DIRECTIONS(map->base_direction, i) && MOV_BY_PTR(maze, map, i))
        {
            return find_recursive(maze, map);
        }
    }

    switch (map->base_direction)
    {
        case NORTH:
            map->base_direction = EAST;

            return find_recursive(maze, map);
            break;

        case EAST:
            map->base_direction = SOUTH;

            return find_recursive(maze, map);
            break;

        case SOUTH:
            map->base_direction = WEST;
            
            return find_recursive(maze, map);
            break;

        case WEST:
            return pop_or_drop(maze, map);

        default:
            return false;
    }
}

bool pop_or_drop(MazePtr maze, MapPtr map)
{
    CrossingsStackPtr stack = stack_pop(map->crossings);

    if(stack != NULL)
    {
        map->base_direction = NORTH;
        map->curr = stack->top;
                
        return find_recursive(maze, map);
    }
    else
    {
        map->base_direction = -1;
        return false;
    }
}

bool move_north(MazePtr maze, MapPtr map)
{
    if(goes_north(maze, map->curr))
    {
        map->curr.y++;
        return true;
    }
    else
    {
        return false;
    }
}
bool move_south(MazePtr maze, MapPtr map)
{
    if(goes_south(maze, map->curr))
    {
        map->curr.y--;
        return true;
    }
    else
    {
        return false;
    }
}
bool move_east(MazePtr maze, MapPtr map)
{
    if(goes_east(maze, map->curr))
    {
        map->curr.x++;
        return true;
    }
    else
    {
        return false;
    }
}
bool move_west(MazePtr maze, MapPtr map)
{
    if(goes_west(maze, map->curr))
    {
        map->curr.x--;
        return true;
    }
    else
    {
        return false;
    }
}

// wrapper-function for find_recursive()
// finds exit from a maze and assigns it's coordinates to the struct pointed to by the position parameter
// returns 1 on success and 0 on failure
bool find_exit(MazePtr maze, Point start)
{
    Map map = { NULL, NULL, NULL, NULL, start, stack_init(start), NORTH };
    map.move_north = move_north;
    map.move_south = move_south;
    map.move_east = move_east;
    map.move_west = move_west;

    return find_recursive(maze, &map);
}