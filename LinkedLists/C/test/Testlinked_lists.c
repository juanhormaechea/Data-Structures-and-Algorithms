#include "../../../Unity/src/unity.h"
#include <stdlib.h>
#include "linked_lists.h"

void setUp(void) {

}

void tearDown(void) {

}

// test cases for insert

void test_insert_returns_null_on_empty(void) {
    LinkedList* input = NULL;
    Node* expected = NULL;

    Node* output = insert_node(input, 0, 1);

    TEST_ASSERT_EQUAL_PTR(expected, output);

};

void test_insert_return_null_on_impossible_position(void) {
    LinkedList input;
    input.head = malloc(sizeof(Node));
    input.head->data = 1;
    input.head->next = NULL;

    Node* expected = NULL;

    Node* output_1 = insert_node(&input, 1, 0);
    Node* output_2 = insert_node(&input, 1, -3);


    TEST_ASSERT_EQUAL_PTR(expected, output_1);
    TEST_ASSERT_EQUAL_PTR(expected, output_2);
    free(input.head);
    
}

void test_insert_first_position(void) {
    LinkedList input;
    input.head = malloc(sizeof(Node));
    input.head->data = 1;
    input.head->next = NULL;

    Node* output = insert_node(&input, 0, 1);

    TEST_ASSERT_EQUAL_PTR(input.head, output);
    TEST_ASSERT_EQUAL_INT(0, input.head->data);
    TEST_ASSERT_EQUAL_INT(1, input.head->next->data);

    Node* head = input.head;
    Node* next;

    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    }

};

void test_insert_out_of_bounds(void) {
    LinkedList input;
    input.head = malloc(sizeof(Node));
    Node* head = input.head;
    for (int i = 1; i < 4; i++) {
        head->data = i;
        Node* new_node = malloc(sizeof(Node));
        head->next = new_node;
        head = head->next;
    };
    head->data = 4;
    head->next = NULL;

    Node* output = insert_node(&input, 5, 10);

    TEST_ASSERT_EQUAL_PTR(head->next, output);
    TEST_ASSERT_EQUAL_INT(5, output->data);
    TEST_ASSERT_EQUAL_PTR(NULL, output->next);

    head = input.head;
    for (int i = 1; i < 6; i++) {
        TEST_ASSERT_EQUAL_INT(i, head->data);
        head = head->next;
    };


    head = input.head;
    Node* next;

    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    };




};





int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_insert_returns_null_on_empty);
    RUN_TEST(test_insert_return_null_on_impossible_position);
    RUN_TEST(test_insert_out_of_bounds);

    return UNITY_END();
}