#ifndef FLOODFILL_H
#define FLOODFILL_H

#include "maze.h"

void floodfill(
    Maze *maze,
    const Cell *goals,
    int goalCount
);

#endif