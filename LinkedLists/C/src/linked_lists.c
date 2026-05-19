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

Node* merge(Node* list1, Node* list2) {
    if (list1 == NULL) {
        return list2;
    };
     
    if (list2 == NULL) {
        return list1;
    };

    if (list1->data <= list2->data) {
        list1->next = merge(list1->next, list2);
        return list1;
    } else {
        list2->next = merge(list1, list2->next);
        return list2;
    };


    


};

Node* sort_list(Node* list, int list_size) {
    if (list == NULL || list_size <= 1) {
        return list;
    };

    int mid = list_size/2;
    Node* prev = list;
    for (int i = 0; i < mid-1; i++) {
        prev = prev->next;
    };

    Node* head_right = prev->next;
    prev->next = NULL;

    

    Node* sorted_left = sort_list(list, mid);
    Node* sorted_right = sort_list(head_right, list_size-mid);

    return merge(sorted_left,sorted_right);

    
    
    


};
