import unittest
import sys
import io
from avl import AVLT, AVLNode

class TestAVLT(unittest.TestCase):

    def setUp(self):
        self.tree = AVLT()

    def test_isEmpty_and_size_initial(self):
        self.assertTrue(self.tree.isEmpty())
        self.assertEqual(self.tree.size(), 0)
        self.assertEqual(self.tree.height(), 0)
        self.assertEqual(self.tree.countLeaves(), 0)

    def test_insert_and_validate(self):
        # Insert elements to trigger various rotations (LL, RR, LR, RL)
        elements = [10, 20, 30, 40, 50, 25]
        for el in elements:
            self.tree.insert(el)
            self.assertTrue(self.tree.validateAVL(), f"Tree invalid after inserting {el}")
        
        self.assertFalse(self.tree.isEmpty())
        self.assertEqual(self.tree.size(), 6)

    def test_search(self):
        for el in [15, 10, 20, 5, 3]:
            self.tree.insert(el)
        
        node = self.tree.search(10)
        self.assertIsNotNone(node)
        self.assertEqual(node.data, 10)
        
        node = self.tree.search(100)
        self.assertIsNone(node)

    def test_findMin_and_findMax(self):
        self.assertIsNone(self.tree.findMin())
        self.assertIsNone(self.tree.findMax())
        
        elements = [50, 30, 70, 20, 40, 60, 80]
        for el in elements:
            self.tree.insert(el)
            
        self.assertEqual(self.tree.findMin().data, 20)
        self.assertEqual(self.tree.findMax().data, 80)

    def test_delete(self):
        elements = [50, 30, 70, 20, 40, 60, 80, 10, 25]
        for el in elements:
            self.tree.insert(el)
        
        # Delete leaf
        self.tree.delete(10)
        self.assertTrue(self.tree.validateAVL())
        self.assertIsNone(self.tree.search(10))
        
        # Delete node with one child
        self.tree.delete(20)
        self.assertTrue(self.tree.validateAVL())
        self.assertIsNone(self.tree.search(20))
        
        # Delete node with two children
        self.tree.delete(30)
        self.assertTrue(self.tree.validateAVL())
        self.assertIsNone(self.tree.search(30))
        
        # Delete root (two children)
        self.tree.delete(50)
        self.assertTrue(self.tree.validateAVL())
        self.assertIsNone(self.tree.search(50))
        self.assertEqual(self.tree.size(), 5)

    def test_findSuccessor_and_findPredecessor(self):
        elements = [20, 10, 30, 5, 15, 25, 35]
        for el in elements:
            self.tree.insert(el)
            
        # Successors
        self.assertEqual(self.tree.findSuccessor(10).data, 15)
        self.assertEqual(self.tree.findSuccessor(15).data, 20)
        self.assertEqual(self.tree.findSuccessor(35), None)
        self.assertEqual(self.tree.findSuccessor(12).data, 15) # 12 not in tree
        
        # Predecessors
        self.assertEqual(self.tree.findPredecessor(30).data, 25)
        self.assertEqual(self.tree.findPredecessor(20).data, 15)
        self.assertEqual(self.tree.findPredecessor(5), None)
        self.assertEqual(self.tree.findPredecessor(22).data, 20) # 22 not in tree

    def test_metrics(self):
        elements = [10, 5, 15]
        for el in elements:
            self.tree.insert(el)
            
        self.assertEqual(self.tree.size(), 3)
        self.assertEqual(self.tree.height(), 1)
        self.assertEqual(self.tree.countLeaves(), 2)
        
        self.tree.insert(2)
        self.assertEqual(self.tree.height(), 2)
        self.assertEqual(self.tree.countLeaves(), 2)

    def test_traversals(self):
        elements = [20, 10, 30]
        for el in elements:
            self.tree.insert(el)
            
        # Capture stdout for inOrder
        captured_output = io.StringIO()
        sys.stdout = captured_output
        self.tree.inOrder()
        self.assertEqual(captured_output.getvalue().strip(), "10 20 30")
        
        # Capture stdout for preOrder
        captured_output = io.StringIO()
        sys.stdout = captured_output
        self.tree.preOrder()
        self.assertEqual(captured_output.getvalue().strip(), "20 10 30")
        
        # Capture stdout for postOrder
        captured_output = io.StringIO()
        sys.stdout = captured_output
        self.tree.postOrder()
        self.assertEqual(captured_output.getvalue().strip(), "10 30 20")
        
        # Restore stdout
        sys.stdout = sys.__stdout__

if __name__ == '__main__':
    unittest.main()
