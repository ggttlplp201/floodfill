#include "queue.h"
#include "maze.h"

void floodfill(Maze *maze, const Cell *goals, int goalCount) {

    initQueue(maze->width * maze->height);

    //init maze
    for (int y = 0; y < maze->height; y++) {
        for (int x = 0; x < maze->width; x++) {
            maze->distances[y][x] = -1;
        }
    }

    //Queue goal cells
    for (int i = 0; i < goalCount; i++) {
        Cell goal = goals[i];

        maze->distances[goal.y][goal.x] = 0;
        enqueue(goal);
    }

    //BFS to check neighbours
    while (!isEmpty()) {
        Cell current = dequeue();

        int x = current.x;
        int y = current.y;

        //process each direction
        processNeighbour(maze, current, (Cell){x, y + 1}, NORTH);
        processNeighbour(maze, current, (Cell){x + 1, y}, EAST);
        processNeighbour(maze, current, (Cell){x, y - 1}, SOUTH);
        processNeighbour(maze, current, (Cell){x - 1, y}, WEST);

        
    }

    freeQueue();
}

static void processNeighbour(Maze *maze, Cell current, Cell neighbour, Direction direction){
    if (neighbour.x < 0 || neighbour.x >= maze->width || neighbour.y < 0 || neighbour.y >= maze->height){ //check if out of bounds
        return;
    }
    
    if (maze->walls[current.x][current.y] & direction){ //check if wall is blocking
        return;
    }

    if (maze->distances[neighbour.x][neighbour.y] != -1){ //check if already visited
        return;
    }

    enqueue(neighbour);
}