#include "avl.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int getHeight(AVLNode *node) {
  return (node == NULL) ? -1 : node->height;
};

static void updateHeight(AVLNode *node) {

  int height_left = getHeight(node->left_child);
  int height_right = getHeight(node->right_child);

  node->height =
      1 + ((height_left >= height_right) ? height_left : height_right);
};

static int getBalanceFactor(AVLNode *node) {
  return getHeight(node->left_child) - getHeight(node->right_child);
};

static AVLNode *rotateRight(AVLNode *y) {
  AVLNode *x_left = y->left_child;
  y->left_child = x_left->right_child;
  x_left->right_child = y;

  updateHeight(y);
  updateHeight(x_left);
  return x_left;
};

static AVLNode *rotateLeft(AVLNode *x) {
  AVLNode *y_right = x->right_child;
  x->right_child = y_right->left_child;
  y_right->left_child = x;

  updateHeight(x);
  updateHeight(y_right);
  return y_right;
};

static AVLNode *rebalance(AVLNode *unbalanced_node) {
  int current_balance_factor = getBalanceFactor(unbalanced_node);
  AVLNode *balanced_node;
  if (current_balance_factor == 2) {
    int balance_factor_left = getBalanceFactor(unbalanced_node->left_child);
    if (balance_factor_left >= 0) {
      balanced_node = rotateRight(unbalanced_node);
    } else {
      unbalanced_node->left_child = rotateLeft(unbalanced_node->left_child);
      balanced_node = rotateRight(unbalanced_node);
    };
  } else if (current_balance_factor == -2) {
    int balance_factor_right = getBalanceFactor(unbalanced_node->right_child);
    if (balance_factor_right <= 0) {
      balanced_node = rotateLeft(unbalanced_node);
    } else {
      unbalanced_node->right_child = rotateRight(unbalanced_node->right_child);
      balanced_node = rotateLeft(unbalanced_node);
    };
  } else {
    balanced_node = unbalanced_node;
  };

  return balanced_node;
};

AVLNode *createNode(int data) {
  AVLNode *new_node = malloc(sizeof(AVLNode));
  if (new_node == NULL) {
    return NULL;
  };

  new_node->data = data;
  new_node->left_child = NULL;
  new_node->right_child = NULL;
  new_node->height = 0;

  return new_node;
};

AVLT *createAVLT() {
  AVLT *new_tree = malloc(sizeof(AVLT));

  if (new_tree == NULL) {
    return NULL;
  };

  new_tree->root = NULL;

  return new_tree;
};

static void freeNodes(AVLNode *root) {
  if (root == NULL) {
    return;
  };

  freeNodes(root->left_child);
  freeNodes(root->right_child);
  free(root);
  return;
};

void destroyAVLT(AVLT *tree) {
  if (tree == NULL) {
    return;
  };

  freeNodes(tree->root);
  free(tree);
  return;
};

AVLNode *insert(AVLNode *root, int data) {
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

  updateHeight(root);
  return rebalance(root);
};

AVLNode *del(AVLNode *root, int data) {
  if (root == NULL) {
    return NULL;
  };

  if (root->data == data) {
    if (root->left_child == NULL && root->right_child == NULL) {
      free(root);
      return NULL;
    };

    if (root->left_child == NULL) {
      AVLNode *right_child = root->right_child;
      free(root);
      return right_child;
    };

    if (root->right_child == NULL) {
      AVLNode *left_child = root->left_child;
      free(root);
      return left_child;
    };

    AVLNode *successor = findMin(root->right_child);
    int successor_data = successor->data;
    root->data = successor_data;
    root->right_child = del(root->right_child, successor_data);
    updateHeight(root);
    return rebalance(root);
  };

  if (root->data < data) {
    root->right_child = del(root->right_child, data);
    updateHeight(root);
    return rebalance(root);
  };

  root->left_child = del(root->left_child, data);
  updateHeight(root);
  return rebalance(root);
};

AVLNode *search(AVLNode *root, int data) {
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

AVLNode *findMin(AVLNode *root) {
  if (root == NULL) {
    return NULL;
  };

  if (root->left_child == NULL) {
    return root;
  };

  return findMin(root->left_child);
};

AVLNode *findMax(AVLNode *root) {
  if (root == NULL) {
    return NULL;
  };

  if (root->right_child == NULL) {
    return root;
  };

  return findMax(root->right_child);
};

void inOrder(AVLNode *root) {
  if (root == NULL) {
    return;
  };

  inOrder(root->left_child);
  printf("%d ", root->data);
  inOrder(root->right_child);
};

void preOrder(AVLNode *root) {
  if (root == NULL) {
    return;
  };

  printf("%d ", root->data);
  preOrder(root->left_child);
  preOrder(root->right_child);
};

void postOrder(AVLNode *root) {
  if (root == NULL) {
    return;
  };

  postOrder(root->left_child);
  postOrder(root->right_child);
  printf("%d ", root->data);
};

int height(AVLNode *root) {
  if (root == NULL) {
    return 0;
  };

  return root->height;
};

int size(AVLNode *root) {
  if (root == NULL) {
    return 0;
  };

  return 1 + size(root->left_child) + size(root->right_child);
};

bool isEmpty(AVLNode *root) { return (size(root) == 0); };

static bool isAVL(AVLNode *root, int min, int max) {
  if (root == NULL) {
    return true;
  };

  int height_left = getHeight(root->left_child);
  int height_right = getHeight(root->right_child);
  int expected_height =
      1 + (height_left >= height_right ? height_left : height_right);

  if (root->data < min || root->data > max ||
      abs(height_left - height_right) > 1 || root->height != expected_height) {
    return false;
  };

  return (isAVL(root->left_child, min, root->data) &&
          isAVL(root->right_child, root->data, max));
};

bool validateAVLT(AVLNode *root) { return isAVL(root, INT_MIN, INT_MAX); };

AVLNode *findSuccessor(AVLNode *root, int data) {
  if (root == NULL) {
    return NULL;
  };

  if (root->data > data) {
    AVLNode *left_successor = findSuccessor(root->left_child, data);
    return (left_successor == NULL ? root : left_successor);
  };

  return findSuccessor(root->right_child, data);
};

AVLNode *findPredecessor(AVLNode *root, int data) {
  if (root == NULL) {
    return NULL;
  };

  if (root->data < data) {
    AVLNode *right_predecessor = findPredecessor(root->right_child, data);
    return (right_predecessor == NULL ? root : right_predecessor);
  };

  return findPredecessor(root->left_child, data);
};

int countLeaves(AVLNode *root) {
  if (root == NULL) {
    return 0;
  };

  if (root->left_child == NULL && root->right_child == NULL) {
    return 1;
  };

  return countLeaves(root->left_child) + countLeaves(root->right_child);
};
