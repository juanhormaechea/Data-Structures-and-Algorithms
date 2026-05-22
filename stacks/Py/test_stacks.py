import unittest
import stacks

class TestPush(unittest.TestCase):
    def test_empty_list(self):
        stack = stacks.Stack()
        stack.push(1)
        self.assertEqual(1, stack._size)
        self.assertEqual(1, stack.head.data)
    
    def test_full_list(self):
        stack = stacks.Stack()
        for i in range(0, 10):
            stack.push(i)
        self.assertEqual(10, stack._size)
        head = stack.head
        for i in range(9, -1, -1):
            self.assertEqual(i, head.data)
            head = head.next


class TestPop(unittest.TestCase):
    def test_empty_list(self):
        stack = stacks.Stack()
        self.assertIsNone(stack.pop())
        self.assertEqual(0, stack._size)
    
    def test_one_node(self):
        stack = stacks.Stack()
        stack.push(1)
        value = stack.pop()
        self.assertEqual(0, stack._size)
        self.assertEqual(1, value)
        self.assertIsNone(stack.head)
    
    def test_full_list(self):
        stack = stacks.Stack()
        for i in range(0, 10):
            stack.push(i)
        value = stack.pop()
        self.assertEqual(9, stack._size)
        self.assertEqual(9, value)
        self.assertEqual(8, stack.head.data)
    

class TestPeek(unittest.TestCase):
    def test_empty_list(self):
        stack = stacks.Stack()
        self.assertIsNone(stack.peek())
    
    def test_one_node(self):
        stack = stacks.Stack()
        stack.push(1)
        value = stack.peek()
        self.assertEqual(1, value)
    
    def test_full_list(self):
        stack = stacks.Stack()
        for i in range(0, 10):
            stack.push(i)
        
        value = stack.peek()
        self.assertEqual(9, value)

class TestIsEmpty(unittest.TestCase):
    def test_empty_list(self):
        stack = stacks.Stack()
        self.assertTrue(stack.isEmpty())
    
    def test_one_node(self):
        stack = stacks.Stack()
        stack.push(1)
        self.assertFalse(stack.isEmpty())
    
    def test_full_list(self):
        stack = stacks.Stack()
        for i in range(0, 10):
            stack.push(i)
        self.assertFalse(stack.isEmpty())

class TestStackSize(unittest.TestCase):
    def test_empty_list(self):
        stack = stacks.Stack()
        self.assertEqual(0, stack.stackSize())
    
    def test_one_node(self):
        stack = stacks.Stack()
        stack.push(1)
        self.assertEqual(1, stack.stackSize())
    
    def test_full_list(self):
        stack = stacks.Stack()
        for i in range(0, 10):
            stack.push(i)
        self.assertEqual(10, stack.stackSize())
    


if __name__ == '__main__':
    unittest.main()