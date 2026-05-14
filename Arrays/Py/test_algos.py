import unittest
import algos

class TestBubbleSort(unittest.TestCase):
    def test_unordered_array(self):
        input = [5,17,59,1,53,102,3,53,21,116,53,22]
        output = [1, 3, 5, 17, 21, 22, 53, 53, 53, 59, 102, 116]
        self.assertEqual(output, algos.bubble_sort(input))
    
    def test_single_element(self):
        input = [65]
        output = [65]
        self.assertEqual(output, algos.bubble_sort(input))

    def test_empty_array(self):
        input = []
        output = []
        self.assertEqual(output, algos.bubble_sort(input))

    def test_already_sorted(self):
        input = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        output = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        self.assertEqual(output, algos.bubble_sort(input))

    def test_negative_values(self):
        input = [-1, -9, -2, -7, -5, -3, -12, -24, -3]
        output = [-24, -12, -9, -7, -5, -3, -3, -2, -1]
        self.assertEqual(output, algos.bubble_sort(input))


class TestSelectionSort(unittest.TestCase):
     def test_unordered_array(self):
        input = [5,17,59,1,53,102,3,53,21,116,53,22]
        output = [1, 3, 5, 17, 21, 22, 53, 53, 53, 59, 102, 116]
        self.assertEqual(output, algos.selection_sort(input))
    
     def test_single_element(self):
        input = [65]
        output = [65]
        self.assertEqual(output, algos.selection_sort(input))

     def test_empty_array(self):
        input = []
        output = []
        self.assertEqual(output, algos.selection_sort(input))

     def test_already_sorted(self):
        input = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        output = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        self.assertEqual(output, algos.selection_sort(input))

     def test_negative_values(self):
        input = [-1, -9, -2, -7, -5, -3, -12, -24, -3]
        output = [-24, -12, -9, -7, -5, -3, -3, -2, -1]
        self.assertEqual(output, algos.selection_sort(input))


class TestInsertionSort(unittest.TestCase):
    def test_unordered_array(self):
        input = [5,17,59,1,53,102,3,53,21,116,53,22]
        output = [1, 3, 5, 17, 21, 22, 53, 53, 53, 59, 102, 116]
        self.assertEqual(output, algos.insertion_sort(input))
    
    def test_single_element(self):
        input = [65]
        output = [65]
        self.assertEqual(output, algos.insertion_sort(input))

    def test_empty_array(self):
        input = []
        output = []
        self.assertEqual(output, algos.insertion_sort(input))

    def test_already_sorted(self):
        input = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        output = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        self.assertEqual(output, algos.insertion_sort(input))

    def test_negative_values(self):
        input = [-1, -9, -2, -7, -5, -3, -12, -24, -3]
        output = [-24, -12, -9, -7, -5, -3, -3, -2, -1]
        self.assertEqual(output, algos.insertion_sort(input))

class TestQuickSort(unittest.TestCase):
    def test_unordered_array(self):
        input = [5,17,59,1,53,102,3,53,21,116,53,22]
        output = [1, 3, 5, 17, 21, 22, 53, 53, 53, 59, 102, 116]
        self.assertEqual(output, algos.quicksort(input))
    
    def test_single_element(self):
        input = [65]
        output = [65]
        self.assertEqual(output, algos.quicksort(input))

    def test_empty_array(self):
        input = []
        output = []
        self.assertEqual(output, algos.quicksort(input))

    def test_already_sorted(self):
        input = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        output = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        self.assertEqual(output, algos.quicksort(input))

    def test_negative_values(self):
        input = [-1, -9, -2, -7, -5, -3, -12, -24, -3]
        output = [-24, -12, -9, -7, -5, -3, -3, -2, -1]
        self.assertEqual(output, algos.quicksort(input))

class TestCountingSort(unittest.TestCase):
    def test_preliminary(self):
        input = [5,1,2,2,1,4,2,4,3,1,2,3]
        output = [1, 1, 1, 2, 2, 2, 2, 3, 3, 4, 4, 5]
        self.assertEqual(output, algos.counting_sort(input))

    def test_unordered_array(self):
        input = [5,17,59,1,53,102,3,53,21,116,53,22]
        output = [1, 3, 5, 17, 21, 22, 53, 53, 53, 59, 102, 116]
        self.assertEqual(output, algos.counting_sort(input))
    
    def test_single_element(self):
        input = [65]
        output = [65]
        self.assertEqual(output, algos.counting_sort(input))

    def test_empty_array(self):
        input = []
        output = []
        self.assertEqual(output, algos.counting_sort(input))

    def test_already_sorted(self):
        input = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        output = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        self.assertEqual(output, algos.counting_sort(input))

class TestMergeSort(unittest.TestCase):
    def test_unordered_array(self):
        input = [5,17,59,1,53,102,3,53,21,116,53,22]
        output = [1, 3, 5, 17, 21, 22, 53, 53, 53, 59, 102, 116]
        self.assertEqual(output, algos.merge_sort(input))
    
    def test_single_element(self):
        input = [65]
        output = [65]
        self.assertEqual(output, algos.merge_sort(input))

    def test_empty_array(self):
        input = []
        output = []
        self.assertEqual(output, algos.merge_sort(input))

    def test_already_sorted(self):
        input = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        output = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        self.assertEqual(output, algos.merge_sort(input))

    def test_negative_values(self):
        input = [-1, -9, -2, -7, -5, -3, -12, -24, -3]
        output = [-24, -12, -9, -7, -5, -3, -3, -2, -1]
        self.assertEqual(output, algos.merge_sort(input))


class TestLinearSearch(unittest.TestCase):
    def test_search_empty(self):
        input = []
        self.assertEqual(-1, algos.linear_search(input, 5))
    
    def test_search_first_element(self):
        input = [5,17,59,1,53,102,3,53,21,116,53,22]
        self.assertEqual(0, algos.linear_search(input, 5))
    
    def test_search_last_element(self):
        input = [5,17,59,1,53,102,3,53,21,116,53,22]
        self.assertEqual(len(input)-1, algos.linear_search(input, 22))

    def test_search_first_element_seen(self):
        input = [5,17,59,1,53,102,3,53,21,116,53,22]
        self.assertEqual(4, algos.linear_search(input, 53))
    
    def test_search_negative_values_first_element(self):
        input = [-1, -9, -2, -7, -5, -3, -12, -24, -3]
        self.assertEqual(0, algos.linear_search(input, -1))
    
    def test_search_negative_values_last_element(self):
        input = [-1, -9, -2, -7, -5, -3, -12, -24, -36]
        self.assertEqual(len(input)-1, algos.linear_search(input, -36))
    
    def test_search_negative_values_first_element_seen(self):
        input = [-1, -9, -2, -7, -5, -3, -12, -24, -3]
        self.assertEqual(5, algos.linear_search(input, -3))
    
    def test_search_mid_point(self):
        input = [5,17,59,1,53,102,3,53,21,116,53,22]
        self.assertEqual(6, algos.linear_search(input, 3))


class TestBinarySearch(unittest.TestCase):
    def test_search_empty(self):
        input = []
        self.assertEqual(-1, algos.binary_search(input, 5))
    
    def test_search_first_element(self):
        input = [1, 3, 5, 17, 21, 22, 53, 53, 53, 59, 102, 116]
        self.assertEqual(0, algos.binary_search(input, 1))
    
    def test_search_last_element(self):
        input = [1, 3, 5, 17, 21, 22, 53, 53, 53, 59, 102, 116]
        self.assertEqual(len(input)-1, algos.binary_search(input, 116))
    
    def test_search_negative_values_first_element(self):
        input = [-24, -12, -9, -7, -5, -3, -3, -2, -1]
        self.assertEqual(0, algos.binary_search(input, -24))
    
    def test_search_negative_values_last_element(self):
        input = [-24, -12, -9, -7, -5, -3, -3, -2, -1]
        self.assertEqual(len(input)-1, algos.binary_search(input, -1))
    
    def test_search_mid_point(self):
        input = [1, 3, 5, 17, 21, 22, 53, 53, 53, 59, 102, 116]
        self.assertEqual(5, algos.binary_search(input, 22))


if __name__ == '__main__':
    unittest.main()
