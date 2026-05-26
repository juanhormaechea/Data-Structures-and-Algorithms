#include "hashset.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

HashSet *hashset_create(int initial_size, double max_load_factor) {
  if (initial_size <= 0 || (initial_size & (initial_size - 1)) != 0) {
    return NULL;
  };

  HashSet *new_set = malloc(sizeof(HashSet));

  if (new_set == NULL) {
    return NULL;
  };

  new_set->set = (Node **)calloc(initial_size, sizeof(Node *));

  if (new_set->set == NULL) {
    free(new_set);
    return NULL;
  };
  new_set->size = initial_size;

  new_set->num_elements = 0;

  new_set->max_load_factor = max_load_factor;

  return new_set;
};

void hashset_destroy(HashSet *set) {
  if (set == NULL) {
    return;
  };

  if (set->set == NULL) {
    free(set);
    return;
  };

  Node *head;
  Node *next;
  for (int i = 0; i < set->size; i++) {
    head = set->set[i];
    while (head != NULL) {
      next = head->next;
      free(head);
      head = next;
    };
  };

  free(set->set);
  free(set);
  return;
};

bool hashset_add(HashSet *set, int value) {
  if (set == NULL) {
    return false;
  };

  if (hashset_contains(set, value)) {
    return false;
  };

  int p = __builtin_ctz(set->size);
  int index = knuth_hash(value) >> (32 - p);

  Node *new_node = malloc(sizeof(Node));
  new_node->data = value;
  new_node->next = NULL;

  Node *current_node = set->set[index];
  if (current_node == NULL) {
    set->set[index] = new_node;
    set->num_elements++;
    if (((double)set->num_elements / set->size) > 0.75) {
      hashset_resize(set);
    };
    return true;
  };

  while (current_node->next != NULL) {
    current_node = current_node->next;
  };
  current_node->next = new_node;
  set->num_elements++;
  if (((double)set->num_elements / set->size) > 0.75) {
    hashset_resize(set);
  };
  return true;
};

bool hashset_remove(HashSet *set, int value) {
  if (set == NULL) {
    return false;
  };

  int p = __builtin_ctz(set->size);
  int index = knuth_hash(value) >> (32 - p);
  Node *head = set->set[index];
  Node *next;
  if (head == NULL) {
    return false;
  };

  next = head->next;

  if (head->data == value) {
    free(head);
    set->set[index] = next;
    set->num_elements--;
    return true;
  };

  while (next != NULL) {

    if (next->data == value) {
      head->next = next->next;
      free(next);
      set->num_elements--;
      return true;
    };

    head = next;
    next = next->next;
  };

  return false;
};

bool hashset_contains(HashSet *set, int value) {
  if (set == NULL) {
    return false;
  };

  int p = __builtin_ctz(set->size);
  int index = knuth_hash(value) >> (32 - p);
  Node *head = set->set[index];

  while (head != NULL) {
    if (head->data == value) {
      return true;
    };

    head = head->next;
  };

  return false;
};

void hashset_resize(HashSet *set) {
  if (set == NULL) {
    return;
  };
  int new_size = 2 * set->size;
  if (__builtin_ctz(new_size) > 30) {
    return;
  };
  Node **new_set = calloc(new_size, sizeof(Node *));

  if (new_set == NULL) {
    fprintf(stderr, "failed to allocate new set");
    return;
  };

  Node *head;
  Node *next;
  Node *new_head;
  int new_index;
  int p = __builtin_ctz(new_size);
  for (int i = 0; i < set->size; i++) {
    head = set->set[i];
    while (head != NULL) {
      next = head->next;
      Node *new_node = malloc(sizeof(Node));
      new_node->data = head->data;
      new_node->next = NULL;
      new_index = knuth_hash(head->data) >> (32 - p);
      new_head = new_set[new_index];
      if (new_head == NULL) {
        new_set[new_index] = new_node;

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

  set->size = new_size;
  free(set->set);
  set->set = new_set;
  return;
};

uint32_t knuth_hash(int value) { return (uint32_t)value * 2654435761u; };