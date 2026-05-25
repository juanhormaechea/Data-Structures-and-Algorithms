#include <stdbool.h>
#include <stdint.h>
#ifndef HASHSET_H
#define HASHSET_H
typedef struct Node Node;
typedef struct HashSet HashSet;

struct Node {
    int data;
    Node* next;
};

struct HashSet {
    Node** set;
    int size;
    int num_elements;
    double max_load_factor = 0.75;
};

HashSet* hashset_create(int initial_size, double max_load_factor);

void hashset_destroy(HashSet* set);

bool hashset_add(HashSet* set, int value);

bool hashset_remove(HashSet* set, int value);

bool hashset_contains(HashSet* set, int value);

uint32_t knuth_hash(int value);

void hashset_resize(HashSet* set);



#endif