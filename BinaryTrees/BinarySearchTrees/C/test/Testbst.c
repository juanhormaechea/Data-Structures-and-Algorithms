#include "../src/bst.h"
#include "../../../../Unity/src/unity.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

/* ─── helpers ────────────────────────────────────────────────────────────── */

/* Local post-order free (freeNodes is static in bst.c). */
static void freeTree(Node *root) {
  if (root == NULL) return;
  freeTree(root->left_child);
  freeTree(root->right_child);
  free(root);
}

/*
 * Builds the standard 7-node balanced test tree:
 *
 *          10
 *         /  \
 *        5    15
 *       / \   / \
 *      3   7 12  20
 *
 * height = 2 | size = 7 | leaves = 4 (3, 7, 12, 20)
 */
static Node *buildTree(void) {
  Node *root = NULL;
  root = insert(root, 10);
  root = insert(root, 5);
  root = insert(root, 15);
  root = insert(root, 3);
  root = insert(root, 7);
  root = insert(root, 12);
  root = insert(root, 20);
  return root;
}

/* ─── createNode ──────────────────────────────────────────────────────────── */

void test_createNode_returns_non_null(void) {
  Node *n = createNode(42);
  TEST_ASSERT_NOT_NULL(n);
  free(n);
}

void test_createNode_stores_data(void) {
  Node *n = createNode(99);
  TEST_ASSERT_EQUAL_INT(99, n->data);
  free(n);
}

void test_createNode_children_are_null(void) {
  Node *n = createNode(1);
  TEST_ASSERT_NULL(n->left_child);
  TEST_ASSERT_NULL(n->right_child);
  free(n);
}

/* ─── createBST / destroyBST ──────────────────────────────────────────────── */

void test_createBST_returns_non_null(void) {
  BST *tree = createBST();
  TEST_ASSERT_NOT_NULL(tree);
  destroyBST(tree);
}

void test_createBST_root_is_null(void) {
  BST *tree = createBST();
  TEST_ASSERT_NULL(tree->root);
  destroyBST(tree);
}

void test_destroyBST_null_does_not_crash(void) {
  destroyBST(NULL);
}

void test_destroyBST_empty_tree_does_not_crash(void) {
  BST *tree = createBST();
  destroyBST(tree);
}

void test_destroyBST_non_empty_tree_does_not_crash(void) {
  BST *tree = createBST();
  tree->root = insert(tree->root, 10);
  tree->root = insert(tree->root, 5);
  tree->root = insert(tree->root, 15);
  destroyBST(tree);
}

/* ─── insert ──────────────────────────────────────────────────────────────── */

void test_insert_into_null_creates_root(void) {
  Node *root = insert(NULL, 10);
  TEST_ASSERT_NOT_NULL(root);
  TEST_ASSERT_EQUAL_INT(10, root->data);
  freeTree(root);
}

void test_insert_smaller_value_goes_left(void) {
  Node *root = insert(NULL, 10);
  root = insert(root, 5);
  TEST_ASSERT_NOT_NULL(root->left_child);
  TEST_ASSERT_EQUAL_INT(5, root->left_child->data);
  freeTree(root);
}

void test_insert_larger_value_goes_right(void) {
  Node *root = insert(NULL, 10);
  root = insert(root, 15);
  TEST_ASSERT_NOT_NULL(root->right_child);
  TEST_ASSERT_EQUAL_INT(15, root->right_child->data);
  freeTree(root);
}

void test_insert_duplicate_is_ignored(void) {
  Node *root = insert(NULL, 10);
  Node *root2 = insert(root, 10);
  TEST_ASSERT_EQUAL_PTR(root, root2);
  TEST_ASSERT_NULL(root->left_child);
  TEST_ASSERT_NULL(root->right_child);
  freeTree(root);
}

void test_insert_maintains_bst_property(void) {
  Node *root = buildTree();
  TEST_ASSERT_TRUE(validateBST(root));
  freeTree(root);
}

void test_insert_increases_size(void) {
  Node *root = NULL;
  root = insert(root, 10);
  root = insert(root, 5);
  root = insert(root, 15);
  TEST_ASSERT_EQUAL_INT(3, size(root));
  freeTree(root);
}

/* ─── search ──────────────────────────────────────────────────────────────── */

void test_search_null_tree_returns_null(void) {
  TEST_ASSERT_NULL(search(NULL, 10));
}

void test_search_existing_value_returns_node(void) {
  Node *root = buildTree();
  Node *result = search(root, 7);
  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_INT(7, result->data);
  freeTree(root);
}

void test_search_nonexistent_value_returns_null(void) {
  Node *root = buildTree();
  TEST_ASSERT_NULL(search(root, 99));
  freeTree(root);
}

void test_search_root_value_returns_root(void) {
  Node *root = buildTree();
  Node *result = search(root, 10);
  TEST_ASSERT_EQUAL_PTR(root, result);
  freeTree(root);
}

void test_search_left_subtree(void) {
  Node *root = buildTree();
  TEST_ASSERT_EQUAL_INT(3, search(root, 3)->data);
  freeTree(root);
}

void test_search_right_subtree(void) {
  Node *root = buildTree();
  TEST_ASSERT_EQUAL_INT(20, search(root, 20)->data);
  freeTree(root);
}

/* ─── findMin ─────────────────────────────────────────────────────────────── */

void test_findMin_null_returns_null(void) {
  TEST_ASSERT_NULL(findMin(NULL));
}

void test_findMin_single_node_returns_itself(void) {
  Node *root = insert(NULL, 10);
  TEST_ASSERT_EQUAL_INT(10, findMin(root)->data);
  freeTree(root);
}

void test_findMin_returns_leftmost_node(void) {
  Node *root = buildTree();
  TEST_ASSERT_EQUAL_INT(3, findMin(root)->data);
  freeTree(root);
}

/* ─── findMax ─────────────────────────────────────────────────────────────── */

void test_findMax_null_returns_null(void) {
  TEST_ASSERT_NULL(findMax(NULL));
}

void test_findMax_single_node_returns_itself(void) {
  Node *root = insert(NULL, 10);
  TEST_ASSERT_EQUAL_INT(10, findMax(root)->data);
  freeTree(root);
}

void test_findMax_returns_rightmost_node(void) {
  Node *root = buildTree();
  TEST_ASSERT_EQUAL_INT(20, findMax(root)->data);
  freeTree(root);
}

/* ─── height ──────────────────────────────────────────────────────────────── */

void test_height_null_is_zero(void) {
  TEST_ASSERT_EQUAL_INT(0, height(NULL));
}

void test_height_leaf_is_zero(void) {
  Node *n = createNode(5);
  TEST_ASSERT_EQUAL_INT(0, height(n));
  free(n);
}

void test_height_one_level(void) {
  Node *root = insert(NULL, 10);
  root = insert(root, 5);
  TEST_ASSERT_EQUAL_INT(1, height(root));
  freeTree(root);
}

void test_height_two_levels(void) {
  Node *root = buildTree();
  TEST_ASSERT_EQUAL_INT(2, height(root));
  freeTree(root);
}

void test_height_right_heavy_chain(void) {
  /* 10 → 15 → 20  (height = 2) */
  Node *root = insert(NULL, 10);
  root = insert(root, 15);
  root = insert(root, 20);
  TEST_ASSERT_EQUAL_INT(2, height(root));
  freeTree(root);
}

/* ─── size ────────────────────────────────────────────────────────────────── */

void test_size_null_is_zero(void) {
  TEST_ASSERT_EQUAL_INT(0, size(NULL));
}

void test_size_single_node(void) {
  Node *n = createNode(5);
  TEST_ASSERT_EQUAL_INT(1, size(n));
  free(n);
}

void test_size_full_tree(void) {
  Node *root = buildTree();
  TEST_ASSERT_EQUAL_INT(7, size(root));
  freeTree(root);
}

/* ─── isEmpty ─────────────────────────────────────────────────────────────── */

void test_isEmpty_null_returns_true(void) {
  TEST_ASSERT_TRUE(isEmpty(NULL));
}

void test_isEmpty_non_null_returns_false(void) {
  Node *n = createNode(1);
  TEST_ASSERT_FALSE(isEmpty(n));
  free(n);
}

/* ─── validateBST ─────────────────────────────────────────────────────────── */

void test_validateBST_null_is_valid(void) {
  TEST_ASSERT_TRUE(validateBST(NULL));
}

void test_validateBST_single_node_is_valid(void) {
  Node *n = createNode(5);
  TEST_ASSERT_TRUE(validateBST(n));
  free(n);
}

void test_validateBST_valid_tree(void) {
  Node *root = buildTree();
  TEST_ASSERT_TRUE(validateBST(root));
  freeTree(root);
}

void test_validateBST_invalid_tree(void) {
  /* Manually build an invalid BST:
   *     5
   *    / \
   *   3   7
   *        \
   *         4   <- 4 < 5 but in the right subtree of 5: invalid
   */
  Node *root = createNode(5);
  root->left_child = createNode(3);
  root->right_child = createNode(7);
  root->right_child->right_child = createNode(4);
  TEST_ASSERT_FALSE(validateBST(root));
  freeTree(root);
}

/* ─── findSuccessor ───────────────────────────────────────────────────────── */

void test_findSuccessor_null_root_returns_null(void) {
  TEST_ASSERT_NULL(findSuccessor(NULL, 5));
}

void test_findSuccessor_of_max_returns_null(void) {
  Node *root = buildTree();
  TEST_ASSERT_NULL(findSuccessor(root, 20));
  freeTree(root);
}

void test_findSuccessor_of_root(void) {
  /* In-order successor of 10 is 12 (min of right subtree). */
  Node *root = buildTree();
  Node *result = findSuccessor(root, 10);
  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_INT(12, result->data);
  freeTree(root);
}

void test_findSuccessor_internal_node(void) {
  /* Successor of 5 is 7 (right child of 5). */
  Node *root = buildTree();
  TEST_ASSERT_EQUAL_INT(7, findSuccessor(root, 5)->data);
  freeTree(root);
}

void test_findSuccessor_leaf_no_right_subtree(void) {
  /* Successor of 3 is 5 (lowest ancestor where we turned left). */
  Node *root = buildTree();
  TEST_ASSERT_EQUAL_INT(5, findSuccessor(root, 3)->data);
  freeTree(root);
}

void test_findSuccessor_cross_subtree(void) {
  /* Successor of 12 is 15 (lowest ancestor where we turned left). */
  Node *root = buildTree();
  TEST_ASSERT_EQUAL_INT(15, findSuccessor(root, 12)->data);
  freeTree(root);
}

/* ─── findPredecessor ─────────────────────────────────────────────────────── */

void test_findPredecessor_null_root_returns_null(void) {
  TEST_ASSERT_NULL(findPredecessor(NULL, 5));
}

void test_findPredecessor_of_min_returns_null(void) {
  Node *root = buildTree();
  TEST_ASSERT_NULL(findPredecessor(root, 3));
  freeTree(root);
}

void test_findPredecessor_of_root(void) {
  /* In-order predecessor of 10 is 7 (max of left subtree). */
  Node *root = buildTree();
  Node *result = findPredecessor(root, 10);
  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_INT(7, result->data);
  freeTree(root);
}

void test_findPredecessor_internal_node(void) {
  /* Predecessor of 5 is 3 (left child of 5). */
  Node *root = buildTree();
  TEST_ASSERT_EQUAL_INT(3, findPredecessor(root, 5)->data);
  freeTree(root);
}

void test_findPredecessor_leaf_no_left_subtree(void) {
  /* Predecessor of 7 is 5 (lowest ancestor where we turned right). */
  Node *root = buildTree();
  TEST_ASSERT_EQUAL_INT(5, findPredecessor(root, 7)->data);
  freeTree(root);
}

void test_findPredecessor_cross_subtree(void) {
  /* Predecessor of 20 is 15. */
  Node *root = buildTree();
  TEST_ASSERT_EQUAL_INT(15, findPredecessor(root, 20)->data);
  freeTree(root);
}

/* ─── countLeaves ─────────────────────────────────────────────────────────── */

void test_countLeaves_null_is_zero(void) {
  TEST_ASSERT_EQUAL_INT(0, countLeaves(NULL));
}

void test_countLeaves_single_node(void) {
  Node *n = createNode(1);
  TEST_ASSERT_EQUAL_INT(1, countLeaves(n));
  free(n);
}

void test_countLeaves_full_tree(void) {
  /* Leaves of the standard tree: 3, 7, 12, 20 */
  Node *root = buildTree();
  TEST_ASSERT_EQUAL_INT(4, countLeaves(root));
  freeTree(root);
}

void test_countLeaves_chain_has_one_leaf(void) {
  /* 10 → 15 → 20  has only one leaf (20) */
  Node *root = insert(NULL, 10);
  root = insert(root, 15);
  root = insert(root, 20);
  TEST_ASSERT_EQUAL_INT(1, countLeaves(root));
  freeTree(root);
}

/* ─── isBalanced ──────────────────────────────────────────────────────────── */

void test_isBalanced_null_is_true(void) {
  TEST_ASSERT_TRUE(isBalanced(NULL));
}

void test_isBalanced_single_node(void) {
  Node *n = createNode(5);
  TEST_ASSERT_TRUE(isBalanced(n));
  free(n);
}

void test_isBalanced_balanced_tree(void) {
  Node *root = buildTree();
  TEST_ASSERT_TRUE(isBalanced(root));
  freeTree(root);
}

void test_isBalanced_unbalanced_left_chain(void) {
  /* 10 → 5 → 3 → 1  (height diff at root = 3) */
  Node *root = insert(NULL, 10);
  root = insert(root, 5);
  root = insert(root, 3);
  root = insert(root, 1);
  TEST_ASSERT_FALSE(isBalanced(root));
  freeTree(root);
}

void test_isBalanced_unbalanced_right_chain(void) {
  /* 10 → 15 → 20 → 25 */
  Node *root = insert(NULL, 10);
  root = insert(root, 15);
  root = insert(root, 20);
  root = insert(root, 25);
  TEST_ASSERT_FALSE(isBalanced(root));
  freeTree(root);
}

/* ─── traversals (smoke tests — verify no crash) ─────────────────────────── */

void test_inOrder_null_does_not_crash(void) {
  inOrder(NULL);
}

void test_preOrder_null_does_not_crash(void) {
  preOrder(NULL);
}

void test_postOrder_null_does_not_crash(void) {
  postOrder(NULL);
}

void test_traversals_non_null_do_not_crash(void) {
  Node *root = buildTree();
  inOrder(root);   printf("\n");
  preOrder(root);  printf("\n");
  postOrder(root); printf("\n");
  freeTree(root);
}

/* ─── del ─────────────────────────────────────────────────────────────────── */

void test_del_null_tree_returns_null(void) {
  TEST_ASSERT_NULL(del(NULL, 10));
}

void test_del_nonexistent_key_returns_null(void) {
  /* del returns NULL when the key is not in the tree; root is not freed. */
  Node *root = buildTree();
  Node *result = del(root, 99);
  TEST_ASSERT_NULL(result);
  TEST_ASSERT_EQUAL_INT(7, size(root)); /* tree unchanged */
  freeTree(root);
}

void test_del_leaf_left_child(void) {
  /* Delete 3 (leaf, left child of 5). */
  Node *root = buildTree();
  root = del(root, 3);
  TEST_ASSERT_NULL(search(root, 3));
  TEST_ASSERT_EQUAL_INT(6, size(root));
  TEST_ASSERT_TRUE(validateBST(root));
  freeTree(root);
}

void test_del_leaf_right_child(void) {
  /* Delete 20 (leaf, right child of 15). */
  Node *root = buildTree();
  root = del(root, 20);
  TEST_ASSERT_NULL(search(root, 20));
  TEST_ASSERT_EQUAL_INT(6, size(root));
  TEST_ASSERT_TRUE(validateBST(root));
  freeTree(root);
}

void test_del_node_with_only_right_child(void) {
  /* Tree: 10 → right=15 → right=20.  Delete 15. */
  Node *root = insert(NULL, 10);
  root = insert(root, 15);
  root = insert(root, 20);
  root = del(root, 15);
  TEST_ASSERT_NULL(search(root, 15));
  TEST_ASSERT_NOT_NULL(search(root, 20));
  TEST_ASSERT_EQUAL_INT(2, size(root));
  TEST_ASSERT_TRUE(validateBST(root));
  freeTree(root);
}

void test_del_node_with_only_left_child(void) {
  /* Tree: 10 → right=15 → left=12.  Delete 15. */
  Node *root = insert(NULL, 10);
  root = insert(root, 15);
  root = insert(root, 12);
  root = del(root, 15);
  TEST_ASSERT_NULL(search(root, 15));
  TEST_ASSERT_NOT_NULL(search(root, 12));
  TEST_ASSERT_EQUAL_INT(2, size(root));
  TEST_ASSERT_TRUE(validateBST(root));
  freeTree(root);
}

void test_del_node_with_two_children(void) {
  /* Delete 5 (children: 3 and 7). Successor 7 replaces it. */
  Node *root = buildTree();
  root = del(root, 5);
  TEST_ASSERT_NULL(search(root, 5));
  TEST_ASSERT_NOT_NULL(search(root, 3));  /* left child preserved */
  TEST_ASSERT_NOT_NULL(search(root, 7));  /* successor value in tree  */
  TEST_ASSERT_EQUAL_INT(6, size(root));
  TEST_ASSERT_TRUE(validateBST(root));
  freeTree(root);
}

void test_del_root_leaf(void) {
  /* Single-node tree: deleting root returns NULL. */
  Node *root = insert(NULL, 10);
  root = del(root, 10);
  TEST_ASSERT_NULL(root);
}

void test_del_root_with_right_child_only(void) {
  /* Delete root 10; right child 15 becomes new root. */
  Node *root = insert(NULL, 10);
  root = insert(root, 15);
  root = del(root, 10);
  TEST_ASSERT_NOT_NULL(root);
  TEST_ASSERT_EQUAL_INT(15, root->data);
  TEST_ASSERT_EQUAL_INT(1, size(root));
  freeTree(root);
}

void test_del_root_with_left_child_only(void) {
  /* Delete root 10; left child 5 becomes new root. */
  Node *root = insert(NULL, 10);
  root = insert(root, 5);
  root = del(root, 10);
  TEST_ASSERT_NOT_NULL(root);
  TEST_ASSERT_EQUAL_INT(5, root->data);
  TEST_ASSERT_EQUAL_INT(1, size(root));
  freeTree(root);
}

void test_del_root_with_two_children(void) {
  /* Delete root 10; successor 12 takes its place. */
  Node *root = buildTree();
  root = del(root, 10);
  TEST_ASSERT_NULL(search(root, 10));
  TEST_ASSERT_EQUAL_INT(6, size(root));
  TEST_ASSERT_TRUE(validateBST(root));
  /* Root now stores the former in-order successor of 10 (12). */
  TEST_ASSERT_EQUAL_INT(12, root->data);
  freeTree(root);
}

void test_del_preserves_bst_property(void) {
  /* Delete every node one by one; BST property must hold after each step. */
  int values[] = {10, 5, 15, 3, 7, 12, 20};
  int n = 7;
  Node *root = buildTree();
  for (int i = 0; i < n; i++) {
    root = del(root, values[i]);
    if (root != NULL) {
      TEST_ASSERT_TRUE(validateBST(root));
    }
  }
  TEST_ASSERT_NULL(root);
}

/* ─── main ────────────────────────────────────────────────────────────────── */

int main(void) {
  UNITY_BEGIN();

  /* createNode */
  RUN_TEST(test_createNode_returns_non_null);
  RUN_TEST(test_createNode_stores_data);
  RUN_TEST(test_createNode_children_are_null);

  /* createBST / destroyBST */
  RUN_TEST(test_createBST_returns_non_null);
  RUN_TEST(test_createBST_root_is_null);
  RUN_TEST(test_destroyBST_null_does_not_crash);
  RUN_TEST(test_destroyBST_empty_tree_does_not_crash);
  RUN_TEST(test_destroyBST_non_empty_tree_does_not_crash);

  /* insert */
  RUN_TEST(test_insert_into_null_creates_root);
  RUN_TEST(test_insert_smaller_value_goes_left);
  RUN_TEST(test_insert_larger_value_goes_right);
  RUN_TEST(test_insert_duplicate_is_ignored);
  RUN_TEST(test_insert_maintains_bst_property);
  RUN_TEST(test_insert_increases_size);

  /* search */
  RUN_TEST(test_search_null_tree_returns_null);
  RUN_TEST(test_search_existing_value_returns_node);
  RUN_TEST(test_search_nonexistent_value_returns_null);
  RUN_TEST(test_search_root_value_returns_root);
  RUN_TEST(test_search_left_subtree);
  RUN_TEST(test_search_right_subtree);

  /* findMin */
  RUN_TEST(test_findMin_null_returns_null);
  RUN_TEST(test_findMin_single_node_returns_itself);
  RUN_TEST(test_findMin_returns_leftmost_node);

  /* findMax */
  RUN_TEST(test_findMax_null_returns_null);
  RUN_TEST(test_findMax_single_node_returns_itself);
  RUN_TEST(test_findMax_returns_rightmost_node);

  /* height */
  RUN_TEST(test_height_null_is_zero);
  RUN_TEST(test_height_leaf_is_zero);
  RUN_TEST(test_height_one_level);
  RUN_TEST(test_height_two_levels);
  RUN_TEST(test_height_right_heavy_chain);

  /* size */
  RUN_TEST(test_size_null_is_zero);
  RUN_TEST(test_size_single_node);
  RUN_TEST(test_size_full_tree);

  /* isEmpty */
  RUN_TEST(test_isEmpty_null_returns_true);
  RUN_TEST(test_isEmpty_non_null_returns_false);

  /* validateBST */
  RUN_TEST(test_validateBST_null_is_valid);
  RUN_TEST(test_validateBST_single_node_is_valid);
  RUN_TEST(test_validateBST_valid_tree);
  RUN_TEST(test_validateBST_invalid_tree);

  /* findSuccessor */
  RUN_TEST(test_findSuccessor_null_root_returns_null);
  RUN_TEST(test_findSuccessor_of_max_returns_null);
  RUN_TEST(test_findSuccessor_of_root);
  RUN_TEST(test_findSuccessor_internal_node);
  RUN_TEST(test_findSuccessor_leaf_no_right_subtree);
  RUN_TEST(test_findSuccessor_cross_subtree);

  /* findPredecessor */
  RUN_TEST(test_findPredecessor_null_root_returns_null);
  RUN_TEST(test_findPredecessor_of_min_returns_null);
  RUN_TEST(test_findPredecessor_of_root);
  RUN_TEST(test_findPredecessor_internal_node);
  RUN_TEST(test_findPredecessor_leaf_no_left_subtree);
  RUN_TEST(test_findPredecessor_cross_subtree);

  /* countLeaves */
  RUN_TEST(test_countLeaves_null_is_zero);
  RUN_TEST(test_countLeaves_single_node);
  RUN_TEST(test_countLeaves_full_tree);
  RUN_TEST(test_countLeaves_chain_has_one_leaf);

  /* isBalanced */
  RUN_TEST(test_isBalanced_null_is_true);
  RUN_TEST(test_isBalanced_single_node);
  RUN_TEST(test_isBalanced_balanced_tree);
  RUN_TEST(test_isBalanced_unbalanced_left_chain);
  RUN_TEST(test_isBalanced_unbalanced_right_chain);

  /* traversals */
  RUN_TEST(test_inOrder_null_does_not_crash);
  RUN_TEST(test_preOrder_null_does_not_crash);
  RUN_TEST(test_postOrder_null_does_not_crash);
  RUN_TEST(test_traversals_non_null_do_not_crash);

  /* del */
  RUN_TEST(test_del_null_tree_returns_null);
  RUN_TEST(test_del_nonexistent_key_returns_null);
  RUN_TEST(test_del_leaf_left_child);
  RUN_TEST(test_del_leaf_right_child);
  RUN_TEST(test_del_node_with_only_right_child);
  RUN_TEST(test_del_node_with_only_left_child);
  RUN_TEST(test_del_node_with_two_children);
  RUN_TEST(test_del_root_leaf);
  RUN_TEST(test_del_root_with_right_child_only);
  RUN_TEST(test_del_root_with_left_child_only);
  RUN_TEST(test_del_root_with_two_children);
  RUN_TEST(test_del_preserves_bst_property);

  return UNITY_END();
}