#include "bst.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Node *createNode(int data) {
  Node *new_node = malloc(sizeof(Node));
  new_node->data = data;
  new_node->left_child = NULL;
  new_node->right_child = NULL;
  return new_node;
};

BST *createBST() {
  BST *new_BST = malloc(sizeof(BST));
  return new_BST;
};

static void freeNodes(Node *root) {
  if (root == NULL) {
    return;
  };

  freeNodes(root->left_child);
  freeNodes(root->right_child);
  free(root);
};

void destroyBST(BST *tree) {
  if (tree == NULL) {
    return;
  };

  freeNodes(tree->root);
  free(tree);
};

Node *insert(Node *root, int data) {
  if (root == NULL) {
    return createNode(data);
  };

  Node *left_child = root->left_child;
  Node *right_child = root->right_child;

  if (root->data <= data) {
    if (right_child == NULL) {
      root->right_child = createNode(data);
    } else {
      insert(right_child, data);
    };
  } else {
    if (left_child == NULL) {
      root->left_child = createNode(data);
    } else {
      insert(left_child, data);
    };
  };

  return root;
};