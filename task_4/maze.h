#include <stdbool.h>
#include "stack.h"
#define UINT32_BIT_LEN 32
#define UINT32_LAST_BIT 2147483648

#define NON_ALIGNED_DIRECTIONS(offset, index) ((offset % 2) != i)
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

// all types and functions for task (including the exit search algorithm) will be implemented with the following 
// presumptions about the maze in mind: 

// maze has one and only one exit 
// (which, given the dimensions of the maze, is defined as a zero bit in place of an expected one)

// regardless of starting point, there must be one and only one path to the exit,
// such that any given rout either leads to the exit or to a dead end

// passage width must be equal to one


typedef struct Maze
{
    int arr[UINT32_BIT_LEN];
    unsigned short height;
    unsigned short width;
    Point spawn;
} Maze, *MazePtr;

struct Map;
typedef bool (*Move)(MazePtr maze, struct Map * m);

struct Map 
{
    Move move_north;
    Move move_east;
    Move move_south;
    Move move_west;
    
    PointPtr curr;
    CrossingsStackPtr crossings;

    bool north;
    bool east;
    bool south;
    bool west;
    int base_direction; // - indicates the current direction that's being tried
};
typedef struct Map Map, *MapPtr;

void print_maze(MazePtr maze);
bool find_exit(MazePtr maze, PointPtr position);

// 11111111111111110000000000000000
// 10100000000001010000000000000000
// 10111101111011010000000000000000
// 10000001000000010000000000000000
// 11111111101101110000000000000000
// 10100000001000010000000000000000
// 10001111101111110000000000000000
// 11100100001000010000000000000000
// 10001111111101010000000000000000
// 11100000100001110000000000000000
// 10001110101100010000000000000000
// 10100010001111110000000000000000
// 10101111111000010000000000000000
// 10111010000011010000000000000000
// 10000000110110010000000000000000
// 11111111111110110000000000000000
