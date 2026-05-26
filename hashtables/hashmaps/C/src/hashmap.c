#include "hashmap.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

HashMap *hashmap_create(int initial_size, double max_load_factor) {
  if (initial_size <= 0 || (initial_size & (initial_size - 1)) != 0) {
    return NULL;
  };

  HashMap *new_map = malloc(sizeof(HashMap));

  if (new_map == NULL) {
    return NULL;
  };

  Node **map = calloc(initial_size, sizeof(Node *));

  if (map == NULL) {
    return NULL;
  };

  new_map->map = map;
  new_map->num_elements = 0;
  new_map->size = initial_size;
  new_map->max_load_factor = max_load_factor;

  return new_map;
};

void hashmap_destroy(HashMap *map) {
  if (map == NULL) {
    return;
  };

  if (map->map == NULL) {
    free(map);
    return;
  };

  Node *head;
  Node *next;
  for (int i = 0; i < map->size; i++) {
    head = map->map[i];
    while (head != NULL) {
      next = head->next;
      free(head);
      head = next;
    };
  };

  free(map->map);
  free(map);

  return;
};

bool hashmap_add(HashMap *map, int key, int value) {
  if (map == NULL) {
    return false;
  };

  int p = __builtin_ctz(map->size);
  int index = knuth_hash(key) >> (32 - p);
  Node *head = map->map[index];
  Node *new_node;
  if (head == NULL) {
    new_node = malloc(sizeof(Node));
    new_node->data[0] = key;
    new_node->data[1] = value;
    new_node->next = NULL;
    map->map[index] = new_node;
    map->num_elements++;
    return true;
  };

  while (head->next != NULL) {
    if (head->data[0] == key) {
      head->data[1] = value;
      return true;
    };
    head = head->next;
  };

  if (head->data[0] == key) {
    head->data[1] = value;

  } else {
    new_node = malloc(sizeof(Node));
    new_node->data[0] = key;
    new_node->data[1] = value;
    new_node->next = NULL;
    head->next = new_node;
    map->num_elements++;
  };

  return true;
};

bool hashmap_remove(HashMap *map, int key) {
  if (map == NULL) {
    return false;
  };

  int p = __builtin_ctz(map->size);
  int index = knuth_hash(key) >> (32 - p);
  Node *head = map->map[index];
  Node *next;
  if (head == NULL) {
    return false;
  };

  next = head->next;

  if (head->data[0] == key) {
    free(head);
    map->map[index] = next;
    map->num_elements--;
    return true;
  };

  while (next != NULL) {
    if (next->data[0] == key) {
      head->next = next->next;
      free(next);
      map->num_elements--;
      return true;
    };
    head = next;
    next = next->next;
  };

  return false;
};

void hashmap_resize(HashMap *map) {
  if (map == NULL) {
    return;
  };
  int new_size = 2 * map->size;
  if (__builtin_ctz(new_size) > 30) {
    return;
  };

  Node **new_map = calloc(new_size, sizeof(Node *));

  if (new_map == NULL) {
    return;
  };

  Node *head;
  Node *next;
  Node *new_head;
  int new_index;
  int p = __builtin_ctz(new_size);
  for (int i = 0; i < map->size; i++) {
    head = map->map[i];
    while (head != NULL) {
      next = head->next;
      Node *new_node = malloc(sizeof(Node));
      new_node->data[0] = head->data[0];
      new_node->data[1] = head->data[1];
      new_node->next = NULL;
      new_index = knuth_hash(new_node->data[0]) >> (32 - p);
      new_head = new_map[new_index];
      if (new_head == NULL) {
        new_map[new_index] = new_node;

      } else {
        while (new_head->next != NULL) {
          new_head = new_head->next;
        };
        new_head->next = new_node;
      };
      free(head);
      head = next;
    };
  };
  map->size = new_size;
  map->map = new_map;
}

bool hashmap_get(HashMap *map, int key, int *retrieved_value) {
  if (map == NULL) {
    return false;
  };

  int p = __builtin_ctz(map->size);
  int index = knuth_hash(key) >> (32 - p);
  Node *head = map->map[index];
  while (head != NULL) {
    if (head->data[0] == key) {
      *retrieved_value = head->data[1];
      return true;
    };
    head = head->next;
  };

  return false;
};

uint32_t knuth_hash(int key) { return (uint32_t)key * 2654435761u; };
