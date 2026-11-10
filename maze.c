#include <stdlib.h>
#include "maze.h"

Maze *createMaze(int width, int height){
    Maze *maze = malloc(sizeof(Maze));

    if(maze == NULL){
        return NULL;
    }

    maze->width = width;
    maze->height = height;

    return maze;
}