#include <stdlib.h>
#include "maze.h"

Maze *createMaze(int width, int height) {
    if (width <= 0 || height <= 0) {
        return NULL;
    }

    Maze *maze = malloc(sizeof(Maze));

    if (maze == NULL) {
        return NULL;
    }

    maze->width = width;
    maze->height = height;

    // allocate row pointers
    maze->distances = calloc(height, sizeof(int *));
    maze->walls = calloc(height, sizeof(unsigned char *));

    if (maze->distances == NULL || maze->walls == NULL) {
        free(maze->distances);
        free(maze->walls);
        free(maze);
        return NULL;
    }

    // allocate each row
    for (int row = 0; row < height; row++) {
        maze->distances[row] = malloc(width * sizeof(int));
        maze->walls[row] = calloc(width, sizeof(unsigned char));

        if (maze->distances[row] == NULL ||
            maze->walls[row] == NULL) {

            for (int i = 0; i <= row; i++) {
                free(maze->distances[i]);
                free(maze->walls[i]);
            }

            free(maze->distances);
            free(maze->walls);
            free(maze);

            return NULL;
        }

        // init distances
        for (int col = 0; col < width; col++) {
            maze->distances[row][col] = -1;
        }
    }

    // init boundary walls
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {

            if (row == height - 1)
                maze->walls[row][col] |= NORTH;

            if (row == 0)
                maze->walls[row][col] |= SOUTH;

            if (col == width - 1)
                maze->walls[row][col] |= EAST;

            if (col == 0)
                maze->walls[row][col] |= WEST;
        }
    }

    return maze;
}

int isValidCell(const Maze *maze, int row, int col) {
    return maze != NULL &&
           row >= 0 && row < maze->height &&
           col >= 0 && col < maze->width;
}

void addWall(
    Maze *maze,
    int row,
    int col,
    Direction direction
) {
    if (!isValidCell(maze, row, col)) {
        return;
    }

    // add wall to current cell
    maze->walls[row][col] |= direction;

    // add opposite wall to neighboring cell
    switch (direction) {
        case NORTH:
            if (isValidCell(maze, row + 1, col))
                maze->walls[row + 1][col] |= SOUTH;
            break;

        case EAST:
            if (isValidCell(maze, row, col + 1))
                maze->walls[row][col + 1] |= WEST;
            break;

        case SOUTH:
            if (isValidCell(maze, row - 1, col))
                maze->walls[row - 1][col] |= NORTH;
            break;

        case WEST:
            if (isValidCell(maze, row, col - 1))
                maze->walls[row][col - 1] |= EAST;
            break;
    }
}

void freeMaze(Maze *maze) {
    if (maze == NULL) {
        return;
    }

    for (int row = 0; row < maze->height; row++) {
        free(maze->distances[row]);
        free(maze->walls[row]);
    }

    free(maze->distances);
    free(maze->walls);
    free(maze);
}