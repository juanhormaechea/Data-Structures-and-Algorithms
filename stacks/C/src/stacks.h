#include <stdbool.h>
#ifndef STACKS_H
#define STACKS_H
typedef struct Node Node;
typedef struct Stack Stack;

struct Node {
    int data;
    Node* next;
};


struct Stack {
    Node* head;
    int size;
};

void push(Stack* stack, int node);

bool pop(Stack* stack, int* popped_value);

bool peek(Stack* stack, int* peek_value);

bool isEmpty(Stack* stack);

int stackSize(Stack* stack);


#endif