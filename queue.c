#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

static Cell *queue = NULL;
static int front = 0;
static int rear = 0;
static int count = 0;
static int capacity = 0;

void initQueue(int size) {
    if (size <= 0) {
        fprintf(stderr, "Invalid queue size\n");
        exit(EXIT_FAILURE);
    }

    free(queue);

    queue = malloc((size_t)size * sizeof(Cell));

    if (queue == NULL) {
        fprintf(stderr, "Queue allocation failed\n");
        exit(EXIT_FAILURE);
    }

    capacity = size;
    front = 0;
    rear = 0;
    count = 0;
}

void enqueue(Cell cell) {
    if (count == capacity) {
        fprintf(stderr, "Queue is full\n");
        exit(EXIT_FAILURE);
    }

    queue[rear] = cell;
    rear = (rear + 1) % capacity;
    count++;
}

Cell dequeue(void) {
    if (isEmpty()) {
        fprintf(stderr, "Queue is empty\n");
        exit(EXIT_FAILURE);
    }

    Cell cell = queue[front];
    front = (front + 1) % capacity;
    count--;

    return cell;
}

Cell peek(void) {
    if (isEmpty()) {
        fprintf(stderr, "Queue is empty\n");
        exit(EXIT_FAILURE);
    }

    return queue[front];
}

int isEmpty(void) {
    return count == 0;
}

void freeQueue(void) {
    free(queue);

    queue = NULL;
    front = 0;
    rear = 0;
    count = 0;
    capacity = 0;
}