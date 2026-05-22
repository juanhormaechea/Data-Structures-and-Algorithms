#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stacks.h"

void push(Stack* stack, int node) {
    if (stack == NULL) {
        return;
    };

    Node* head = stack->head;
    Node* new_head = malloc(sizeof(Node));
    new_head->data = node;
    if (head == NULL) {
        new_head->next = NULL;
        stack->head = new_head;
        stack->size++;
        return;
    };

    new_head->next = head;
    stack->head = new_head;
    stack->size++;
    return;


};



bool pop(Stack* stack, int* popped_value) {
    if (stack == NULL || isEmpty(stack) || popped_value == NULL) {
        return false;
    };

    Node* head = stack->head;

    *popped_value = head->data;
    stack->head = head->next;
    free(head);
    stack->size--;

    return true;


};


bool peek(Stack* stack, int* peek_value) {
    if (stack == NULL || peek_value == NULL || isEmpty(stack)) {
        return false;
    };

    *peek_value = stack->head->data;
    return true;
};


bool isEmpty(Stack* stack) {
    return (stack == NULL || stack->size == 0);
};


int stackSize(Stack* stack) {
    if (stack == NULL || stack->head == NULL) {
        return 0;
    };

    return stack->size;
}