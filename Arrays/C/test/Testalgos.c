#include "../../../Unity/src/unity.h"
#include "algos.h"

void setUp(void) {

}

void tearDown(void) {

}

//test cases

void test_bubble_sort_sorts_unordered_array(void) {
    int input[] = {65, 18, 34, 68, 69};
    int expected[] = {18, 34, 65, 68, 69};
    int length = 5;

    int* arr = bubble_sort(input, length);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, input, length);
};



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_bubble_sort_sorts_unordered_array);

    return UNITY_END();
}