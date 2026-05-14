#include "../../../Unity/src/unity.h"
#include "algos.h"

void setUp(void) {

}

void tearDown(void) {

}

//test cases for bubble sort

void test_bubble_sort_sorts_unordered_array(void) {
    int input[] = {5,17,59,1,53,102,3,53,21,116,53,22};
    int expected[] = {1, 3, 5, 17, 21, 22, 53, 53, 53, 59, 102, 116};
    int length = 12;

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

void test_bubble_sort_negative_values(void) {
    int input[] = {-1, -9, -2, -7, -5, -3, -12, -24, -3};
    int expected[] = {-24, -12, -9, -7, -5, -3, -3, -2, -1};
    int length = 9;

    int* arr = bubble_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, length);
}

//test cases for selection sort

void test_selection_sort_sorts_unordered_array(void) {
    int input[] = {5,17,59,1,53,102,3,53,21,116,53,22};
    int expected[] = {1, 3, 5, 17, 21, 22, 53, 53, 53, 59, 102, 116};
    int length = 12;

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

void test_selection_sort_negative_values(void) {
    int input[] = {-1, -9, -2, -7, -5, -3, -12, -24, -3};
    int expected[] = {-24, -12, -9, -7, -5, -3, -3, -2, -1};
    int length = 9;

    int* arr = selection_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, length);
}

//test cases for insertion sort

void test_insertion_sort_sorts_unordered_array(void) {
    int input[] = {5,17,59,1,53,102,3,53,21,116,53,22};
    int expected[] = {1, 3, 5, 17, 21, 22, 53, 53, 53, 59, 102, 116};
    int length = 12;

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

void test_insertion_sort_negative_values(void) {
    int input[] = {-1, -9, -2, -7, -5, -3, -12, -24, -3};
    int expected[] = {-24, -12, -9, -7, -5, -3, -3, -2, -1};
    int length = 9;

    int* arr = insertion_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, length);
}

// test cases for quicksort

void test_quicksort_sorts_unordered_array(void) {
    int input[] = {5,17,59,1,53,102,3,53,21,116,53,22};
    int expected[] = {1, 3, 5, 17, 21, 22, 53, 53, 53, 59, 102, 116};
    int length = 12;

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

void test_quicksort_sort_negative_values(void) {
    int input[] = {-1, -9, -2, -7, -5, -3, -12, -24, -3};
    int expected[] = {-24, -12, -9, -7, -5, -3, -3, -2, -1};
    int length = 9;

    int* arr = quicksort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, length);
}


// test cases for counting sort
void test_counting_sort_preliminary(void) {
    int input[] = {5,1,2,2,1,4,2,4,3,1,2,3};
    int expected[] = {1, 1, 1, 2, 2, 2, 2, 3, 3, 4, 4, 5};

    int* arr = counting_sort(input, 12);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, 12);
}

void test_counting_sort_sorts_unordered_array(void) {
    int input[] = {5,17,59,1,53,102,3,53,21,116,53,22};
    int expected[] = {1, 3, 5, 17, 21, 22, 53, 53, 53, 59, 102, 116};
    int length = 12;

    int* arr = counting_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
};

void test_counting_sort_sorts_array_single_element(void) {
    int input[] = {65};
    int expected[] = {65};
    int length = 1;

    int* arr = counting_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, length);
};

void test_counting_sort_empty_array(void) {
    int input[] = {};
    int length = 0;
    
    int* arr = counting_sort(input, length);

    TEST_ASSERT_EQUAL_INT(0, sizeof(input)/sizeof(int));
};


void test_counting_sort_already_sorted_array(void) {
    int input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int expected[] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int length = 10;

    int* arr = counting_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, length);
};


//tests for merge_sort

void test_merge_sort_sorts_unordered_array(void) {
    int input[] = {5,17,59,1,53,102,3,53,21,116,53,22};
    int expected[] = {1, 3, 5, 17, 21, 22, 53, 53, 53, 59, 102, 116};
    int length = 12;

    int* arr = merge_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
};

void test_merge_sort_sorts_array_single_element(void) {
    int input[] = {65};
    int expected[] = {65};
    int length = 1;

    int* arr = merge_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, length);
};

void test_merge_sort_empty_array(void) {
    int input[] = {};
    int length = 0;
    
    int* arr = merge_sort(input, length);

    TEST_ASSERT_EQUAL_INT(0, sizeof(input)/sizeof(int));
};


void test_merge_sort_already_sorted_array(void) {
    int input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int expected[] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int length = 10;

    int* arr = merge_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, length);
};

void test_merge_sort_sort_negative_values(void) {
    int input[] = {-1, -9, -2, -7, -5, -3, -12, -24, -3};
    int expected[] = {-24, -12, -9, -7, -5, -3, -3, -2, -1};
    int length = 9;

    int* arr = merge_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, length);
}

// test for linear search

void test_linearsearch_search_empty_array(void) {
    int input[] = {};
    int length = 0;

    TEST_ASSERT_EQUAL_INT(-1, linear_search(input, length, 1));
};

void test_linearsearch_search_first_element(void) {
    int input[] = {5,17,59,1,53,102,3,53,21,116,53,22};
    int length = 12;

    TEST_ASSERT_EQUAL_INT(0, linear_search(input, length, 5));
};

void test_linearsearch_search_last_element(void) {
    int input[] = {5,17,59,1,53,102,3,53,21,116,53,22};
    int length = 12;

    TEST_ASSERT_EQUAL_INT(11, linear_search(input, length, 22));
};

void test_linearsearch_search_first_element_seen(void) {
    int input[] = {5,17,59,1,53,102,3,53,21,116,53,22};
    int length = 12;

    TEST_ASSERT_EQUAL_INT(4, linear_search(input, length, 53));
};

void test_linearsearch_search_negative_values_first_element(void) {
    int input[] = {-1, -9, -2, -7, -5, -3, -12, -24, -3};
    int length = 9;

    TEST_ASSERT_EQUAL_INT(0, linear_search(input, length, -1));
};

void test_linearsearch_search_negative_values_last_element(void) {
    int input[] = {-1, -9, -2, -7, -5, -3, -12, -24, -16};
    int length = 9;

    TEST_ASSERT_EQUAL_INT(8, linear_search(input, length, -16));
};

void test_linearsearch_search_negative_values_first_element_seen(void) {
    int input[] = {-1, -9, -2, -7, -5, -3, -12, -24, -3};
    int length = 9;

    TEST_ASSERT_EQUAL_INT(5, linear_search(input, length, -3));
};

// test cases for binary search

void test_binary_search_search_empty_array(void) {
    int input[] = {};
    int length = 0;

    TEST_ASSERT_EQUAL_INT(-1, binary_search(input, length, 1));
};

void test_binary_search_search_first_element(void) {
    int input[] = {1, 3, 5, 17, 21, 22, 53, 53, 53, 59, 102, 116};
    int length = 12;

    TEST_ASSERT_EQUAL_INT(0, binary_search(input, length, 1));
};

void test_binary_search_search_last_element(void) {
    int input[] = {1, 3, 5, 17, 21, 22, 53, 53, 53, 59, 102, 116};
    int length = 12;

    TEST_ASSERT_EQUAL_INT(11, binary_search(input, length, 116));
};


void test_binary_search_search_negative_values_first_element(void) {
    int input[] = {-24, -12, -9, -7, -5, -3, -3, -2, -1};
    int length = 9;

    TEST_ASSERT_EQUAL_INT(0, binary_search(input, length, -24));
};

void test_binary_search_search_negative_values_last_element(void) {
    int input[] = {-24, -12, -9, -7, -5, -3, -3, -2, -1};
    int length = 9;

    TEST_ASSERT_EQUAL_INT(8, binary_search(input, length, -1));
};



int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_bubble_sort_sorts_unordered_array);
    RUN_TEST(test_bubble_sort_sorts_array_single_element);
    RUN_TEST(test_bubble_sort_empty_array);
    RUN_TEST(test_bubble_sort_already_sorted_array);
    RUN_TEST(test_bubble_sort_negative_values);
    
    RUN_TEST(test_selection_sort_sorts_unordered_array);
    RUN_TEST(test_selection_sort_sorts_array_single_element);
    RUN_TEST(test_selection_sort_empty_array);
    RUN_TEST(test_selection_sort_already_sorted_array);
    RUN_TEST(test_selection_sort_negative_values);

    RUN_TEST(test_insertion_sort_sorts_unordered_array);
    RUN_TEST(test_insertion_sort_sorts_array_single_element);
    RUN_TEST(test_insertion_sort_empty_array);
    RUN_TEST(test_insertion_sort_already_sorted_array);
    RUN_TEST(test_insertion_sort_negative_values);

    RUN_TEST(test_quicksort_sorts_unordered_array);
    RUN_TEST(test_quicksort_sorts_array_single_element);
    RUN_TEST(test_quicksort_empty_array);
    RUN_TEST(test_quicksort_already_sorted_array);
    RUN_TEST(test_quicksort_sort_negative_values);

    RUN_TEST(test_counting_sort_preliminary);
    RUN_TEST(test_counting_sort_sorts_unordered_array);
    RUN_TEST(test_counting_sort_sorts_array_single_element);
    RUN_TEST(test_counting_sort_empty_array);
    RUN_TEST(test_counting_sort_already_sorted_array);

    RUN_TEST(test_merge_sort_sorts_unordered_array);
    RUN_TEST(test_merge_sort_sorts_array_single_element);
    RUN_TEST(test_merge_sort_empty_array);
    RUN_TEST(test_merge_sort_already_sorted_array);
    RUN_TEST(test_merge_sort_sort_negative_values);

    RUN_TEST(test_linearsearch_search_empty_array);
    RUN_TEST(test_linearsearch_search_first_element);
    RUN_TEST(test_linearsearch_search_last_element);
    RUN_TEST(test_linearsearch_search_negative_values_first_element);
    RUN_TEST(test_linearsearch_search_negative_values_last_element);
    RUN_TEST(test_linearsearch_search_first_element_seen);
    RUN_TEST(test_linearsearch_search_negative_values_first_element_seen);

    RUN_TEST(test_binary_search_search_empty_array);
    RUN_TEST(test_binary_search_search_first_element);
    RUN_TEST(test_binary_search_search_last_element);
    RUN_TEST(test_binary_search_search_negative_values_first_element);
    RUN_TEST(test_binary_search_search_negative_values_last_element);
  
    return UNITY_END();
}