#include "../../../../Unity/src/unity.h"
#include "../src/hashset.h"
#include <stdbool.h>
#include <stdlib.h>

void setUp(void) {

};

void tearDown(void) {

};

/* -----------------------------------------------------------------------
 * hashset_create
 * ----------------------------------------------------------------------- */

void test_create_returns_non_null(void) {
  HashSet *set = hashset_create(8, 0.75);
  TEST_ASSERT_NOT_NULL(set);
  hashset_destroy(set);
};

void test_create_sets_correct_size(void) {
  HashSet *set = hashset_create(16, 0.75);
  TEST_ASSERT_EQUAL_INT(16, set->size);
  hashset_destroy(set);
};

void test_create_sets_num_elements_zero(void) {
  HashSet *set = hashset_create(8, 0.75);
  TEST_ASSERT_EQUAL_INT(0, set->num_elements);
  hashset_destroy(set);
};

void test_create_sets_max_load_factor(void) {
  HashSet *set = hashset_create(8, 0.6);
  TEST_ASSERT_EQUAL_INT(60, (int)(set->max_load_factor * 100));
  hashset_destroy(set);
};

void test_create_returns_null_on_non_power_of_two(void) {
  HashSet *set = hashset_create(7, 0.75);
  TEST_ASSERT_NULL(set);
};

void test_create_returns_null_on_zero_size(void) {
  HashSet *set = hashset_create(0, 0.75);
  TEST_ASSERT_NULL(set);
};

void test_create_returns_null_on_negative_size(void) {
  HashSet *set = hashset_create(-4, 0.75);
  TEST_ASSERT_NULL(set);
};

void test_create_internal_array_is_null_initialised(void) {
  HashSet *set = hashset_create(8, 0.75);
  TEST_ASSERT_NOT_NULL(set->set);
  for (int i = 0; i < set->size; i++) {
    TEST_ASSERT_NULL(set->set[i]);
  }
  hashset_destroy(set);
};

/* -----------------------------------------------------------------------
 * hashset_destroy
 * ----------------------------------------------------------------------- */

void test_destroy_null_set_does_not_crash(void) {
  /* Should return cleanly without segfault */
  hashset_destroy(NULL);
};

void test_destroy_empty_set(void) {
  HashSet *set = hashset_create(8, 0.75);
  /* Should not crash or leak */
  hashset_destroy(set);
};

void test_destroy_populated_set(void) {
  HashSet *set = hashset_create(8, 0.75);
  hashset_add(set, 1);
  hashset_add(set, 2);
  hashset_add(set, 3);
  /* Should free all nodes without crashing */
  hashset_destroy(set);
};

/* -----------------------------------------------------------------------
 * hashset_add
 * ----------------------------------------------------------------------- */

void test_add_returns_true_on_new_value(void) {
  HashSet *set = hashset_create(8, 0.75);
  bool result = hashset_add(set, 42);
  TEST_ASSERT_TRUE(result);
  hashset_destroy(set);
};

void test_add_returns_false_on_duplicate(void) {
  HashSet *set = hashset_create(8, 0.75);
  hashset_add(set, 42);
  bool result = hashset_add(set, 42);
  TEST_ASSERT_FALSE(result);
  hashset_destroy(set);
};

void test_add_returns_false_on_null_set(void) {
  bool result = hashset_add(NULL, 42);
  TEST_ASSERT_FALSE(result);
};

void test_add_increments_num_elements(void) {
  HashSet *set = hashset_create(8, 0.75);
  hashset_add(set, 1);
  TEST_ASSERT_EQUAL_INT(1, set->num_elements);
  hashset_add(set, 2);
  TEST_ASSERT_EQUAL_INT(2, set->num_elements);
  hashset_destroy(set);
};

void test_add_does_not_increment_on_duplicate(void) {
  HashSet *set = hashset_create(8, 0.75);
  hashset_add(set, 10);
  hashset_add(set, 10);
  TEST_ASSERT_EQUAL_INT(1, set->num_elements);
  hashset_destroy(set);
};

void test_add_multiple_unique_values(void) {
  HashSet *set = hashset_create(16, 0.75);
  int values[] = {1, 5, 9, 13, 17, 21};
  int n = 6;
  for (int i = 0; i < n; i++) {
    TEST_ASSERT_TRUE(hashset_add(set, values[i]));
  }
  TEST_ASSERT_EQUAL_INT(n, set->num_elements);
  hashset_destroy(set);
};

void test_add_zero(void) {
  HashSet *set = hashset_create(8, 0.75);
  bool result = hashset_add(set, 0);
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_TRUE(hashset_contains(set, 0));
  hashset_destroy(set);
};

void test_add_negative_value(void) {
  HashSet *set = hashset_create(8, 0.75);
  bool result = hashset_add(set, -7);
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_TRUE(hashset_contains(set, -7));
  hashset_destroy(set);
};

/* -----------------------------------------------------------------------
 * hashset_remove
 * ----------------------------------------------------------------------- */

void test_remove_returns_false_on_null_set(void) {
  bool result = hashset_remove(NULL, 5);
  TEST_ASSERT_FALSE(result);
};

void test_remove_returns_false_on_empty_set(void) {
  HashSet *set = hashset_create(8, 0.75);
  bool result = hashset_remove(set, 5);
  TEST_ASSERT_FALSE(result);
  hashset_destroy(set);
};

void test_remove_returns_false_on_missing_value(void) {
  HashSet *set = hashset_create(8, 0.75);
  hashset_add(set, 1);
  hashset_add(set, 2);
  bool result = hashset_remove(set, 99);
  TEST_ASSERT_FALSE(result);
  hashset_destroy(set);
};

void test_remove_returns_true_on_existing_value(void) {
  HashSet *set = hashset_create(8, 0.75);
  hashset_add(set, 42);
  bool result = hashset_remove(set, 42);
  TEST_ASSERT_TRUE(result);
  hashset_destroy(set);
};

void test_remove_decrements_num_elements(void) {
  HashSet *set = hashset_create(8, 0.75);
  hashset_add(set, 1);
  hashset_add(set, 2);
  hashset_remove(set, 1);
  TEST_ASSERT_EQUAL_INT(1, set->num_elements);
  hashset_destroy(set);
};

void test_remove_value_no_longer_present(void) {
  HashSet *set = hashset_create(8, 0.75);
  hashset_add(set, 7);
  hashset_remove(set, 7);
  TEST_ASSERT_FALSE(hashset_contains(set, 7));
  hashset_destroy(set);
};

void test_remove_only_element_empties_set(void) {
  HashSet *set = hashset_create(8, 0.75);
  hashset_add(set, 3);
  hashset_remove(set, 3);
  TEST_ASSERT_EQUAL_INT(0, set->num_elements);
  hashset_destroy(set);
};

void test_remove_does_not_affect_other_elements(void) {
  HashSet *set = hashset_create(8, 0.75);
  hashset_add(set, 10);
  hashset_add(set, 20);
  hashset_add(set, 30);
  hashset_remove(set, 20);
  TEST_ASSERT_TRUE(hashset_contains(set, 10));
  TEST_ASSERT_FALSE(hashset_contains(set, 20));
  TEST_ASSERT_TRUE(hashset_contains(set, 30));
  hashset_destroy(set);
};

void test_remove_negative_value(void) {
  HashSet *set = hashset_create(8, 0.75);
  hashset_add(set, -5);
  bool result = hashset_remove(set, -5);
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_FALSE(hashset_contains(set, -5));
  hashset_destroy(set);
};

/* -----------------------------------------------------------------------
 * hashset_contains
 * ----------------------------------------------------------------------- */

void test_contains_returns_false_on_null_set(void) {
  bool result = hashset_contains(NULL, 1);
  TEST_ASSERT_FALSE(result);
};

void test_contains_returns_false_on_empty_set(void) {
  HashSet *set = hashset_create(8, 0.75);
  bool result = hashset_contains(set, 1);
  TEST_ASSERT_FALSE(result);
  hashset_destroy(set);
};

void test_contains_returns_true_for_added_value(void) {
  HashSet *set = hashset_create(8, 0.75);
  hashset_add(set, 55);
  bool result = hashset_contains(set, 55);
  TEST_ASSERT_TRUE(result);
  hashset_destroy(set);
};

void test_contains_returns_false_for_missing_value(void) {
  HashSet *set = hashset_create(8, 0.75);
  hashset_add(set, 55);
  bool result = hashset_contains(set, 56);
  TEST_ASSERT_FALSE(result);
  hashset_destroy(set);
};

void test_contains_zero(void) {
  HashSet *set = hashset_create(8, 0.75);
  hashset_add(set, 0);
  TEST_ASSERT_TRUE(hashset_contains(set, 0));
  hashset_destroy(set);
};

void test_contains_negative_value(void) {
  HashSet *set = hashset_create(8, 0.75);
  hashset_add(set, -99);
  TEST_ASSERT_TRUE(hashset_contains(set, -99));
  TEST_ASSERT_FALSE(hashset_contains(set, 99));
  hashset_destroy(set);
};

void test_contains_multiple_values(void) {
  HashSet *set = hashset_create(16, 0.75);
  int values[] = {3, 7, 11, 15, 19};
  for (int i = 0; i < 5; i++) {
    hashset_add(set, values[i]);
  }
  for (int i = 0; i < 5; i++) {
    TEST_ASSERT_TRUE(hashset_contains(set, values[i]));
  }
  TEST_ASSERT_FALSE(hashset_contains(set, 100));
  hashset_destroy(set);
};

/* -----------------------------------------------------------------------
 * hashset_resize
 * ----------------------------------------------------------------------- */

void test_resize_doubles_the_size(void) {
  HashSet *set = hashset_create(8, 0.75);
  /* Add enough elements to avoid auto-resize (keep load factor low) */
  hashset_add(set, 1);
  hashset_add(set, 2);
  int old_size = set->size; /* should still be 8 */
  hashset_resize(set);
  TEST_ASSERT_EQUAL_INT(old_size * 2, set->size);
  hashset_destroy(set);
};

void test_resize_preserves_all_elements(void) {
  HashSet *set = hashset_create(8, 0.75);
  int values[] = {1, 2, 3, 4, 5};
  for (int i = 0; i < 5; i++) {
    hashset_add(set, values[i]);
  }
  hashset_resize(set);
  for (int i = 0; i < 5; i++) {
    TEST_ASSERT_TRUE(hashset_contains(set, values[i]));
  }
  hashset_destroy(set);
};

void test_resize_preserves_num_elements(void) {
  HashSet *set = hashset_create(8, 0.75);
  hashset_add(set, 10);
  hashset_add(set, 20);
  hashset_add(set, 30);
  int before = set->num_elements;
  hashset_resize(set);
  TEST_ASSERT_EQUAL_INT(before, set->num_elements);
  hashset_destroy(set);
};

void test_resize_triggered_automatically_on_high_load(void) {
  /* With size=8 and load factor 0.75, adding 7 elements (> 0.75*8=6)
     must trigger at least one automatic resize. */
  HashSet *set = hashset_create(8, 0.75);
  for (int i = 1; i <= 7; i++) {
    hashset_add(set, i);
  }
  TEST_ASSERT_TRUE(set->size > 8);
  /* All values still reachable after resize */
  for (int i = 1; i <= 7; i++) {
    TEST_ASSERT_TRUE(hashset_contains(set, i));
  }
  hashset_destroy(set);
};

/* -----------------------------------------------------------------------
 * knuth_hash
 * ----------------------------------------------------------------------- */

void test_knuth_hash_zero(void) {
  uint32_t result = knuth_hash(0);
  TEST_ASSERT_EQUAL_UINT32(0u, result);
};

void test_knuth_hash_one(void) {
  uint32_t result = knuth_hash(1);
  TEST_ASSERT_EQUAL_UINT32(2654435761u, result);
};

void test_knuth_hash_is_deterministic(void) {
  uint32_t a = knuth_hash(42);
  uint32_t b = knuth_hash(42);
  TEST_ASSERT_EQUAL_UINT32(a, b);
};

void test_knuth_hash_different_values_produce_different_hashes(void) {
  uint32_t h1 = knuth_hash(1);
  uint32_t h2 = knuth_hash(2);
  TEST_ASSERT_NOT_EQUAL(h1, h2);
};

void test_knuth_hash_uses_correct_multiplier(void) {
  /* Knuth multiplicative hash: value * 2654435761 (mod 2^32) */
  uint32_t expected = (uint32_t)(7 * 2654435761u);
  TEST_ASSERT_EQUAL_UINT32(expected, knuth_hash(7));
};

/* -----------------------------------------------------------------------
 * Integration / cross-function tests
 * ----------------------------------------------------------------------- */

void test_add_then_remove_then_re_add(void) {
  HashSet *set = hashset_create(8, 0.75);
  hashset_add(set, 100);
  hashset_remove(set, 100);
  bool result = hashset_add(set, 100);
  TEST_ASSERT_TRUE(result);
  TEST_ASSERT_TRUE(hashset_contains(set, 100));
  TEST_ASSERT_EQUAL_INT(1, set->num_elements);
  hashset_destroy(set);
};

void test_set_handles_many_elements(void) {
  HashSet *set = hashset_create(8, 0.75);
  int n = 50;
  for (int i = 0; i < n; i++) {
    hashset_add(set, i);
  }
  TEST_ASSERT_EQUAL_INT(n, set->num_elements);
  for (int i = 0; i < n; i++) {
    TEST_ASSERT_TRUE(hashset_contains(set, i));
  }
  hashset_destroy(set);
};

void test_no_duplicate_after_multiple_adds(void) {
  HashSet *set = hashset_create(8, 0.75);
  for (int i = 0; i < 10; i++) {
    hashset_add(set, 42); /* repeated adds of the same value */
  }
  TEST_ASSERT_EQUAL_INT(1, set->num_elements);
  hashset_destroy(set);
};

void test_add_remove_all_then_empty(void) {
  HashSet *set = hashset_create(8, 0.75);
  int values[] = {4, 8, 15, 16, 23, 42};
  int n = 6;
  for (int i = 0; i < n; i++) {
    hashset_add(set, values[i]);
  }
  for (int i = 0; i < n; i++) {
    hashset_remove(set, values[i]);
  }
  TEST_ASSERT_EQUAL_INT(0, set->num_elements);
  for (int i = 0; i < n; i++) {
    TEST_ASSERT_FALSE(hashset_contains(set, values[i]));
  }
  hashset_destroy(set);
};

/* -----------------------------------------------------------------------
 * main
 * ----------------------------------------------------------------------- */

int main(void) {
  UNITY_BEGIN();

  /* hashset_create */
  RUN_TEST(test_create_returns_non_null);
  RUN_TEST(test_create_sets_correct_size);
  RUN_TEST(test_create_sets_num_elements_zero);
  RUN_TEST(test_create_sets_max_load_factor);
  RUN_TEST(test_create_returns_null_on_non_power_of_two);
  RUN_TEST(test_create_returns_null_on_zero_size);
  RUN_TEST(test_create_returns_null_on_negative_size);
  RUN_TEST(test_create_internal_array_is_null_initialised);

  /* hashset_destroy */
  RUN_TEST(test_destroy_null_set_does_not_crash);
  RUN_TEST(test_destroy_empty_set);
  RUN_TEST(test_destroy_populated_set);

  /* hashset_add */
  RUN_TEST(test_add_returns_true_on_new_value);
  RUN_TEST(test_add_returns_false_on_duplicate);
  RUN_TEST(test_add_returns_false_on_null_set);
  RUN_TEST(test_add_increments_num_elements);
  RUN_TEST(test_add_does_not_increment_on_duplicate);
  RUN_TEST(test_add_multiple_unique_values);
  RUN_TEST(test_add_zero);
  RUN_TEST(test_add_negative_value);

  /* hashset_remove */
  RUN_TEST(test_remove_returns_false_on_null_set);
  RUN_TEST(test_remove_returns_false_on_empty_set);
  RUN_TEST(test_remove_returns_false_on_missing_value);
  RUN_TEST(test_remove_returns_true_on_existing_value);
  RUN_TEST(test_remove_decrements_num_elements);
  RUN_TEST(test_remove_value_no_longer_present);
  RUN_TEST(test_remove_only_element_empties_set);
  RUN_TEST(test_remove_does_not_affect_other_elements);
  RUN_TEST(test_remove_negative_value);

  /* hashset_contains */
  RUN_TEST(test_contains_returns_false_on_null_set);
  RUN_TEST(test_contains_returns_false_on_empty_set);
  RUN_TEST(test_contains_returns_true_for_added_value);
  RUN_TEST(test_contains_returns_false_for_missing_value);
  RUN_TEST(test_contains_zero);
  RUN_TEST(test_contains_negative_value);
  RUN_TEST(test_contains_multiple_values);

  /* hashset_resize */
  RUN_TEST(test_resize_doubles_the_size);
  RUN_TEST(test_resize_preserves_all_elements);
  RUN_TEST(test_resize_preserves_num_elements);
  RUN_TEST(test_resize_triggered_automatically_on_high_load);

  /* knuth_hash */
  RUN_TEST(test_knuth_hash_zero);
  RUN_TEST(test_knuth_hash_one);
  RUN_TEST(test_knuth_hash_is_deterministic);
  RUN_TEST(test_knuth_hash_different_values_produce_different_hashes);
  RUN_TEST(test_knuth_hash_uses_correct_multiplier);

  /* Integration */
  RUN_TEST(test_add_then_remove_then_re_add);
  RUN_TEST(test_set_handles_many_elements);
  RUN_TEST(test_no_duplicate_after_multiple_adds);
  RUN_TEST(test_add_remove_all_then_empty);

  return UNITY_END();
};