#include <stdbool.h>
#ifndef QUEUES_H
#define QUEUES_H
typedef struct Node Node;
typedef struct Queue Queue;

struct Node {
    int data;
    Node* next;
};

struct Queue {
    Node* front;
    Node* back;
    int size;
};

void enqueue(Queue* queue, int element);

bool dequeue(Queue* queue, int* dequeued_value);

bool peek(Queue* queue, int* peeked_value);

bool isEmpty(Queue* queue);

int queueSize(Queue* queue);



#endif