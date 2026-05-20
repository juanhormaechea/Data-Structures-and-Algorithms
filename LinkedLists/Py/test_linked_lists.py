import unittest
import linked_lists

class TestAppend(unittest.TestCase):
    def test_empty_list(self):
        list = linked_lists.LinkedList()
        list.append(1)
        self.assertEqual(1, list.get_size())
        self.assertEqual(list.head.data, 1)
        self.assertIsNone(list.head.next)

    def test_one_node(self):
        list = linked_lists.LinkedList()
        list.head = linked_lists.Node(0)
        list._size+=1
        list.append(1)
        self.assertEqual(2, list.get_size())
        self.assertEqual(0, list.head.data)
        self.assertEqual(1, list.head.next.data)
        self.assertIsNone(list.head.next.next)

    def test_full_list(self):
        list = linked_lists.LinkedList()
        list.head = linked_lists.Node(0)
        head = list.head
        list._size+=1
        for i in range(1, 5):
            new_node = linked_lists.Node(i)
            head.next = new_node
            head = head.next
            list._size+=1
        list.append(5)
        

        self.assertEqual(6, list.get_size())

        head = list.head
        for i in range(0,6):
            self.assertEqual(i, head.data)
            head = head.next
        

class TestPop(unittest.TestCase):
    def test_empty_list(self):
        list = linked_lists.LinkedList()
        value = list.pop()
        self.assertIsNone(value)
        self.assertEqual(0, list.get_size())
    
    def test_one_node(self):
        list = linked_lists.LinkedList()
        list.append(1)
        value = list.pop()
        self.assertEqual(0, list.get_size())
        self.assertEqual(1, value)
        self.assertIsNone(list.head)
    
    def test_full_list(self):
        list = linked_lists.LinkedList()
        for i in range(0, 10):
            list.append(i)
        value = list.pop()
        self.assertEqual(9, list.get_size())
        self.assertEqual(9, value)
        head = list.head
        while head.next is not None:
            head = head.next
        self.assertEqual(8, head.data)


class TestInsert(unittest.TestCase):
    def test_index_out_of_bounds(self):
        list = linked_lists.LinkedList()
        self.assertRaises(ValueError, list.insert_node, 1, -1)
        self.assertRaises(ValueError, list.insert_node, 1, 1)
        
        for i in range(0, 5):
            list.append(i)

        self.assertRaises(ValueError, list.insert_node, 5, 6)
        self.assertRaises(ValueError, list.insert_node, 6, -1)

    def test_empty_list(self):
        list = linked_lists.LinkedList()
        list.insert_node(1, 0)
        self.assertEqual(1, list.get_size())
        self.assertEqual(list.head.data, 1)
        self.assertIsNone(list.head.next)
    
    def test_insert_start_of_list(self):
        list = linked_lists.LinkedList()
        list.head = linked_lists.Node(1)
        list._size+=1
        list.insert_node(0, 0)
        self.assertEqual(2, list.get_size())
        self.assertEqual(0, list.head.data)
        self.assertEqual(1, list.pop())

    def test_insert_end_of_list(self):
        list = linked_lists.LinkedList()
        for i in range(0, 5):
            list.append(i)
            
        list.insert_node(5, 5)
        self.assertEqual(6, list.get_size())
        head = list.head
        for i in range(1, 5):
            head = head.next
        self.assertEqual(5, head.next.data)
        self.assertIsNone(head.next.next)
    
    def test_insert_middle_point(self):
        list = linked_lists.LinkedList()
        for i in range(0, 5):
            list.append(i)
        list.insert_node(24, 3)
        self.assertEqual(6, list.get_size())
        head = list.head
        for i in range(1, 4):
            head = head.next
        self.assertEqual(24, head.data)
        
            
        

if __name__ == '__main__':
    unittest.main()
    


