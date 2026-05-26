#include <stdbool.h>
#include <stdint.h>
#ifndef HASHMAP_H
#define HASHMAP_H
typedef struct Node Node;
typedef struct HashMap HashMap;

struct Node {
  int data[2];
  Node *next;
};

struct HashMap {
  Node **map;
  int num_elements;
  int size;
  double max_load_factor;
};

HashMap *hashmap_create(int initial_size, double max_load_factor);

void hashmap_destroy(HashMap *map);

bool hashmap_add(HashMap *map, int key, int value);

bool hashmap_remove(HashMap *map, int key);

void hashmap_resize(HashMap *map);

bool hashmap_get(HashMap *map, int key, int *retrieved_value);

uint32_t knuth_hash(int key);

#endif