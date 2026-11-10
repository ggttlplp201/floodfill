#ifndef MAZE_H
#define MAZE_H

typedef struct {
    int row;
    int col;
} Cell;

typedef enum {
    NORTH = 0x8,
    EAST  = 0x4,
    SOUTH = 0x2,
    WEST  = 0x1
} Direction;

typedef struct {
    int width;
    int height;
    int **distances;
    unsigned char **walls;
} Maze;

Maze *createMaze(int width, int height);
void freeMaze(Maze *maze);

int isValidCell(const Maze *maze, int row, int col);

void addWall(
    Maze *maze,
    int row,
    int col,
    Direction direction
);

#endif