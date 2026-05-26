import unittest
from hashset import HashSet


class TestHashSetInit(unittest.TestCase):

    def test_init_sets_correct_size(self):
        s = HashSet(8, 0.75)
        self.assertEqual(s.size, 8)

    def test_init_sets_num_elements_zero(self):
        s = HashSet(8, 0.75)
        self.assertEqual(s.num_elements, 0)

    def test_init_sets_max_load_factor(self):
        s = HashSet(8, 0.6)
        self.assertAlmostEqual(s.max_load_factor, 0.6)

    def test_init_internal_list_is_none_filled(self):
        s = HashSet(8, 0.75)
        self.assertEqual(len(s.set), 8)
        for slot in s.set:
            self.assertIsNone(slot)

    def test_init_raises_on_zero_size(self):
        with self.assertRaises(ValueError):
            HashSet(0, 0.75)

    def test_init_raises_on_negative_size(self):
        with self.assertRaises(ValueError):
            HashSet(-4, 0.75)

    def test_init_raises_on_non_power_of_two(self):
        with self.assertRaises(ValueError):
            HashSet(7, 0.75)

    def test_init_accepts_power_of_two(self):
        for size in (1, 2, 4, 8, 16, 32, 64):
            s = HashSet(size, 0.75)
            self.assertEqual(s.size, size)


class TestHashSetAdd(unittest.TestCase):

    def setUp(self):
        self.s = HashSet(8, 0.75)

    def test_add_returns_true_on_new_value(self):
        self.assertTrue(self.s.add(42))

    def test_add_returns_false_on_duplicate(self):
        self.s.add(42)
        self.assertFalse(self.s.add(42))

    def test_add_increments_num_elements(self):
        self.s.add(1)
        self.assertEqual(self.s.num_elements, 1)
        self.s.add(2)
        self.assertEqual(self.s.num_elements, 2)

    def test_add_does_not_increment_on_duplicate(self):
        self.s.add(10)
        self.s.add(10)
        self.assertEqual(self.s.num_elements, 1)

    def test_add_zero(self):
        self.assertTrue(self.s.add(0))
        self.assertTrue(self.s.contains(0))

    def test_add_negative_value(self):
        self.assertTrue(self.s.add(-7))
        self.assertTrue(self.s.contains(-7))

    def test_add_multiple_unique_values(self):
        values = [1, 5, 9, 13, 17, 21]
        for v in values:
            self.assertTrue(self.s.add(v))
        self.assertEqual(self.s.num_elements, len(values))

    def test_add_no_duplicate_after_many_attempts(self):
        for _ in range(10):
            self.s.add(42)
        self.assertEqual(self.s.num_elements, 1)


class TestHashSetContains(unittest.TestCase):

    def setUp(self):
        self.s = HashSet(8, 0.75)

    def test_contains_returns_false_on_empty_set(self):
        self.assertFalse(self.s.contains(1))

    def test_contains_returns_true_for_added_value(self):
        self.s.add(55)
        self.assertTrue(self.s.contains(55))

    def test_contains_returns_false_for_missing_value(self):
        self.s.add(55)
        self.assertFalse(self.s.contains(56))

    def test_contains_zero(self):
        self.s.add(0)
        self.assertTrue(self.s.contains(0))

    def test_contains_negative_value(self):
        self.s.add(-99)
        self.assertTrue(self.s.contains(-99))
        self.assertFalse(self.s.contains(99))

    def test_contains_multiple_values(self):
        values = [3, 7, 11, 15, 19]
        for v in values:
            self.s.add(v)
        for v in values:
            self.assertTrue(self.s.contains(v))
        self.assertFalse(self.s.contains(100))


class TestHashSetRemove(unittest.TestCase):

    def setUp(self):
        self.s = HashSet(8, 0.75)

    def test_remove_returns_false_on_empty_set(self):
        self.assertFalse(self.s.remove(5))

    def test_remove_returns_false_on_missing_value(self):
        self.s.add(1)
        self.s.add(2)
        self.assertFalse(self.s.remove(99))

    def test_remove_returns_true_on_existing_value(self):
        self.s.add(42)
        self.assertTrue(self.s.remove(42))

    def test_remove_decrements_num_elements(self):
        self.s.add(1)
        self.s.add(2)
        self.s.remove(1)
        self.assertEqual(self.s.num_elements, 1)

    def test_remove_value_no_longer_present(self):
        self.s.add(7)
        self.s.remove(7)
        self.assertFalse(self.s.contains(7))

    def test_remove_only_element_empties_set(self):
        self.s.add(3)
        self.s.remove(3)
        self.assertEqual(self.s.num_elements, 0)

    def test_remove_does_not_affect_other_elements(self):
        self.s.add(10)
        self.s.add(20)
        self.s.add(30)
        self.s.remove(20)
        self.assertTrue(self.s.contains(10))
        self.assertFalse(self.s.contains(20))
        self.assertTrue(self.s.contains(30))

    def test_remove_negative_value(self):
        self.s.add(-5)
        self.assertTrue(self.s.remove(-5))
        self.assertFalse(self.s.contains(-5))


class TestHashSetResize(unittest.TestCase):

    def test_resize_triggered_automatically_on_high_load(self):
        # size=8, load threshold=0.75 → resize after 7th element (7/8 > 0.75)
        s = HashSet(8, 0.75)
        for i in range(1, 8):
            s.add(i)
        self.assertGreater(s.size, 8)

    def test_all_elements_present_after_resize(self):
        s = HashSet(8, 0.75)
        values = list(range(1, 8))
        for v in values:
            s.add(v)
        for v in values:
            self.assertTrue(s.contains(v))

    def test_num_elements_preserved_after_resize(self):
        s = HashSet(8, 0.75)
        for i in range(1, 8):
            s.add(i)
        self.assertEqual(s.num_elements, 7)

    def test_size_doubles_after_resize(self):
        s = HashSet(8, 0.75)
        # Add exactly 2 elements — well below threshold — then resize manually
        s.add(1)
        s.add(2)
        old_size = s.size  # still 8
        s._HashSet__resize()
        self.assertEqual(s.size, old_size * 2)

    def test_elements_accessible_after_manual_resize(self):
        s = HashSet(8, 0.75)
        s.add(10)
        s.add(20)
        s._HashSet__resize()
        self.assertTrue(s.contains(10))
        self.assertTrue(s.contains(20))


class TestHashSetIntegration(unittest.TestCase):

    def test_add_remove_re_add(self):
        s = HashSet(8, 0.75)
        s.add(100)
        s.remove(100)
        self.assertTrue(s.add(100))
        self.assertTrue(s.contains(100))
        self.assertEqual(s.num_elements, 1)

    def test_handles_many_elements(self):
        s = HashSet(8, 0.75)
        n = 50
        for i in range(n):
            s.add(i)
        self.assertEqual(s.num_elements, n)
        for i in range(n):
            self.assertTrue(s.contains(i))

    def test_add_remove_all_leaves_set_empty(self):
        s = HashSet(8, 0.75)
        values = [4, 8, 15, 16, 23, 42]
        for v in values:
            s.add(v)
        for v in values:
            s.remove(v)
        self.assertEqual(s.num_elements, 0)
        for v in values:
            self.assertFalse(s.contains(v))

    def test_remove_then_contains_is_consistent(self):
        s = HashSet(16, 0.75)
        for i in range(10):
            s.add(i)
        for i in range(0, 10, 2):   # remove evens
            s.remove(i)
        for i in range(10):
            if i % 2 == 0:
                self.assertFalse(s.contains(i))
            else:
                self.assertTrue(s.contains(i))


if __name__ == "__main__":
    unittest.main()