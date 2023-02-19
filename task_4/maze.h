#include "point.h"

#define UINT32_BIT_LEN 32
#define UINT32_LAST_BIT 2147483648

#define NON_ALIGNED_DIRECTIONS(offset, index) ((offset % 2) != (i % 2))
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
    unsigned int arr[UINT32_BIT_LEN];
    unsigned short height;
    unsigned short width;
    Point spawn;
    Point exit;
} Maze, *MazePtr;

struct Map;
typedef bool (*Move)(MazePtr maze, struct Map * m);
typedef struct CrossingsStack CrossingsStack, *CrossingsStackPtr;

struct CrossingsStack
{
    bool north;
    bool east;
    bool south;
    bool west;
    
    Point top;
    CrossingsStackPtr next;
};
struct Map 
{
    Move move_north;
    Move move_east;
    Move move_south;
    Move move_west;
    
    Point curr;
    CrossingsStackPtr crossings;
    int base_direction;
};
typedef struct Map Map, *MapPtr;

bool stack_push(MapPtr map);
CrossingsStackPtr stack_init(Point top);
CrossingsStackPtr stack_pop(CrossingsStackPtr stack);
CrossingsStackPtr stack_peek(CrossingsStackPtr stack); // ??

void print_maze(MazePtr maze);
bool find_exit(MazePtr maze, Point start, int init_direction);

// 11111111111111110000000000000000 = 4294901760
// 10100000000001010000000000000000 = 2684682240
// 10111101111011010000000000000000 = 3186425856
// 10000001000000010000000000000000 = 2164326400
// 11111111101101110000000000000000 = 4290183168
// 10100000001000010000000000000000 = 2686517248
// 10001111101111110000000000000000 = 2411659264
// 11100100001000010000000000000000 = 3827367936
// 10001111111101010000000000000000 = 2415198208
// 11100000100001110000000000000000 = 3766943744
// 10001110101100010000000000000000 = 2393964544
// 10100010001111110000000000000000 = 2722037760
// 10101111111000010000000000000000 = 2950758400
// 10111010000011010000000000000000 = 3121414144
// 10000000110110010000000000000000 = 2161704960
// 11111111111110110000000000000000 = 4294639616
