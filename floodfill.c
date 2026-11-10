#include <stddef.h>
#include "floodfill.h"
#include "queue.h"

static void processNeighbour(Maze *maze, Cell current, Cell neighbour, Direction direction) {
    // check boundaries
    if (!isValidCell(maze, neighbour.row, neighbour.col)) {
        return;
    }

    // check walls
    if (maze->walls[current.row][current.col] & direction) {
        return;
    }

    // check if visited
    if (maze->distances[neighbour.row][neighbour.col] != -1) {
        return;
    }

    // update
    maze->distances[neighbour.row][neighbour.col] =
        maze->distances[current.row][current.col] + 1;

    // add neighbor
    enqueue(neighbour);
}

void floodfill(Maze *maze, const Cell *goals, int goalCount) {
    if (maze == NULL || goals == NULL || goalCount <= 0) {
        return;
    }

    initQueue(maze->width * maze->height);

    // init maze
    for (int row = 0; row < maze->height; row++) {
        for (int col = 0; col < maze->width; col++) {
            maze->distances[row][col] = -1;
        }
    }

    // init goal cells
    for (int i = 0; i < goalCount; i++) {
        Cell goal = goals[i];

        if (!isValidCell(maze, goal.row, goal.col)) {
            continue;
        }

        if (maze->distances[goal.row][goal.col] == 0) {
            continue;
        }

        maze->distances[goal.row][goal.col] = 0;
        enqueue(goal);
    }

    // BFS
    while (!isEmpty()) {
        Cell current = dequeue();

        int row = current.row;
        int col = current.col;

        processNeighbour(maze, current, (Cell){row + 1, col}, NORTH);
        processNeighbour(maze, current, (Cell){row, col + 1}, EAST);
        processNeighbour(maze, current, (Cell){row - 1, col}, SOUTH);
        processNeighbour(maze, current, (Cell){row, col - 1}, WEST);
    }

    freeQueue();
}