#include <stdbool.h>
#ifndef AVL_H
#define AVL_H
typedef struct AVLNode AVLNode;
typedef struct AVLT AVLT;

struct AVLNode {
  int data;
  AVLNode *left_child;
  AVLNode *right_child;
  int height;
};

struct AVLT {
  AVLNode *root;
};

AVLNode *createNode(int data);

AVLT *createAVLT();

void destroyBST(AVLT *tree);

AVLNode *insert(AVLNode *root, int data);

AVLNode *del(AVLNode *root, int data);

AVLNode *search(AVLNode *root, int data);

AVLNode *findMin(AVLNode *root);

AVLNode *findMax(AVLNode *root);

void inOrder(AVLNode *root);

void preOrder(AVLNode *root);

void postOrder(AVLNode *root);

int height(AVLNode *root);

int size(AVLNode *root);

bool isEmpty(AVLNode *root);

bool validateBST(AVLNode *root);

AVLNode *findSuccessor(AVLNode *root, int data);

AVLNode *findPredecessor(AVLNode *root, int data);

int countLeaves(AVLNode *root);

bool isBalanced(AVLNode *root);

#endif