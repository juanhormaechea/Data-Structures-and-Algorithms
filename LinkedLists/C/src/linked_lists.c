#include <stdio.h>
#include <stdlib.h>
#include "linked_lists.h"

int size(LinkedList* list) {
    if (list == NULL || list->head == NULL) {
        return 0;
    }

    int size = 0;

    Node* next = list->head;
    while (next != NULL) {
        size++;
        next = next->next;
    };

    return size;
};

Node* insert_node(LinkedList* list, int node, int index) {
    if (list == NULL || index < 0) {
        return NULL;
    };

    Node* head = list->head;

    if (index == 0) {
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
    for (int i = 0; i < index-1; i++) {
        if (next->next == NULL) {
            break;
        }

        next = next->next;
    }


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

void remove_node(LinkedList* list, int node) {
    if (list == NULL || list->head == NULL) {
        return;
    };

    Node* head = list->head;
    Node* next = head->next;

    if (head->data == node) {
        list->head = next;
        free(head);
        return;
    };

    while (next != NULL) {
        if(next->data == node) {
            head->next = next->next;
            free(next);
            return;
        };
        head = next;
        next = next->next;
    };

    

    return;
};

Node* search_node(LinkedList* list, int node) {
    if (list == NULL) {
        return NULL;
    };
    
    Node* head = list->head;
    while (head != NULL) {
        if (head->data == node) {
            return head;
        };

        head = head->next;
    };

    return NULL;
};

