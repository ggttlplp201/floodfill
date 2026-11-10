#ifndef MAZE_H
#define MAZE_H

typedef struct {
    int x;
    int y;
} Cell;

typedef struct {
    int width;
    int height;
    int **distances;
    unsigned char **walls;
} Maze;

typedef enum {
    NORTH = 0x8,
    EAST  = 0x4,
    SOUTH = 0x2,
    WEST  = 0x1
} Direction;

#endif