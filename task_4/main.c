#include "maze.h" 

int main(void)
{
    Maze maze;
    Point spawn;

    spawn.x = 0;
    spawn.y = 0;
    maze.height = 0;
    maze.width = 0;
    maze.spawn = spawn;

    find_exit(&maze, &spawn);

    return 0;
}