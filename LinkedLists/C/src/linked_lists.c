#include <stdio.h>
#include <stdlib.h>
#include "linked_lists.h"

Node* insert_node(LinkedList* list, int node, int position) {
    if (list == NULL || position < 1) {
        return NULL;
    };

    Node* head = list->head;

    if (position == 1) {
        Node* new_node = malloc(sizeof(Node));
        if(!new_node) {
            perror("malloc failed");
            exit(1);
        };
        new_node->data = node;
        new_node->next = head;
        list->head = new_node;
        return new_node;
    };

    Node* next = head;
    for (int i = 2; i < node; i++) {
        if (next->next != NULL) {
            next = next->next;
        } else {
            break;
        };
    };


    Node* new_node = malloc(sizeof(Node));
    if(!new_node) {
        perror("malloc failed");
        exit(1);
    }
    new_node->data = node;
    new_node->next = next->next;
    next->next = new_node;
    return new_node;


}

