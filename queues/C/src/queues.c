#include <stdlib.h>
#include <stdbool.h>
#include "queues.h"

void enqueue(Queue* queue, int element) {
    if (queue == NULL) {
        return;
    };

    Node* new_element = malloc(sizeof(Node));
    new_element->data = element;
    new_element->next = NULL;
    if (queue->back == NULL) {
        queue->back = new_element;
        queue->front = new_element;
        queue->size++;
        return;
    };

    queue->back->next = new_element;
    queue->back = new_element;
    queue->size++;
    return;
};


bool dequeue(Queue* queue, int* dequeued_value) {
    if (queue == NULL || queue->front == NULL) {
        return false;
    };

    *dequeued_value = queue->front->data;
    Node* next = queue->front->next;
    free(queue->front);
    queue->front = next;
    queue->size--;
    return true;
};


bool peek(Queue* queue, int* peeked_value) {
    if (queue == NULL || queue->front == NULL) {
        return false;
    };

    *peeked_value = queue->front->data;
    return true;
};

bool isEmpty(Queue* queue) {
    if (queue == NULL) {
        return true;
    };

    return (queue->size == 0);
};


int queueSize(Queue* queue) {
    if (queue == NULL) {
        return 0;
    };

    return queue->size;
};

