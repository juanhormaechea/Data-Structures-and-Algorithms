#ifndef LINKED_LISTS_H
#define LINKED_LISTS_H

typedef struct Node Node;
typedef struct LinkedList LinkedList;


struct Node {
    int data;
    Node* next;
};

struct LinkedList {
    Node* head;
};

Node* insert_node(LinkedList* list, int node, int index);

int size(LinkedList* list);

void remove_node(LinkedList* list, int node);

Node* search_node(LinkedList* list, int node);

Node* sort_list(Node* list, int size);




#endif