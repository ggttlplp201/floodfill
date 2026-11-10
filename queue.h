#ifndef QUEUE_H
#define QUEUE_H

#include "maze.h"

void initQueue(int size);
void enqueue(Cell cell);
Cell dequeue(void);
Cell peek(void);
int isEmpty(void);
void freeQueue(void);

#endif