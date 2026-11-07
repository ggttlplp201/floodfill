#include "queue.h"

int queue[256];
int front = 0;
int rear = 0;

void enqueue(int value) {
    queue[rear++] = value;
}

int dequeue() {
    return queue[front++];
}

int peek() {
    return queue[front];
}