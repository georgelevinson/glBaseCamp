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

#define MOV_BY_PTR(maze, map, offset) (*(Move *)((void*)map + sizeof(void*) * offset))(maze, map) // - why do I need to multiply by sizeof tho??
#define ARR_LAST_IDX 31

static const Point empty;

unsigned int get_row(MazePtr maze, int y)
{
    
    // this "flips" the row sequence such that we can index rows as if they are in the first quadrant of Decart coordinate system 

    // 31         (32,32)
    // ...
    // 5 0 0 0 0 0
    // 4 0 0 0 0 0
    // 3 0 0 X 0 0
    // 2 0 0 0 0 0
    // 1 0 0 0 0 0
    // 0 1 2 3 4 5 ... 31

    // so bit X is considered to have coordinates of (4,3) while being the 4th BigEndian bit of integer at maze.arr[31-3]

    int row_no = ARR_LAST_IDX - y; 

    if(row_no < 0)
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
        printf("(%02d)", (m.height - i - 1));
        print_row(m.arr[i], m.width);
    }

    printf("     ");

    for (short i = 0; i < m.width; i++)
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

bool check_crossroads(MazePtr maze, MapPtr map)
{
    bool nesw[4];
    nesw[0] = goes_north(maze, map->curr);
    nesw[1] = goes_east(maze, map->curr);
    nesw[2] = goes_south(maze, map->curr);
    nesw[3] = goes_west(maze, map->curr);

    if(nesw[0] + nesw[1] + nesw[2] + nesw[3] > 2)
    {
        stack_push(map);
        unsigned opdir = (map->base_direction + 2) > 3 ? map->base_direction % 2 : map->base_direction + 2;

        for(unsigned i = 0; i < 4; i++)
        {
            // accessing struct members by offset pointer
            // the NON_ALLIGNED_DIRECTIONS() condition exclueds the direction that we approached
            // the crossing from as well as the one that we're gonna continue moving in
            // (which, from the point of view of the crossing, are opposite)
            
            *((bool*)(map->crossings) + i) = nesw[i] && (NON_ALIGNED_DIRECTIONS(map->base_direction, i));
        }


        return true;
    }
    else
    {
        return false;
    }
}

bool pop_or_drop(MazePtr maze, MapPtr map);

// recursively finds exit from a maze and assigns it's coordinates to the struct pointed to by the position parameter
bool find_recursive(MazePtr maze, MapPtr map)
{
    print_point(map->curr);

    if(map->curr.x == 0 || map->curr.x == (maze->width - 1) || map->curr.y == 0 || map->curr.y == (maze->height - 1))
    {
        maze->exit = map->curr;
        return true;
    }

    if(!cmpr_pts(map->crossings->top, map->curr)) // to avoid excess crossings on start and and endless loop on return to point for another turn
    {
        check_crossroads(maze, map);
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
        if(NON_ALIGNED_DIRECTIONS(map->base_direction, i) && cmpr_pts((map->curr), (map->crossings->top)) && MOV_BY_PTR(maze, map, i))
        {
            // this conditional branch is needed to handle the case when there's a turn at a crossroad
            // the direction bool has to be updated to avoid an infinite loop
            *((bool*)(map->crossings) + i) = false;
            map->base_direction = i;
            
            return find_recursive(maze, map);
        }
        else if(NON_ALIGNED_DIRECTIONS(map->base_direction, i) && MOV_BY_PTR(maze, map, i))
        {
            map->base_direction = i;
            
            return find_recursive(maze, map);
        }
    }

    // at this point we, based on the previously checked conditions must be in a dead end somewhere 
    // and must return to either previous crossing or the one before that (in case we've just gone down the last split of the previous one)
    if(map->crossings->north)
    {
        map->curr = map->crossings->top;
        map->crossings->north = false;
        map->base_direction = NORTH;

        return find_recursive(maze, map);
    }
    else if(map->crossings->east)
    {
        map->curr = map->crossings->top;
        map->crossings->east = false;
        map->base_direction = EAST;

        return find_recursive(maze, map);
    }
    else if(map->crossings->south)
    {
        map->curr = map->crossings->top;
        map->crossings->south = false;
        map->base_direction = SOUTH;

        return find_recursive(maze, map);
    }
    else if(map->crossings->west)
    {
        map->curr = map->crossings->top;
        map->crossings->west = false;
        map->base_direction = WEST;

        return find_recursive(maze, map);
    }
    else
    {
        return pop_or_drop(maze, map);
    }
}

bool pop_or_drop(MazePtr maze, MapPtr map)
{
    do
    {
        map->crossings = stack_pop(map->crossings);
    } 
    while(map->crossings != NULL && !(map->crossings->north || map->crossings->east || map->crossings->south || map->crossings->west));

    if(map->crossings != NULL)
    {
        map->base_direction = NORTH * map->crossings->north + EAST * map->crossings->east + 
                              SOUTH * map->crossings->south + WEST * map->crossings->west;
        map->curr = map->crossings->top;

        return find_recursive(maze, map);
    }
    else
    {
        map->base_direction = -1; // might cause segfault?? - need to check
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
// initializes structures needed for recursive() to run and calls it
// returns 1 on success and 0 on failure
bool find_exit(MazePtr maze, Point start, int init_direction)
{
    Map map = { NULL, NULL, NULL, NULL, start, stack_init(start), init_direction };

    check_crossroads(maze, &map);

    map.move_north = move_north;
    map.move_south = move_south;
    map.move_east = move_east;
    map.move_west = move_west;

    return find_recursive(maze, &map);
}