#include <stdbool.h>
#ifndef BST_H
#define BST_H
typedef struct Node Node;
typedef struct BST BST;

struct Node {
  int data;
  Node *left_child;
  Node *right_child;
};

struct BST {
  Node *root;
};

Node *createNode(int data);

BST *createBST();

void destroyBST(BST *tree);

Node *insert(Node *root, int data);

Node *del(Node *root, int data);

Node *search(Node *root, int data);

Node *findMin(Node *root);

Node *findMax(Node *root);

void inOrder(Node *root);

void preOrder(Node *root);

void postOrder(Node *root);

int height(Node *root);

int size(Node *root);

bool isEmpty(Node *root);

bool validateBST(Node *root);

Node *findSuccessor(Node *root, int data);

Node *findPredecessor(Node *root, int data);

int countLeaves(Node *root);

bool isBalanced(Node *root);

#endif