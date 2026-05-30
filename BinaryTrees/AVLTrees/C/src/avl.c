#include "avl.h"
#include <limits.h>
#include <stdbool.h>
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