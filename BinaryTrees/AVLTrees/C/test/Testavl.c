#include "../../../../Unity/src/unity.h"
#include "../src/avl.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

AVLT *tree;

void setUp(void) {
  tree = createAVLT();
}

void tearDown(void) {
  destroyAVLT(tree);
}

// ── CREATE / DESTROY ─────────────────────────────────────────────────────────

void test_createAVLT(void) {
  TEST_ASSERT_NOT_NULL(tree);
  TEST_ASSERT_NULL(tree->root);
  TEST_ASSERT_TRUE(isEmpty(tree->root));
}

// ── INSERT & ROTATIONS (AVL PROPERTY) ────────────────────────────────────────

void test_insert_left_left_rotation(void) {
  tree->root = insert(tree->root, 30);
  tree->root = insert(tree->root, 20);
  tree->root = insert(tree->root, 10);
  
  // After LL rotation, 20 should be root, 10 left, 30 right.
  TEST_ASSERT_EQUAL_INT(20, tree->root->data);
  TEST_ASSERT_EQUAL_INT(10, tree->root->left_child->data);
  TEST_ASSERT_EQUAL_INT(30, tree->root->right_child->data);
  TEST_ASSERT_TRUE(validateAVLT(tree->root));
}

void test_insert_right_right_rotation(void) {
  tree->root = insert(tree->root, 10);
  tree->root = insert(tree->root, 20);
  tree->root = insert(tree->root, 30);
  
  // After RR rotation, 20 should be root, 10 left, 30 right.
  TEST_ASSERT_EQUAL_INT(20, tree->root->data);
  TEST_ASSERT_EQUAL_INT(10, tree->root->left_child->data);
  TEST_ASSERT_EQUAL_INT(30, tree->root->right_child->data);
  TEST_ASSERT_TRUE(validateAVLT(tree->root));
}

void test_insert_left_right_rotation(void) {
  tree->root = insert(tree->root, 30);
  tree->root = insert(tree->root, 10);
  tree->root = insert(tree->root, 20);
  
  TEST_ASSERT_EQUAL_INT(20, tree->root->data);
  TEST_ASSERT_EQUAL_INT(10, tree->root->left_child->data);
  TEST_ASSERT_EQUAL_INT(30, tree->root->right_child->data);
  TEST_ASSERT_TRUE(validateAVLT(tree->root));
}

void test_insert_right_left_rotation(void) {
  tree->root = insert(tree->root, 10);
  tree->root = insert(tree->root, 30);
  tree->root = insert(tree->root, 20);
  
  TEST_ASSERT_EQUAL_INT(20, tree->root->data);
  TEST_ASSERT_EQUAL_INT(10, tree->root->left_child->data);
  TEST_ASSERT_EQUAL_INT(30, tree->root->right_child->data);
  TEST_ASSERT_TRUE(validateAVLT(tree->root));
}

void test_insert_duplicate(void) {
  tree->root = insert(tree->root, 10);
  tree->root = insert(tree->root, 10);
  TEST_ASSERT_EQUAL_INT(1, size(tree->root));
}

// ── SEARCH ───────────────────────────────────────────────────────────────────

void test_search_existing(void) {
  tree->root = insert(tree->root, 10);
  tree->root = insert(tree->root, 5);
  tree->root = insert(tree->root, 15);
  
  AVLNode *found = search(tree->root, 5);
  TEST_ASSERT_NOT_NULL(found);
  TEST_ASSERT_EQUAL_INT(5, found->data);
}

void test_search_missing(void) {
  tree->root = insert(tree->root, 10);
  AVLNode *found = search(tree->root, 99);
  TEST_ASSERT_NULL(found);
}

// ── MIN / MAX ────────────────────────────────────────────────────────────────

void test_findMin(void) {
  tree->root = insert(tree->root, 20);
  tree->root = insert(tree->root, 10);
  tree->root = insert(tree->root, 30);
  
  AVLNode *min_node = findMin(tree->root);
  TEST_ASSERT_NOT_NULL(min_node);
  TEST_ASSERT_EQUAL_INT(10, min_node->data);
}

void test_findMax(void) {
  tree->root = insert(tree->root, 20);
  tree->root = insert(tree->root, 10);
  tree->root = insert(tree->root, 30);
  
  AVLNode *max_node = findMax(tree->root);
  TEST_ASSERT_NOT_NULL(max_node);
  TEST_ASSERT_EQUAL_INT(30, max_node->data);
}

// ── PROPERTIES (SIZE, HEIGHT, LEAVES) ────────────────────────────────────────

void test_size(void) {
  TEST_ASSERT_EQUAL_INT(0, size(tree->root));
  tree->root = insert(tree->root, 10);
  tree->root = insert(tree->root, 20);
  TEST_ASSERT_EQUAL_INT(2, size(tree->root));
}

void test_height(void) {
  TEST_ASSERT_EQUAL_INT(0, height(tree->root));
  tree->root = insert(tree->root, 10);
  TEST_ASSERT_EQUAL_INT(0, height(tree->root)); // Leaf is 0
  tree->root = insert(tree->root, 20);
  TEST_ASSERT_EQUAL_INT(1, height(tree->root));
  tree->root = insert(tree->root, 30); // Triggers RR rotation
  TEST_ASSERT_EQUAL_INT(1, height(tree->root)); // 20 is root, 10 and 30 are leaves. Height is 1.
}

void test_countLeaves(void) {
  TEST_ASSERT_EQUAL_INT(0, countLeaves(tree->root));
  tree->root = insert(tree->root, 20);
  TEST_ASSERT_EQUAL_INT(1, countLeaves(tree->root));
  tree->root = insert(tree->root, 10);
  tree->root = insert(tree->root, 30);
  TEST_ASSERT_EQUAL_INT(2, countLeaves(tree->root));
}

// ── SUCCESSOR / PREDECESSOR ──────────────────────────────────────────────────

void test_findSuccessor(void) {
  tree->root = insert(tree->root, 20);
  tree->root = insert(tree->root, 10);
  tree->root = insert(tree->root, 30);
  
  AVLNode *succ = findSuccessor(tree->root, 10);
  TEST_ASSERT_NOT_NULL(succ);
  TEST_ASSERT_EQUAL_INT(20, succ->data);
  
  TEST_ASSERT_NULL(findSuccessor(tree->root, 30));
}

void test_findPredecessor(void) {
  tree->root = insert(tree->root, 20);
  tree->root = insert(tree->root, 10);
  tree->root = insert(tree->root, 30);
  
  AVLNode *pred = findPredecessor(tree->root, 30);
  TEST_ASSERT_NOT_NULL(pred);
  TEST_ASSERT_EQUAL_INT(20, pred->data);
  
  TEST_ASSERT_NULL(findPredecessor(tree->root, 10));
}

// ── DELETE ───────────────────────────────────────────────────────────────────

void test_delete_leaf(void) {
  tree->root = insert(tree->root, 20);
  tree->root = insert(tree->root, 10);
  tree->root = insert(tree->root, 30);
  
  tree->root = del(tree->root, 10);
  TEST_ASSERT_NULL(search(tree->root, 10));
  TEST_ASSERT_EQUAL_INT(2, size(tree->root));
  TEST_ASSERT_TRUE(validateAVLT(tree->root));
}

void test_delete_node_with_one_child(void) {
  tree->root = insert(tree->root, 20);
  tree->root = insert(tree->root, 10);
  tree->root = insert(tree->root, 30);
  tree->root = insert(tree->root, 5); // 10 now has left child 5
  
  tree->root = del(tree->root, 10);
  TEST_ASSERT_NULL(search(tree->root, 10));
  TEST_ASSERT_NOT_NULL(search(tree->root, 5));
  TEST_ASSERT_TRUE(validateAVLT(tree->root));
}

void test_delete_node_with_two_children(void) {
  tree->root = insert(tree->root, 20);
  tree->root = insert(tree->root, 10);
  tree->root = insert(tree->root, 30);
  tree->root = insert(tree->root, 25);
  tree->root = insert(tree->root, 35);
  
  // Delete 30 (has 25 and 35)
  tree->root = del(tree->root, 30);
  TEST_ASSERT_NULL(search(tree->root, 30));
  TEST_ASSERT_NOT_NULL(search(tree->root, 35)); // Successor
  TEST_ASSERT_NOT_NULL(search(tree->root, 25));
  TEST_ASSERT_TRUE(validateAVLT(tree->root));
}

void test_delete_causes_rebalance(void) {
  // Creating a right heavy tree that will rebalance when deleting from left
  tree->root = insert(tree->root, 20);
  tree->root = insert(tree->root, 10);
  tree->root = insert(tree->root, 30);
  tree->root = insert(tree->root, 40);
  
  // Currently:
  //    20
  //   /  \
  // 10    30
  //         \
  //         40
  // Delete 10 -> Right subtree of 20 is too heavy (height 1 vs -1 -> diff 2)
  // Should trigger Left rotation around 20.
  
  tree->root = del(tree->root, 10);
  
  TEST_ASSERT_EQUAL_INT(30, tree->root->data);
  TEST_ASSERT_EQUAL_INT(20, tree->root->left_child->data);
  TEST_ASSERT_EQUAL_INT(40, tree->root->right_child->data);
  TEST_ASSERT_TRUE(validateAVLT(tree->root));
}

// ── TRAVERSALS ───────────────────────────────────────────────────────────────
// (Traversals print to stdout, so we just run them to ensure no crashes. 
//  Redirecting stdout in C is possible but overkill for a simple test suite)

void test_traversals(void) {
  tree->root = insert(tree->root, 20);
  tree->root = insert(tree->root, 10);
  tree->root = insert(tree->root, 30);
  
  printf("\ninOrder: ");
  inOrder(tree->root);
  printf("\npreOrder: ");
  preOrder(tree->root);
  printf("\npostOrder: ");
  postOrder(tree->root);
  printf("\n");
}

int main(void) {
  UNITY_BEGIN();
  
  RUN_TEST(test_createAVLT);
  
  RUN_TEST(test_insert_left_left_rotation);
  RUN_TEST(test_insert_right_right_rotation);
  RUN_TEST(test_insert_left_right_rotation);
  RUN_TEST(test_insert_right_left_rotation);
  RUN_TEST(test_insert_duplicate);
  
  RUN_TEST(test_search_existing);
  RUN_TEST(test_search_missing);
  
  RUN_TEST(test_findMin);
  RUN_TEST(test_findMax);
  
  RUN_TEST(test_size);
  RUN_TEST(test_height);
  RUN_TEST(test_countLeaves);
  
  RUN_TEST(test_findSuccessor);
  RUN_TEST(test_findPredecessor);
  
  RUN_TEST(test_delete_leaf);
  RUN_TEST(test_delete_node_with_one_child);
  RUN_TEST(test_delete_node_with_two_children);
  RUN_TEST(test_delete_causes_rebalance);
  
  RUN_TEST(test_traversals);
  
  return UNITY_END();
}