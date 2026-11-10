#include "queue.h"
#include "maze.h"

void floodfill(Maze *maze, const Cell *goals, int goalCount) {

    initQueue(maze->width * maze->height);

    for (int y = 0; y < maze->height; y++) {
        for (int x = 0; x < maze->width; x++) {
            maze->distances[y][x] = -1;
        }
    }

    for (int i = 0; i < goalCount; i++) {
        Cell goal = goals[i];

        maze->distances[goal.y][goal.x] = 0;
        enqueue(goal);
    }

    while (!isEmpty()) {
        Cell current = dequeue();

        int x = current.x;
        int y = current.y;

        processNeighbour(maze, current,
                         (Cell){x, y + 1}, NORTH);

        processNeighbour(maze, current,
                         (Cell){x + 1, y}, EAST);

        processNeighbour(maze, current,
                         (Cell){x, y - 1}, SOUTH);

        processNeighbour(maze, current,
                         (Cell){x - 1, y}, WEST);
    }

    freeQueue();
}