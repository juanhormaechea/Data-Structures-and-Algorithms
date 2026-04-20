#include "../../../Unity/src/unity.h"
#include "algos.h"

void setUp(void) {

}

void tearDown(void) {

}

//test cases for bubble sort

void test_bubble_sort_sorts_unordered_array(void) {
    int input[] = {65, 18, 34, 68, 69};
    int expected[] = {18, 34, 65, 68, 69};
    int length = 5;

    int* arr = bubble_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
};

void test_bubble_sort_sorts_array_single_element(void) {
    int input[] = {65};
    int expected[] = {65};
    int length = 1;

    int* arr = bubble_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, length);
};

void test_bubble_sort_empty_array(void) {
    int input[] = {};
    int length = 0;
    
    int* arr = bubble_sort(input, length);

    TEST_ASSERT_EQUAL_INT(0, sizeof(input)/sizeof(int));
};


void test_bubble_sort_already_sorted_array(void) {
    int input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int expected[] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int length = 10;

    int* arr = bubble_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, length);
};

//test cases for selection sort

void test_selection_sort_sorts_unordered_array(void) {
    int input[] = {65, 18, 34, 68, 69};
    int expected[] = {18, 34, 65, 68, 69};
    int length = 5;

    int* arr = selection_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
};

void test_selection_sort_sorts_array_single_element(void) {
    int input[] = {65};
    int expected[] = {65};
    int length = 1;

    int* arr = selection_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, length);
};

void test_selection_sort_empty_array(void) {
    int input[] = {};
    int length = 0;
    
    int* arr = selection_sort(input, length);

    TEST_ASSERT_EQUAL_INT(0, sizeof(input)/sizeof(int));
};


void test_selection_sort_already_sorted_array(void) {
    int input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int expected[] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int length = 10;

    int* arr = selection_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, length);
};

//test cases for insertion sort

void test_insertion_sort_sorts_unordered_array(void) {
    int input[] = {65, 18, 34, 68, 69};
    int expected[] = {18, 34, 65, 68, 69};
    int length = 5;

    int* arr = insertion_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
};

void test_insertion_sort_sorts_array_single_element(void) {
    int input[] = {65};
    int expected[] = {65};
    int length = 1;

    int* arr = insertion_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, length);
};

void test_insertion_sort_empty_array(void) {
    int input[] = {};
    int length = 0;
    
    int* arr = insertion_sort(input, length);

    TEST_ASSERT_EQUAL_INT(0, sizeof(input)/sizeof(int));
};


void test_insertion_sort_already_sorted_array(void) {
    int input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int expected[] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int length = 10;

    int* arr = insertion_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, length);
};

// test cases for quicksort

void test_quicksort_sorts_unordered_array(void) {
    int input[] = {65, 18, 34, 68, 69};
    int expected[] = {18, 34, 65, 68, 69};
    int length = 5;

    int* arr = quicksort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
};

void test_quicksort_sorts_array_single_element(void) {
    int input[] = {65};
    int expected[] = {65};
    int length = 1;

    int* arr = quicksort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, length);
};

void test_quicksort_empty_array(void) {
    int input[] = {};
    int length = 0;
    
    int* arr = quicksort(input, length);

    TEST_ASSERT_EQUAL_INT(0, sizeof(input)/sizeof(int));
};


void test_quicksort_already_sorted_array(void) {
    int input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int expected[] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int length = 10;

    int* arr = quicksort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, length);
};

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_bubble_sort_sorts_unordered_array);
    RUN_TEST(test_bubble_sort_sorts_array_single_element);
    RUN_TEST(test_bubble_sort_empty_array);
    RUN_TEST(test_bubble_sort_already_sorted_array);
    
    RUN_TEST(test_selection_sort_sorts_unordered_array);
    RUN_TEST(test_selection_sort_sorts_array_single_element);
    RUN_TEST(test_selection_sort_empty_array);
    RUN_TEST(test_selection_sort_already_sorted_array);

    RUN_TEST(test_insertion_sort_sorts_unordered_array);
    RUN_TEST(test_insertion_sort_sorts_array_single_element);
    RUN_TEST(test_insertion_sort_empty_array);
    RUN_TEST(test_insertion_sort_already_sorted_array);

    RUN_TEST(test_quicksort_sorts_unordered_array);
    RUN_TEST(test_quicksort_sorts_array_single_element);
    RUN_TEST(test_quicksort_empty_array);
    RUN_TEST(test_quicksort_already_sorted_array);
    return UNITY_END();
}