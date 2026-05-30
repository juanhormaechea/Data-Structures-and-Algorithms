import unittest
import io
import contextlib
from bst import BST, Node


class TestBST(unittest.TestCase):
    """
    Standard test tree built in setUp:

              10
             /  \\
            5    15
           / \\   / \\
          3   7 12  20

    height=2 | size=7 | leaves=4 (3, 7, 12, 20)
    """

    def setUp(self):
        self.bst = BST()
        for v in [10, 5, 15, 3, 7, 12, 20]:
            self.bst.insert(v)

    # ── helper ────────────────────────────────────────────────────────────

    def _capture(self, fn) -> str:
        """Return stdout produced by a traversal method."""
        buf = io.StringIO()
        with contextlib.redirect_stdout(buf):
            fn()
        return buf.getvalue()

    # ── insert ────────────────────────────────────────────────────────────

    def test_insert_into_empty_tree(self):
        bst = BST()
        bst.insert(10)
        self.assertIsNotNone(bst.root)
        self.assertEqual(bst.root.data, 10)

    def test_insert_smaller_value_goes_left(self):
        bst = BST()
        bst.insert(10)
        bst.insert(5)
        self.assertIsNotNone(bst.root.left_child)
        self.assertEqual(bst.root.left_child.data, 5)

    def test_insert_larger_value_goes_right(self):
        bst = BST()
        bst.insert(10)
        bst.insert(15)
        self.assertIsNotNone(bst.root.right_child)
        self.assertEqual(bst.root.right_child.data, 15)

    def test_insert_duplicate_is_ignored(self):
        initial_size = self.bst.size()
        self.bst.insert(10)
        self.assertEqual(self.bst.size(), initial_size)

    def test_insert_maintains_bst_property(self):
        self.assertTrue(self.bst.validateBST())

    def test_insert_increases_size(self):
        self.bst.insert(99)
        self.assertEqual(self.bst.size(), 8)

    # ── search ────────────────────────────────────────────────────────────

    def test_search_empty_tree_returns_none(self):
        self.assertIsNone(BST().search(10))

    def test_search_existing_key_returns_node(self):
        node = self.bst.search(7)
        self.assertIsNotNone(node)
        self.assertEqual(node.data, 7)

    def test_search_nonexistent_key_returns_none(self):
        self.assertIsNone(self.bst.search(99))

    def test_search_root_returns_root_node(self):
        self.assertIs(self.bst.search(10), self.bst.root)

    def test_search_leftmost_leaf(self):
        self.assertEqual(self.bst.search(3).data, 3)

    def test_search_rightmost_leaf(self):
        self.assertEqual(self.bst.search(20).data, 20)

    # ── findMin ───────────────────────────────────────────────────────────

    def test_findMin_empty_tree_returns_none(self):
        self.assertIsNone(BST().findMin())

    def test_findMin_single_node(self):
        bst = BST()
        bst.insert(10)
        self.assertEqual(bst.findMin().data, 10)

    def test_findMin_returns_leftmost_node(self):
        self.assertEqual(self.bst.findMin().data, 3)

    # ── findMax ───────────────────────────────────────────────────────────

    def test_findMax_empty_tree_returns_none(self):
        self.assertIsNone(BST().findMax())

    def test_findMax_single_node(self):
        bst = BST()
        bst.insert(10)
        self.assertEqual(bst.findMax().data, 10)

    def test_findMax_returns_rightmost_node(self):
        self.assertEqual(self.bst.findMax().data, 20)

    # ── height ────────────────────────────────────────────────────────────

    def test_height_empty_tree(self):
        self.assertEqual(BST().height(), 0)

    def test_height_single_node_is_zero(self):
        bst = BST()
        bst.insert(10)
        self.assertEqual(bst.height(), 0)

    def test_height_one_level(self):
        bst = BST()
        bst.insert(10)
        bst.insert(5)
        self.assertEqual(bst.height(), 1)

    def test_height_two_levels(self):
        self.assertEqual(self.bst.height(), 2)

    def test_height_right_heavy_chain(self):
        bst = BST()
        for v in [10, 15, 20]:
            bst.insert(v)
        self.assertEqual(bst.height(), 2)

    # ── size ──────────────────────────────────────────────────────────────

    def test_size_empty_tree(self):
        self.assertEqual(BST().size(), 0)

    def test_size_single_node(self):
        bst = BST()
        bst.insert(10)
        self.assertEqual(bst.size(), 1)

    def test_size_full_tree(self):
        self.assertEqual(self.bst.size(), 7)

    # ── validateBST ───────────────────────────────────────────────────────

    def test_validateBST_empty_tree(self):
        self.assertTrue(BST().validateBST())

    def test_validateBST_single_node(self):
        bst = BST()
        bst.insert(10)
        self.assertTrue(bst.validateBST())

    def test_validateBST_valid_tree(self):
        self.assertTrue(self.bst.validateBST())

    def test_validateBST_invalid_tree(self):
        """Manually attach node 4 as right child of 7.
        4 < 5 (grandparent), so this violates the BST property."""
        self.bst.root.left_child.right_child.right_child = Node(4)
        self.assertFalse(self.bst.validateBST())

    # ── inOrder ───────────────────────────────────────────────────────────

    def test_inOrder_empty_tree_produces_no_output(self):
        self.assertEqual(self._capture(BST().inOrder), '')

    def test_inOrder_output_is_sorted(self):
        values = list(map(int, self._capture(self.bst.inOrder).split()))
        self.assertEqual(values, sorted(values))

    def test_inOrder_contains_all_values(self):
        values = set(map(int, self._capture(self.bst.inOrder).split()))
        self.assertEqual(values, {3, 5, 7, 10, 12, 15, 20})

    # ── preOrder ──────────────────────────────────────────────────────────

    def test_preOrder_empty_tree_produces_no_output(self):
        self.assertEqual(self._capture(BST().preOrder), '')

    def test_preOrder_root_is_first(self):
        values = list(map(int, self._capture(self.bst.preOrder).split()))
        self.assertEqual(values[0], 10)

    def test_preOrder_contains_all_values(self):
        values = set(map(int, self._capture(self.bst.preOrder).split()))
        self.assertEqual(values, {3, 5, 7, 10, 12, 15, 20})

    # ── postOrder ─────────────────────────────────────────────────────────

    def test_postOrder_empty_tree_produces_no_output(self):
        self.assertEqual(self._capture(BST().postOrder), '')

    def test_postOrder_root_is_last(self):
        values = list(map(int, self._capture(self.bst.postOrder).split()))
        self.assertEqual(values[-1], 10)

    def test_postOrder_contains_all_values(self):
        values = set(map(int, self._capture(self.bst.postOrder).split()))
        self.assertEqual(values, {3, 5, 7, 10, 12, 15, 20})

    # ── findSuccessor ─────────────────────────────────────────────────────

    def test_findSuccessor_empty_tree_returns_none(self):
        self.assertIsNone(BST().findSuccessor(5))

    def test_findSuccessor_of_max_returns_none(self):
        self.assertIsNone(self.bst.findSuccessor(20))

    def test_findSuccessor_of_root(self):
        # In-order successor of 10 is 12 (min of right subtree)
        self.assertEqual(self.bst.findSuccessor(10).data, 12)

    def test_findSuccessor_internal_node(self):
        # Successor of 5 is 7 (right child of 5)
        self.assertEqual(self.bst.findSuccessor(5).data, 7)

    def test_findSuccessor_leaf_no_right_subtree(self):
        # Successor of 3 is 5 (lowest ancestor where we turned left)
        self.assertEqual(self.bst.findSuccessor(3).data, 5)

    def test_findSuccessor_cross_subtree(self):
        # Successor of 12 is 15
        self.assertEqual(self.bst.findSuccessor(12).data, 15)

    # ── findPredecessor ───────────────────────────────────────────────────

    def test_findPredecessor_empty_tree_returns_none(self):
        self.assertIsNone(BST().findPredecessor(5))

    def test_findPredecessor_of_min_returns_none(self):
        self.assertIsNone(self.bst.findPredecessor(3))

    def test_findPredecessor_of_root(self):
        # In-order predecessor of 10 is 7 (max of left subtree)
        self.assertEqual(self.bst.findPredecessor(10).data, 7)

    def test_findPredecessor_internal_node(self):
        # Predecessor of 5 is 3 (left child of 5)
        self.assertEqual(self.bst.findPredecessor(5).data, 3)

    def test_findPredecessor_leaf_no_left_subtree(self):
        # Predecessor of 7 is 5 (lowest ancestor where we turned right)
        self.assertEqual(self.bst.findPredecessor(7).data, 5)

    def test_findPredecessor_cross_subtree(self):
        # Predecessor of 20 is 15
        self.assertEqual(self.bst.findPredecessor(20).data, 15)

    # ── countLeaves ───────────────────────────────────────────────────────

    def test_countLeaves_empty_tree(self):
        self.assertEqual(BST().countLeaves(), 0)

    def test_countLeaves_single_node(self):
        bst = BST()
        bst.insert(10)
        self.assertEqual(bst.countLeaves(), 1)

    def test_countLeaves_full_tree(self):
        # Leaves: 3, 7, 12, 20
        self.assertEqual(self.bst.countLeaves(), 4)

    def test_countLeaves_chain_has_one_leaf(self):
        bst = BST()
        for v in [10, 15, 20]:
            bst.insert(v)
        self.assertEqual(bst.countLeaves(), 1)

    # ── isBalanced ────────────────────────────────────────────────────────

    def test_isBalanced_empty_tree(self):
        self.assertTrue(BST().isBalanced())

    def test_isBalanced_single_node(self):
        bst = BST()
        bst.insert(10)
        self.assertTrue(bst.isBalanced())

    def test_isBalanced_balanced_tree(self):
        self.assertTrue(self.bst.isBalanced())

    def test_isBalanced_left_chain_is_unbalanced(self):
        # 10 → 5 → 3 → 1  (height diff at root = 3)
        bst = BST()
        for v in [10, 5, 3, 1]:
            bst.insert(v)
        self.assertFalse(bst.isBalanced())

    def test_isBalanced_right_chain_is_unbalanced(self):
        bst = BST()
        for v in [10, 15, 20, 25]:
            bst.insert(v)
        self.assertFalse(bst.isBalanced())

    # ── delete ────────────────────────────────────────────────────────────

    def test_delete_nonexistent_key_leaves_tree_unchanged(self):
        self.bst.delete(99)
        self.assertEqual(self.bst.size(), 7)
        self.assertTrue(self.bst.validateBST())

    def test_delete_leaf_left_child(self):
        self.bst.delete(3)
        self.assertIsNone(self.bst.search(3))
        self.assertEqual(self.bst.size(), 6)
        self.assertTrue(self.bst.validateBST())

    def test_delete_leaf_right_child(self):
        self.bst.delete(20)
        self.assertIsNone(self.bst.search(20))
        self.assertEqual(self.bst.size(), 6)
        self.assertTrue(self.bst.validateBST())

    def test_delete_node_with_only_right_child(self):
        # Tree: 10 → right=15 → right=20. Delete 15.
        bst = BST()
        for v in [10, 15, 20]:
            bst.insert(v)
        bst.delete(15)
        self.assertIsNone(bst.search(15))
        self.assertIsNotNone(bst.search(20))
        self.assertEqual(bst.size(), 2)
        self.assertTrue(bst.validateBST())

    def test_delete_node_with_only_left_child(self):
        # Tree: 10 → right=15 → left=12. Delete 15.
        bst = BST()
        for v in [10, 15, 12]:
            bst.insert(v)
        bst.delete(15)
        self.assertIsNone(bst.search(15))
        self.assertIsNotNone(bst.search(12))
        self.assertEqual(bst.size(), 2)
        self.assertTrue(bst.validateBST())

    def test_delete_node_with_two_children(self):
        # Delete 5 (children 3 and 7). Successor 7 takes its place.
        self.bst.delete(5)
        self.assertIsNone(self.bst.search(5))
        self.assertIsNotNone(self.bst.search(3))   # left subtree preserved
        self.assertIsNotNone(self.bst.search(7))   # successor value still in tree
        self.assertEqual(self.bst.size(), 6)
        self.assertTrue(self.bst.validateBST())

    def test_delete_root_only_node(self):
        bst = BST()
        bst.insert(10)
        bst.delete(10)
        self.assertIsNone(bst.root)

    def test_delete_root_with_right_child_only(self):
        bst = BST()
        bst.insert(10)
        bst.insert(15)
        bst.delete(10)
        self.assertIsNotNone(bst.root)
        self.assertEqual(bst.root.data, 15)
        self.assertEqual(bst.size(), 1)

    def test_delete_root_with_left_child_only(self):
        bst = BST()
        bst.insert(10)
        bst.insert(5)
        bst.delete(10)
        self.assertIsNotNone(bst.root)
        self.assertEqual(bst.root.data, 5)
        self.assertEqual(bst.size(), 1)

    def test_delete_root_with_two_children(self):
        # Delete root 10; successor 12 takes its place.
        self.bst.delete(10)
        self.assertIsNone(self.bst.search(10))
        self.assertEqual(self.bst.root.data, 12)
        self.assertEqual(self.bst.size(), 6)
        self.assertTrue(self.bst.validateBST())

    def test_delete_all_nodes_preserves_bst_property(self):
        for v in [10, 5, 15, 3, 7, 12, 20]:
            self.bst.delete(v)
            self.assertTrue(self.bst.validateBST())
        self.assertEqual(self.bst.size(), 0)


if __name__ == '__main__':
    unittest.main()