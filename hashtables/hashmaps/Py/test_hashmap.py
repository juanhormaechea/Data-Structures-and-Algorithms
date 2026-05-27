import unittest
from hashmap import HashMap


class TestHashMapInit(unittest.TestCase):
    """Tests for HashMap.__init__"""

    def test_valid_initialization_stores_size(self):
        hm = HashMap(8, 0.75)
        self.assertEqual(hm.size, 8)

    def test_valid_initialization_stores_max_load_factor(self):
        hm = HashMap(8, 0.75)
        self.assertEqual(hm.max_load_factor, 0.75)

    def test_valid_initialization_num_elements_is_zero(self):
        hm = HashMap(8, 0.75)
        self.assertEqual(hm.num_elements, 0)

    def test_valid_initialization_map_length_matches_size(self):
        hm = HashMap(8, 0.75)
        self.assertEqual(len(hm.map), 8)

    def test_valid_initialization_all_slots_are_none(self):
        hm = HashMap(8, 0.75)
        self.assertTrue(all(slot is None for slot in hm.map))

    def test_size_1_is_valid(self):
        hm = HashMap(1, 0.75)
        self.assertEqual(hm.size, 1)

    def test_powers_of_two_are_valid(self):
        for size in [2, 4, 8, 16, 32, 64]:
            with self.subTest(size=size):
                hm = HashMap(size, 0.75)
                self.assertEqual(hm.size, size)

    def test_raises_on_size_zero(self):
        with self.assertRaises(ValueError):
            HashMap(0, 0.75)

    def test_raises_on_negative_size(self):
        with self.assertRaises(ValueError):
            HashMap(-4, 0.75)

    def test_raises_on_non_power_of_two(self):
        for size in [3, 5, 6, 7, 9, 10]:
            with self.subTest(size=size):
                with self.assertRaises(ValueError):
                    HashMap(size, 0.75)


class TestHashMapAdd(unittest.TestCase):
    """Tests for HashMap.add"""

    def setUp(self):
        self.hm = HashMap(8, 0.75)

    def test_add_increments_num_elements(self):
        self.hm.add(1, 100)
        self.assertEqual(self.hm.num_elements, 1)

    def test_add_two_distinct_keys_increments_twice(self):
        self.hm.add(1, 10)
        self.hm.add(2, 20)
        self.assertEqual(self.hm.num_elements, 2)

    def test_add_duplicate_key_does_not_increment_num_elements(self):
        self.hm.add(1, 100)
        self.hm.add(1, 200)
        self.assertEqual(self.hm.num_elements, 1)

    def test_add_duplicate_key_updates_value(self):
        self.hm.add(1, 100)
        self.hm.add(1, 200)
        self.assertEqual(self.hm.get(1), 200)

    def test_add_key_zero(self):
        self.hm.add(0, 99)
        self.assertEqual(self.hm.num_elements, 1)

    def test_add_then_get_returns_correct_value(self):
        self.hm.add(5, 42)
        self.assertEqual(self.hm.get(5), 42)

    def test_add_multiple_distinct_keys_all_retrievable(self):
        pairs = [(1, 10), (2, 20), (4, 40), (8, 80)]
        for key, value in pairs:
            self.hm.add(key, value)
        for key, value in pairs:
            with self.subTest(key=key):
                self.assertEqual(self.hm.get(key), value)

    def test_add_returns_none(self):
        result = self.hm.add(1, 100)
        self.assertIsNone(result)


class TestHashMapGet(unittest.TestCase):
    """Tests for HashMap.get"""

    def setUp(self):
        self.hm = HashMap(8, 0.75)

    def test_get_returns_correct_value(self):
        self.hm.add(3, 42)
        self.assertEqual(self.hm.get(3), 42)

    def test_get_returns_none_for_missing_key(self):
        self.assertIsNone(self.hm.get(7))

    def test_get_on_empty_map_returns_none(self):
        self.assertIsNone(self.hm.get(0))

    def test_get_returns_updated_value_after_overwrite(self):
        self.hm.add(1, 100)
        self.hm.add(1, 999)
        self.assertEqual(self.hm.get(1), 999)

    def test_get_does_not_change_num_elements(self):
        self.hm.add(1, 42)
        self.hm.get(1)
        self.assertEqual(self.hm.num_elements, 1)

    def test_get_key_zero(self):
        self.hm.add(0, 55)
        self.assertEqual(self.hm.get(0), 55)

    def test_get_after_remove_returns_none(self):
        self.hm.add(1, 42)
        self.hm.remove(1)
        self.assertIsNone(self.hm.get(1))


class TestHashMapRemove(unittest.TestCase):
    """Tests for HashMap.remove"""

    def setUp(self):
        self.hm = HashMap(8, 0.75)

    def test_remove_existing_key_returns_true(self):
        self.hm.add(1, 42)
        self.assertTrue(self.hm.remove(1))

    def test_remove_missing_key_returns_false(self):
        self.assertFalse(self.hm.remove(1))

    def test_remove_on_empty_map_returns_false(self):
        self.assertFalse(self.hm.remove(0))

    def test_remove_decrements_num_elements(self):
        self.hm.add(1, 42)
        self.hm.remove(1)
        self.assertEqual(self.hm.num_elements, 0)

    def test_remove_makes_key_unretrievable(self):
        self.hm.add(1, 42)
        self.hm.remove(1)
        self.assertIsNone(self.hm.get(1))

    def test_remove_same_key_twice_returns_false_on_second(self):
        self.hm.add(1, 42)
        self.hm.remove(1)
        self.assertFalse(self.hm.remove(1))

    def test_remove_head_node_preserves_chained_node(self):
        """Removing the first node in a bucket leaves the rest of the chain intact."""
        self.hm.add(1, 10)
        self.hm.add(3, 20)
        self.hm.remove(1)
        self.assertIsNone(self.hm.get(1))
        self.assertEqual(self.hm.get(3), 20)

    def test_remove_chained_node_preserves_head(self):
        """Removing a non-head node leaves the head of the chain intact."""
        self.hm.add(1, 10)
        self.hm.add(3, 20)
        self.hm.remove(3)
        self.assertIsNone(self.hm.get(3))
        self.assertEqual(self.hm.get(1), 10)

    def test_remove_does_not_affect_other_keys(self):
        self.hm.add(1, 10)
        self.hm.add(2, 20)
        self.hm.remove(1)
        self.assertEqual(self.hm.get(2), 20)


class TestHashMapResize(unittest.TestCase):
    """Tests that resize is triggered correctly when the load factor is exceeded."""

    def test_resize_doubles_the_capacity(self):
        # size=2, max_load_factor=0.5 → resize triggers after 1 element (1/2 = 0.5, not > 0.5)
        # adding a second element pushes it to 2/2 = 1.0 > 0.5 → resize
        hm = HashMap(2, 0.5)
        hm.add(1, 10)
        hm.add(2, 20)
        self.assertEqual(hm.size, 4)

    def test_resize_preserves_all_elements(self):
        hm = HashMap(2, 0.5)
        pairs = [(1, 10), (2, 20), (4, 40)]
        for key, value in pairs:
            hm.add(key, value)
        for key, value in pairs:
            with self.subTest(key=key):
                self.assertEqual(hm.get(key), value)

    def test_resize_preserves_num_elements(self):
        hm = HashMap(2, 0.5)
        hm.add(1, 10)
        hm.add(2, 20)
        hm.add(4, 40)
        self.assertEqual(hm.num_elements, 3)


if __name__ == '__main__':
    unittest.main()