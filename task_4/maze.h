#define UINT32_BIT_LEN 32
#define UINT32_LAST_BIT 2147483648

// all types and functions for task (including the exit search algorithm) will be implemented with the following 
// presumptions about the maze in mind: 

// maze has one and only one exit 
// (which, given the dimensions of the maze, is defined as a zero bit in place of an expected one)

// regardless of starting point, there must be one and only one path to the exit,
// such that any given rout either leads to the exit or to a dead end

// passage width must be equal to one

typedef struct point
{
    unsigned short x;
    unsigned short y;
} Point, *PointPtr;
typedef struct maze
{
    int arr[UINT32_BIT_LEN];
    unsigned short height;
    unsigned short width;
    Point spawn;
} Maze, *MazePtr;

void print_maze(MazePtr maze);

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
