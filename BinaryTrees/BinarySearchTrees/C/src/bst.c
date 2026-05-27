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

Node *del(Node *root, int data) { return NULL; };

Node *search(Node *root, int data) {
  if (root == NULL) {
    return NULL;
  };

  if (root->data == data) {
    return root;
  };

  if (root->data < data) {
    return search(root->right_child, data);
  };

  return search(root->left_child, data);
};

Node *findMin(Node *root) {
  if (root == NULL) {
    return NULL;
  };

  if (root->left_child == NULL) {
    return root;
  };

  return findMin(root->left_child);
};

Node *findMax(Node *root) {
  if (root == NULL) {
    return NULL;
  };

  if (root->right_child == NULL) {
    return root;
  };

  return findMax(root->right_child);
};

void inOrder(Node *root) {
  if (root == NULL) {
    return;
  };

  inOrder(root->left_child);
  printf("%d ", root->data);
  inOrder(root->right_child);
  return;
};

void preOrder(Node *root) {
  if (root == NULL) {
    return;
  };

  printf("%d ", root->data);
  preOrder(root->left_child);
  preOrder(root->right_child);
};

void postOrder(Node *root) {
  if (root == NULL) {
    return;
  };

  postOrder(root->left_child);
  postOrder(root->right_child);
  printf("%d ", root->data);
};

int height(Node *root) {
  if (root == NULL) {
    return 0;
  };

  int height_left = height(root->left_child);
  int height_right = height(root->right_child);

  return ((height_left >= height_right) ? height_left : height_right);
}
