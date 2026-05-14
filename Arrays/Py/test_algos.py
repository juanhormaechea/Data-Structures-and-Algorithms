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



if __name__ == '__main__':
    unittest.main()
