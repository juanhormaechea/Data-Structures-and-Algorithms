#include "../../../../Unity/src/unity.h"
#include "../src/hashmap.h"
#include <stdbool.h>
#include <stdlib.h>

void setUp(void) {

};

void tearDown(void) {

};

/* -----------------------------------------------------------------------
 * Collision helpers
 *
 * For a size-8 map (p = 3), bucket = knuth_hash(key) >> 29.
 *   knuth_hash(0) = 0          → bucket 0
 *   knuth_hash(5) = 387276917  → bucket 0   (forced collision)
 *
 * Use COLLISION_KEY_A = 0 and COLLISION_KEY_B = 5 wherever a chain of
 * length >= 2 is needed in the same bucket.
 * ----------------------------------------------------------------------- */
#define COLLISION_KEY_A 0
#define COLLISION_KEY_B 5

/* -----------------------------------------------------------------------
 * hashmap_create
 * ----------------------------------------------------------------------- */

void test_create_returns_non_null(void) {
  HashMap *map = hashmap_create(8, 0.75);
  TEST_ASSERT_NOT_NULL(map);
  hashmap_destroy(map);
};

void test_create_sets_correct_size(void) {
  HashMap *map = hashmap_create(16, 0.75);
  TEST_ASSERT_EQUAL_INT(16, map->size);
  hashmap_destroy(map);
};

void test_create_sets_num_elements_zero(void) {
  HashMap *map = hashmap_create(8, 0.75);
  TEST_ASSERT_EQUAL_INT(0, map->num_elements);
  hashmap_destroy(map);
};

void test_create_sets_max_load_factor(void) {
  HashMap *map = hashmap_create(8, 0.6);
  TEST_ASSERT_EQUAL_INT(60, (int)(map->max_load_factor * 100));
  hashmap_destroy(map);
};

void test_create_internal_array_is_null_initialised(void) {
  HashMap *map = hashmap_create(8, 0.75);
  TEST_ASSERT_NOT_NULL(map->map);
  for (int i = 0; i < map->size; i++) {
    TEST_ASSERT_NULL(map->map[i]);
  }
  hashmap_destroy(map);
};

void test_create_returns_null_on_non_power_of_two(void) {
  HashMap *map = hashmap_create(7, 0.75);
  TEST_ASSERT_NULL(map);
};

void test_create_returns_null_on_zero_size(void) {
  HashMap *map = hashmap_create(0, 0.75);
  TEST_ASSERT_NULL(map);
};

void test_create_returns_null_on_negative_size(void) {
  HashMap *map = hashmap_create(-4, 0.75);
  TEST_ASSERT_NULL(map);
};

/* -----------------------------------------------------------------------
 * hashmap_destroy
 * ----------------------------------------------------------------------- */

void test_destroy_null_map_does_not_crash(void) {
  hashmap_destroy(NULL);
};

void test_destroy_empty_map(void) {
  HashMap *map = hashmap_create(8, 0.75);
  hashmap_destroy(map);
};

void test_destroy_populated_map(void) {
  HashMap *map = hashmap_create(8, 0.75);
  hashmap_add(map, 1, 10);
  hashmap_add(map, 2, 20);
  hashmap_add(map, 3, 30);
  hashmap_destroy(map);
};

/* -----------------------------------------------------------------------
 * hashmap_add
 * ----------------------------------------------------------------------- */

void test_add_returns_true_on_new_key(void) {
  HashMap *map = hashmap_create(8, 0.75);
  bool result = hashmap_add(map, 1, 100);
  TEST_ASSERT_TRUE(result);
  hashmap_destroy(map);
};

void test_add_returns_true_on_existing_key_upsert(void) {
  HashMap *map = hashmap_create(8, 0.75);
  hashmap_add(map, 1, 100);
  bool result = hashmap_add(map, 1, 200);
  TEST_ASSERT_TRUE(result);
  hashmap_destroy(map);
};

void test_add_returns_false_on_null_map(void) {
  bool result = hashmap_add(NULL, 1, 100);
  TEST_ASSERT_FALSE(result);
};

void test_add_increments_num_elements_for_new_key(void) {
  HashMap *map = hashmap_create(8, 0.75);
  hashmap_add(map, 1, 10);
  TEST_ASSERT_EQUAL_INT(1, map->num_elements);
  hashmap_add(map, 2, 20);
  TEST_ASSERT_EQUAL_INT(2, map->num_elements);
  hashmap_destroy(map);
};

void test_add_does_not_increment_num_elements_on_upsert(void) {
  HashMap *map = hashmap_create(8, 0.75);
  hashmap_add(map, 42, 1);
  hashmap_add(map, 42, 2);
  TEST_ASSERT_EQUAL_INT(1, map->num_elements);
  hashmap_destroy(map);
};

void test_add_upsert_updates_value(void) {
  HashMap *map = hashmap_create(8, 0.75);
  int out = 0;
  hashmap_add(map, 7, 100);
  hashmap_add(map, 7, 999);
  hashmap_get(map, 7, &out);
  TEST_ASSERT_EQUAL_INT(999, out);
  hashmap_destroy(map);
};

void test_add_zero_as_key(void) {
  HashMap *map = hashmap_create(8, 0.75);
  int out = 0;
  TEST_ASSERT_TRUE(hashmap_add(map, 0, 55));
  TEST_ASSERT_TRUE(hashmap_get(map, 0, &out));
  TEST_ASSERT_EQUAL_INT(55, out);
  hashmap_destroy(map);
};

void test_add_negative_key(void) {
  HashMap *map = hashmap_create(8, 0.75);
  int out = 0;
  TEST_ASSERT_TRUE(hashmap_add(map, -3, 77));
  TEST_ASSERT_TRUE(hashmap_get(map, -3, &out));
  TEST_ASSERT_EQUAL_INT(77, out);
  hashmap_destroy(map);
};

void test_add_multiple_unique_keys(void) {
  HashMap *map = hashmap_create(16, 0.75);
  int keys[]   = {1, 2, 3, 4, 5};
  int values[] = {10, 20, 30, 40, 50};
  int n = 5;
  for (int i = 0; i < n; i++) {
    TEST_ASSERT_TRUE(hashmap_add(map, keys[i], values[i]));
  }
  TEST_ASSERT_EQUAL_INT(n, map->num_elements);
  hashmap_destroy(map);
};

void test_add_collision_both_keys_retrievable(void) {
  /* COLLISION_KEY_A and COLLISION_KEY_B both hash to bucket 0 in size-8 map */
  HashMap *map = hashmap_create(8, 0.75);
  int out = 0;
  hashmap_add(map, COLLISION_KEY_A, 111);
  hashmap_add(map, COLLISION_KEY_B, 222);
  TEST_ASSERT_EQUAL_INT(2, map->num_elements);
  TEST_ASSERT_TRUE(hashmap_get(map, COLLISION_KEY_A, &out));
  TEST_ASSERT_EQUAL_INT(111, out);
  TEST_ASSERT_TRUE(hashmap_get(map, COLLISION_KEY_B, &out));
  TEST_ASSERT_EQUAL_INT(222, out);
  hashmap_destroy(map);
};

void test_add_upsert_on_collision_chain_updates_correct_node(void) {
  HashMap *map = hashmap_create(8, 0.75);
  int out = 0;
  hashmap_add(map, COLLISION_KEY_A, 1);
  hashmap_add(map, COLLISION_KEY_B, 2);
  /* Update the second node in the chain */
  hashmap_add(map, COLLISION_KEY_B, 99);
  TEST_ASSERT_EQUAL_INT(2, map->num_elements); /* no new node */
  hashmap_get(map, COLLISION_KEY_A, &out);
  TEST_ASSERT_EQUAL_INT(1, out); /* first node untouched */
  hashmap_get(map, COLLISION_KEY_B, &out);
  TEST_ASSERT_EQUAL_INT(99, out); /* second node updated */
  hashmap_destroy(map);
};

/* -----------------------------------------------------------------------
 * hashmap_get
 * ----------------------------------------------------------------------- */

void test_get_returns_false_on_null_map(void) {
  int out = 0;
  TEST_ASSERT_FALSE(hashmap_get(NULL, 1, &out));
};

void test_get_returns_false_on_empty_map(void) {
  HashMap *map = hashmap_create(8, 0.75);
  int out = 0;
  TEST_ASSERT_FALSE(hashmap_get(map, 1, &out));
  hashmap_destroy(map);
};

void test_get_returns_false_for_missing_key(void) {
  HashMap *map = hashmap_create(8, 0.75);
  int out = 0;
  hashmap_add(map, 1, 10);
  TEST_ASSERT_FALSE(hashmap_get(map, 99, &out));
  hashmap_destroy(map);
};

void test_get_returns_true_and_correct_value(void) {
  HashMap *map = hashmap_create(8, 0.75);
  int out = 0;
  hashmap_add(map, 3, 42);
  TEST_ASSERT_TRUE(hashmap_get(map, 3, &out));
  TEST_ASSERT_EQUAL_INT(42, out);
  hashmap_destroy(map);
};

void test_get_returns_correct_value_after_upsert(void) {
  HashMap *map = hashmap_create(8, 0.75);
  int out = 0;
  hashmap_add(map, 3, 42);
  hashmap_add(map, 3, 100);
  hashmap_get(map, 3, &out);
  TEST_ASSERT_EQUAL_INT(100, out);
  hashmap_destroy(map);
};

void test_get_collision_retrieves_correct_values(void) {
  /* Both keys in the same bucket — exercises chain traversal */
  HashMap *map = hashmap_create(8, 0.75);
  int out = 0;
  hashmap_add(map, COLLISION_KEY_A, 10);
  hashmap_add(map, COLLISION_KEY_B, 20);
  TEST_ASSERT_TRUE(hashmap_get(map, COLLISION_KEY_B, &out));
  TEST_ASSERT_EQUAL_INT(20, out);
  TEST_ASSERT_TRUE(hashmap_get(map, COLLISION_KEY_A, &out));
  TEST_ASSERT_EQUAL_INT(10, out);
  hashmap_destroy(map);
};

void test_get_does_not_modify_map(void) {
  HashMap *map = hashmap_create(8, 0.75);
  int out = 0;
  hashmap_add(map, 5, 55);
  hashmap_get(map, 5, &out);
  TEST_ASSERT_EQUAL_INT(1, map->num_elements);
  TEST_ASSERT_TRUE(hashmap_get(map, 5, &out));
  hashmap_destroy(map);
};

/* -----------------------------------------------------------------------
 * hashmap_remove
 * ----------------------------------------------------------------------- */

void test_remove_returns_false_on_null_map(void) {
  TEST_ASSERT_FALSE(hashmap_remove(NULL, 1));
};

void test_remove_returns_false_on_empty_map(void) {
  HashMap *map = hashmap_create(8, 0.75);
  TEST_ASSERT_FALSE(hashmap_remove(map, 1));
  hashmap_destroy(map);
};

void test_remove_returns_false_for_missing_key(void) {
  HashMap *map = hashmap_create(8, 0.75);
  hashmap_add(map, 1, 10);
  TEST_ASSERT_FALSE(hashmap_remove(map, 99));
  hashmap_destroy(map);
};

void test_remove_returns_true_for_existing_key(void) {
  HashMap *map = hashmap_create(8, 0.75);
  hashmap_add(map, 1, 10);
  TEST_ASSERT_TRUE(hashmap_remove(map, 1));
  hashmap_destroy(map);
};

void test_remove_decrements_num_elements(void) {
  HashMap *map = hashmap_create(8, 0.75);
  hashmap_add(map, 1, 10);
  hashmap_add(map, 2, 20);
  hashmap_remove(map, 1);
  TEST_ASSERT_EQUAL_INT(1, map->num_elements);
  hashmap_destroy(map);
};

void test_remove_key_no_longer_retrievable(void) {
  HashMap *map = hashmap_create(8, 0.75);
  int out = 0;
  hashmap_add(map, 7, 70);
  hashmap_remove(map, 7);
  TEST_ASSERT_FALSE(hashmap_get(map, 7, &out));
  hashmap_destroy(map);
};

void test_remove_only_entry_empties_map(void) {
  HashMap *map = hashmap_create(8, 0.75);
  hashmap_add(map, 3, 33);
  hashmap_remove(map, 3);
  TEST_ASSERT_EQUAL_INT(0, map->num_elements);
  hashmap_destroy(map);
};

void test_remove_does_not_affect_other_keys(void) {
  HashMap *map = hashmap_create(16, 0.75);
  hashmap_add(map, 10, 100);
  hashmap_add(map, 20, 200);
  hashmap_add(map, 30, 300);
  hashmap_remove(map, 20);
  int out = 0;
  TEST_ASSERT_TRUE(hashmap_get(map, 10, &out));
  TEST_ASSERT_EQUAL_INT(100, out);
  TEST_ASSERT_FALSE(hashmap_get(map, 20, &out));
  TEST_ASSERT_TRUE(hashmap_get(map, 30, &out));
  TEST_ASSERT_EQUAL_INT(300, out);
  hashmap_destroy(map);
};

void test_remove_negative_key(void) {
  HashMap *map = hashmap_create(8, 0.75);
  int out = 0;
  hashmap_add(map, -5, 50);
  TEST_ASSERT_TRUE(hashmap_remove(map, -5));
  TEST_ASSERT_FALSE(hashmap_get(map, -5, &out));
  hashmap_destroy(map);
};

void test_remove_head_of_collision_chain_leaves_tail_accessible(void) {
  /* Remove the chain-head (COLLISION_KEY_A) — tail (COLLISION_KEY_B) must survive */
  HashMap *map = hashmap_create(8, 0.75);
  int out = 0;
  hashmap_add(map, COLLISION_KEY_A, 111);
  hashmap_add(map, COLLISION_KEY_B, 222);
  TEST_ASSERT_TRUE(hashmap_remove(map, COLLISION_KEY_A));
  TEST_ASSERT_FALSE(hashmap_get(map, COLLISION_KEY_A, &out));
  TEST_ASSERT_TRUE(hashmap_get(map, COLLISION_KEY_B, &out));
  TEST_ASSERT_EQUAL_INT(222, out);
  TEST_ASSERT_EQUAL_INT(1, map->num_elements);
  hashmap_destroy(map);
};

void test_remove_tail_of_collision_chain_leaves_head_accessible(void) {
  /* Remove the chain-tail (COLLISION_KEY_B) — head (COLLISION_KEY_A) must survive */
  HashMap *map = hashmap_create(8, 0.75);
  int out = 0;
  hashmap_add(map, COLLISION_KEY_A, 111);
  hashmap_add(map, COLLISION_KEY_B, 222);
  TEST_ASSERT_TRUE(hashmap_remove(map, COLLISION_KEY_B));
  TEST_ASSERT_FALSE(hashmap_get(map, COLLISION_KEY_B, &out));
  TEST_ASSERT_TRUE(hashmap_get(map, COLLISION_KEY_A, &out));
  TEST_ASSERT_EQUAL_INT(111, out);
  TEST_ASSERT_EQUAL_INT(1, map->num_elements);
  hashmap_destroy(map);
};

/* -----------------------------------------------------------------------
 * hashmap_resize
 * ----------------------------------------------------------------------- */

void test_resize_null_map_does_not_crash(void) {
  hashmap_resize(NULL);
};

void test_resize_doubles_size(void) {
  HashMap *map = hashmap_create(8, 0.75);
  hashmap_add(map, 1, 10);
  hashmap_add(map, 2, 20);
  int old_size = map->size;
  hashmap_resize(map);
  TEST_ASSERT_EQUAL_INT(old_size * 2, map->size);
  hashmap_destroy(map);
};

void test_resize_preserves_all_entries(void) {
  HashMap *map = hashmap_create(8, 0.75);
  int keys[]   = {1, 2, 3, 4, 5};
  int values[] = {10, 20, 30, 40, 50};
  int n = 5;
  for (int i = 0; i < n; i++) {
    hashmap_add(map, keys[i], values[i]);
  }
  hashmap_resize(map);
  int out = 0;
  for (int i = 0; i < n; i++) {
    TEST_ASSERT_TRUE(hashmap_get(map, keys[i], &out));
    TEST_ASSERT_EQUAL_INT(values[i], out);
  }
  hashmap_destroy(map);
};

void test_resize_preserves_num_elements(void) {
  HashMap *map = hashmap_create(8, 0.75);
  hashmap_add(map, 1, 10);
  hashmap_add(map, 2, 20);
  hashmap_add(map, 3, 30);
  int before = map->num_elements;
  hashmap_resize(map);
  TEST_ASSERT_EQUAL_INT(before, map->num_elements);
  hashmap_destroy(map);
};

/* -----------------------------------------------------------------------
 * knuth_hash
 * ----------------------------------------------------------------------- */

void test_knuth_hash_zero(void) {
  TEST_ASSERT_EQUAL_UINT32(0u, knuth_hash(0));
};

void test_knuth_hash_one(void) {
  TEST_ASSERT_EQUAL_UINT32(2654435761u, knuth_hash(1));
};

void test_knuth_hash_is_deterministic(void) {
  TEST_ASSERT_EQUAL_UINT32(knuth_hash(42), knuth_hash(42));
};

void test_knuth_hash_different_keys_produce_different_hashes(void) {
  TEST_ASSERT_NOT_EQUAL(knuth_hash(1), knuth_hash(2));
};

void test_knuth_hash_uses_correct_multiplier(void) {
  uint32_t expected = (uint32_t)(7 * 2654435761u);
  TEST_ASSERT_EQUAL_UINT32(expected, knuth_hash(7));
};

/* -----------------------------------------------------------------------
 * Integration
 * ----------------------------------------------------------------------- */

void test_add_get_remove_get_cycle(void) {
  HashMap *map = hashmap_create(8, 0.75);
  int out = 0;
  hashmap_add(map, 99, 42);
  TEST_ASSERT_TRUE(hashmap_get(map, 99, &out));
  TEST_ASSERT_EQUAL_INT(42, out);
  hashmap_remove(map, 99);
  TEST_ASSERT_FALSE(hashmap_get(map, 99, &out));
  hashmap_destroy(map);
};

void test_re_add_after_remove(void) {
  HashMap *map = hashmap_create(8, 0.75);
  int out = 0;
  hashmap_add(map, 10, 1);
  hashmap_remove(map, 10);
  hashmap_add(map, 10, 2);
  TEST_ASSERT_TRUE(hashmap_get(map, 10, &out));
  TEST_ASSERT_EQUAL_INT(2, out);
  TEST_ASSERT_EQUAL_INT(1, map->num_elements);
  hashmap_destroy(map);
};

void test_handles_many_entries(void) {
  HashMap *map = hashmap_create(8, 0.75);
  int n = 30;
  for (int i = 0; i < n; i++) {
    hashmap_add(map, i, i * 10);
  }
  TEST_ASSERT_EQUAL_INT(n, map->num_elements);
  int out = 0;
  for (int i = 0; i < n; i++) {
    TEST_ASSERT_TRUE(hashmap_get(map, i, &out));
    TEST_ASSERT_EQUAL_INT(i * 10, out);
  }
  hashmap_destroy(map);
};

void test_add_remove_all_empties_map(void) {
  HashMap *map = hashmap_create(8, 0.75);
  int keys[] = {4, 8, 15, 16, 23, 42};
  int n = 6;
  for (int i = 0; i < n; i++) {
    hashmap_add(map, keys[i], i);
  }
  for (int i = 0; i < n; i++) {
    hashmap_remove(map, keys[i]);
  }
  TEST_ASSERT_EQUAL_INT(0, map->num_elements);
  int out = 0;
  for (int i = 0; i < n; i++) {
    TEST_ASSERT_FALSE(hashmap_get(map, keys[i], &out));
  }
  hashmap_destroy(map);
};

/* -----------------------------------------------------------------------
 * main
 * ----------------------------------------------------------------------- */

int main(void) {
  UNITY_BEGIN();

  /* hashmap_create */
  RUN_TEST(test_create_returns_non_null);
  RUN_TEST(test_create_sets_correct_size);
  RUN_TEST(test_create_sets_num_elements_zero);
  RUN_TEST(test_create_sets_max_load_factor);
  RUN_TEST(test_create_internal_array_is_null_initialised);
  RUN_TEST(test_create_returns_null_on_non_power_of_two);
  RUN_TEST(test_create_returns_null_on_zero_size);
  RUN_TEST(test_create_returns_null_on_negative_size);

  /* hashmap_destroy */
  RUN_TEST(test_destroy_null_map_does_not_crash);
  RUN_TEST(test_destroy_empty_map);
  RUN_TEST(test_destroy_populated_map);

  /* hashmap_add */
  RUN_TEST(test_add_returns_true_on_new_key);
  RUN_TEST(test_add_returns_true_on_existing_key_upsert);
  RUN_TEST(test_add_returns_false_on_null_map);
  RUN_TEST(test_add_increments_num_elements_for_new_key);
  RUN_TEST(test_add_does_not_increment_num_elements_on_upsert);
  RUN_TEST(test_add_upsert_updates_value);
  RUN_TEST(test_add_zero_as_key);
  RUN_TEST(test_add_negative_key);
  RUN_TEST(test_add_multiple_unique_keys);
  RUN_TEST(test_add_collision_both_keys_retrievable);
  RUN_TEST(test_add_upsert_on_collision_chain_updates_correct_node);

  /* hashmap_get */
  RUN_TEST(test_get_returns_false_on_null_map);
  RUN_TEST(test_get_returns_false_on_empty_map);
  RUN_TEST(test_get_returns_false_for_missing_key);
  RUN_TEST(test_get_returns_true_and_correct_value);
  RUN_TEST(test_get_returns_correct_value_after_upsert);
  RUN_TEST(test_get_collision_retrieves_correct_values);
  RUN_TEST(test_get_does_not_modify_map);

  /* hashmap_remove */
  RUN_TEST(test_remove_returns_false_on_null_map);
  RUN_TEST(test_remove_returns_false_on_empty_map);
  RUN_TEST(test_remove_returns_false_for_missing_key);
  RUN_TEST(test_remove_returns_true_for_existing_key);
  RUN_TEST(test_remove_decrements_num_elements);
  RUN_TEST(test_remove_key_no_longer_retrievable);
  RUN_TEST(test_remove_only_entry_empties_map);
  RUN_TEST(test_remove_does_not_affect_other_keys);
  RUN_TEST(test_remove_negative_key);
  RUN_TEST(test_remove_head_of_collision_chain_leaves_tail_accessible);
  RUN_TEST(test_remove_tail_of_collision_chain_leaves_head_accessible);

  /* hashmap_resize */
  RUN_TEST(test_resize_null_map_does_not_crash);
  RUN_TEST(test_resize_doubles_size);
  RUN_TEST(test_resize_preserves_all_entries);
  RUN_TEST(test_resize_preserves_num_elements);

  /* knuth_hash */
  RUN_TEST(test_knuth_hash_zero);
  RUN_TEST(test_knuth_hash_one);
  RUN_TEST(test_knuth_hash_is_deterministic);
  RUN_TEST(test_knuth_hash_different_keys_produce_different_hashes);
  RUN_TEST(test_knuth_hash_uses_correct_multiplier);

  /* Integration */
  RUN_TEST(test_add_get_remove_get_cycle);
  RUN_TEST(test_re_add_after_remove);
  RUN_TEST(test_handles_many_entries);
  RUN_TEST(test_add_remove_all_empties_map);

  return UNITY_END();
};