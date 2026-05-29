#include "bst.h"
#include <limits.h>
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
  new_BST->root = NULL;
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

  if (root->data == data) {
    return root;
  };

  if (root->data < data) {
    root->right_child = insert(root->right_child, data);
  } else {
    root->left_child = insert(root->left_child, data);
  };

  return root;
};

static Node *findParent(Node *root, int data) {
  if (root == NULL) {
    return NULL;
  };

  if (root->data == data) {
    return NULL;
  };

  if ((root->left_child != NULL && root->left_child->data == data) ||
      (root->right_child != NULL && root->right_child->data == data)) {
    return root;
  };

  if (root->data < data) {
    return findParent(root->right_child, data);
  };

  return findParent(root->left_child, data);
};

Node *del(Node *root, int data) {
  if (root == NULL) {
    return NULL;
  };

  if (root->data == data) {
    if (root->left_child == NULL && root->right_child == NULL) {
      free(root);
      return NULL;
    };

    if (root->left_child == NULL) {
      Node *right_child = root->right_child;
      free(root);
      return right_child;
    };

    if (root->right_child == NULL) {
      Node *left_child = root->left_child;
      free(root);
      return left_child;
    };

    Node *successor = findMin(root->right_child);
    int successor_data = successor->data;
    root = del(root, successor_data);
    root->data = successor_data;
    return root;
  };

  Node *parent_of_node_to_delete = findParent(root, data);
  Node *node_to_delete = NULL;
  Node *left = NULL;
  Node *right = NULL;
  if (parent_of_node_to_delete == NULL) {
    return NULL;
  };
  left = parent_of_node_to_delete->left_child;
  right = parent_of_node_to_delete->right_child;
  node_to_delete = search(parent_of_node_to_delete, data);
  if (left == node_to_delete) {
    right = NULL;
  } else {
    left = NULL;
  };

  if (node_to_delete->left_child == NULL &&
      node_to_delete->right_child == NULL) {
    if (left == NULL) {
      parent_of_node_to_delete->right_child = NULL;

    } else {
      parent_of_node_to_delete->left_child = NULL;
    };

    free(node_to_delete);
    return root;
  };

  if (node_to_delete->left_child == NULL) {
    if (left == NULL) {
      parent_of_node_to_delete->right_child = node_to_delete->right_child;
    } else {
      parent_of_node_to_delete->left_child = node_to_delete->right_child;
    };
    free(node_to_delete);
    return root;
  };

  if (node_to_delete->right_child == NULL) {
    if (left == NULL) {
      parent_of_node_to_delete->right_child = node_to_delete->left_child;
    } else {
      parent_of_node_to_delete->left_child = node_to_delete->left_child;
    };
    free(node_to_delete);
    return root;
  };

  Node *successor = findMin(node_to_delete->right_child);
  int successor_data = successor->data;
  root = del(root, successor_data);
  node_to_delete->data = successor_data;
  return root;
};

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

  if (root->left_child == NULL && root->right_child == NULL) {
    return 0;
  };

  if (root->left_child == NULL) {
    return 1 + height(root->right_child);
  };

  if (root->right_child == NULL) {
    return 1 + height(root->left_child);
  };

  int height_left = height(root->left_child);
  int height_right = height(root->right_child);

  return 1 + (height_left >= height_right ? height_left : height_right);
};

int size(Node *root) {
  if (root == NULL) {
    return 0;
  };

  return 1 + size(root->left_child) + size(root->right_child);
};

bool isEmpty(Node *root) { return (root == NULL); };

static bool isBST(Node *root, int min, int max) {
  if (root == NULL) {
    return true;
  };

  if (root->data < min || root->data > max) {
    return false;
  };

  return (isBST(root->left_child, min, root->data) &&
          isBST(root->right_child, root->data, max));
};

bool validateBST(Node *root) { return isBST(root, INT_MIN, INT_MAX); };

Node *findSuccessor(Node *root, int data) {
  if (root == NULL) {
    return NULL;
  };
  if (root->data > data) {
    Node *left_successor = findSuccessor(root->left_child, data);
    return (left_successor != NULL ? left_successor : root);
  } else {
    return findSuccessor(root->right_child, data);
  };
};

Node *findPredecessor(Node *root, int data) {
  if (root == NULL) {
    return NULL;
  };

  if (root->data < data) {
    Node *right_predecessor = findPredecessor(root->right_child, data);
    return (right_predecessor != NULL ? right_predecessor : root);
  } else {
    return findPredecessor(root->left_child, data);
  };
};

int countLeaves(Node *root) {
  if (root == NULL) {
    return 0;
  };

  Node *left = root->left_child;
  Node *right = root->right_child;

  if (left == NULL && right == NULL) {
    return 1;
  };

  return countLeaves(left) + countLeaves(right);
};

bool isBalanced(Node *root) {
  if (root == NULL) {
    return true;
  };

  bool balanced_left = isBalanced(root->left_child);
  bool balanced_right = isBalanced(root->right_child);
  bool balanced_root;
  int height_left = height(root->left_child);
  int height_right = height(root->right_child);

  balanced_root = (abs(height_left - height_right) <= 1);

  return (balanced_left && balanced_right && balanced_root);
};
