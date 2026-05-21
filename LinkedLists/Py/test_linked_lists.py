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


class TestRemove(unittest.TestCase):
    def test_index_out_of_bounds(self):
        list = linked_lists.LinkedList()
        self.assertRaises(ValueError, list.remove_node, 0)
        for i in range(0, 5):
            list.append(i)
        self.assertRaises(ValueError, list.remove_node, -1)
        self.assertRaises(ValueError, list.remove_node, 5)
    
    def test_first_node(self):
        list = linked_lists.LinkedList()
        list.append(1)
        value = list.remove_node(0)
        self.assertEqual(1, value)
        self.assertEqual(0, list.get_size())
        self.assertIsNone(list.head)
        for i in range(1, 5):
            list.append(i)
        value = list.remove_node(0)
        self.assertEqual(1, value)
        self.assertEqual(2, list.head.data)
        self.assertEqual(3, list.get_size())    
    
    def test_last_node(self):
        list = linked_lists.LinkedList()
        for i in range(0, 5):
            list.append(i)
        value = list.remove_node(4)
        self.assertEqual(4, value)
        self.assertEqual(4, list.get_size())
        head = list.head
        while head.next is not None:
            head = head.next
        self.assertEqual(3, head.data)

    def test_middle_node(self):
        list = linked_lists.LinkedList()
        for i in range(0, 7):
            list.append(i)
        value = list.remove_node(4)
        self.assertEqual(4, value)
        self.assertEqual(6, list.get_size())
        prev = list.head
        for i in range(1, 4):
            prev = prev.next
        next = prev.next
        self.assertEqual(3, prev.data)
        self.assertEqual(5, next.data)
    

class TestSearch(unittest.TestCase):
    def test_search_empty_list(self):
        list = linked_lists.LinkedList()
        index = list.search_node(1)
        self.assertIsNone(index)
    
    def test_search_node_not_present(self):
        list = linked_lists.LinkedList()
        for i in range(0, 10):
            list.append(i)
        index = list.search_node(10)
        self.assertIsNone(index)
    
    def test_search_first_node(self):
        list = linked_lists.LinkedList()
        list.append(0)
        index = list.search_node(0)
        self.assertEqual(0, index)
        for i in range(1, 10):
            list.append(i)
        index = list.search_node(0)
        self.assertEqual(0, index)
    
    def test_search_last_node(self):
        list = linked_lists.LinkedList()
        for i in range(0, 10):
            list.append(i)
        index = list.search_node(9)
        self.assertEqual(9, index)
        

class TestSort(unittest.TestCase):
    def test_empty_list(self):
        list = linked_lists.LinkedList()
        node = list.sort_list()
        self.assertIsNone(node)
        self.assertEqual(node, list.head)
    
    def test_one_node(self):
        list = linked_lists.LinkedList()
        list.append(1)
        value = list.sort_list()
        self.assertEqual(1, list.get_size())
        self.assertEqual(1, list.head.data)
        self.assertEqual(value, list.head)
    
    def test_already_sorted(self):
        list = linked_lists.LinkedList()
        for i in range(0, 10):
            list.append(i)
        list.sort_list()
        self.assertEqual(10, list.get_size())
        head = list.head
        for i in range(0, 10):
            self.assertEqual(i, head.data)
            head = head.next
    
    def test_even_size(self):
        input_arr = [5, 2, 8, 1, 9, 3, 7, 4, 6, 0]
        expected = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
        list = linked_lists.LinkedList()
        for i in input_arr:
            list.append(i)
        list.sort_list()
        self.assertEqual(10, list.get_size())
        head = list.head
        for i in range(0, 10):
            self.assertEqual(head.data, expected[i])
            head = head.next
    
    def test_odd_size(self):
        input_arr = [5, 2, 8, 1, 9, 3, 7, 4, 6]
        expected = [1, 2, 3, 4, 5, 6, 7, 8, 9]
        list = linked_lists.LinkedList()
        for i in input_arr:
            list.append(i)
        list.sort_list()
        self.assertEqual(9, list.get_size())
        head = list.head
        for i in range(0, 9):
            self.assertEqual(head.data, expected[i])
            head = head.next
    
    def test_reverse_sorted(self):
        input_arr = [9, 8, 7, 6, 5, 4, 3, 2, 1, 0]
        expected = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
        list = linked_lists.LinkedList()
        for i in input_arr:
            list.append(i)
        list.sort_list()
        self.assertEqual(10, list.get_size())
        head = list.head
        for i in range(0, 10):
            self.assertEqual(head.data, expected[i])
            head = head.next
    
    def test_negatives(self):
        input_arr = [-5, -3, -8, -2, -7, -4, -9, -6, -1, -0]
        expected = [-9, -8, -7, -6, -5, -4, -3, -2, -1, -0]
        list = linked_lists.LinkedList()
        for i in input_arr:
            list.append(i)
        list.sort_list()
        self.assertEqual(10, list.get_size())
        head = list.head
        for i in range(0, 10):
            self.assertEqual(head.data, expected[i])
            head = head.next
        
        
            
        

if __name__ == '__main__':
    unittest.main()
    


