#include "../../../Unity/src/unity.h"
#include <stdlib.h>
#include "linked_lists.h"

void setUp(void) {

}

void tearDown(void) {

}


// test cases for size

void test_size_on_null(void) {
    LinkedList* list = NULL;
    TEST_ASSERT_EQUAL_INT(0, size(list));
};

void test_size_no_elements(void) {
    LinkedList list;
    list.head = NULL;

    TEST_ASSERT_EQUAL_INT(0, size(&list));
};

void test_size_one_element(void) {
    LinkedList list;
    list.head = malloc(sizeof(Node));
    list.head->data = 1;
    list.head->next = NULL;

    TEST_ASSERT_EQUAL_INT(1, size(&list));
    free(list.head);
};

void test_size_multiple_elements(void) {
    LinkedList list;
    list.head = malloc(sizeof(Node));
    Node* head = list.head;
    for (int i = 0; i < 9; i++) {
        head->data = i;
        Node* new_node = malloc(sizeof(Node));
        head->next = new_node;
        head = head->next;
    };
    head->data = 9;
    head->next = NULL;

    TEST_ASSERT_EQUAL_INT(10, size(&list));

    head = list.head;
    Node* next;

    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    };


};
// test cases for insert

void test_insert_returns_null_on_empty(void) {
    LinkedList* input = NULL;
    Node* expected = NULL;

    Node* output = insert_node(input, 0, 0);

    TEST_ASSERT_EQUAL_PTR(expected, output);

};

void test_insert_return_null_on_impossible_position(void) {
    LinkedList input;
    input.head = malloc(sizeof(Node));
    input.head->data = 1;
    input.head->next = NULL;

    Node* expected = NULL;

    Node* output_1 = insert_node(&input, 1, -1);
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

    Node* output = insert_node(&input, 0, 0);

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

    TEST_ASSERT_EQUAL_INT(5, size(&input));


    head = input.head;
    Node* next;

    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    };




};

void test_insert_middle_point(void) {
    LinkedList input;
    input.head = malloc(sizeof(Node));
    Node* head = input.head;
    for (int i = 1; i < 6; i++) {
        head->data = i;
        Node* new_node = malloc(sizeof(Node));
        head->next = new_node;
        head = head->next;
    };
    head->data = 6;
    head->next = NULL;

    Node* output = insert_node(&input, 24, 3);

    int index = 0;
    Node* next = input.head;
    while(next != NULL) {
        if (next->data == 24) {
            break;
        }
        index++;
        next = next->next;
    };

    TEST_ASSERT_EQUAL_INT(3, index);


    head = input.head;
    

    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    };


}

// test cases for remove

void test_remove_null_list(void) {
    LinkedList* list = NULL;

    remove_node(list, 5);
    TEST_ASSERT_EQUAL_PTR(NULL, list);
};

void test_remove_empty_list(void) {
    LinkedList list;
    list.head = NULL;

    remove_node(&list, 5);

    TEST_ASSERT_EQUAL_PTR(NULL, list.head);

};

void test_remove_first_node(void) {
    LinkedList list1;
    LinkedList list2;

    list1.head = malloc(sizeof(Node));
    list1.head->data = 1;
    list1.head->next = NULL;

    list2.head = malloc(sizeof(Node));
    Node* head = list2.head;
    Node* next;
    for (int i = 1; i < 5; i++) {
        head->data = i;
        next = malloc(sizeof(Node));
        head->next = next;
        head = head->next;
    };
    head->data = 5;
    head->next = NULL;

    remove_node(&list1, 1);
    remove_node(&list2, 1);

    TEST_ASSERT_EQUAL_PTR(NULL, list1.head);
    Node* follow = list2.head;
    for (int i = 2; i <=5; i++) {
        TEST_ASSERT_EQUAL_INT(i, follow->data);
        follow = follow->next;

    };

    follow = list2.head;
    while (follow != NULL) {
        next = follow->next;
        free(follow);
        follow = next;
    };




};

void test_remove_last_node(void) {
    LinkedList list;
    list.head = malloc(sizeof(Node));
    Node* head = list.head;
    Node* next;
    for (int i = 1; i < 6; i++) {
        head->data = i;
        next = malloc(sizeof(Node));
        head->next = next;
        head = head->next;
    };
    head->data = 6;
    head->next = NULL;

    remove_node(&list, 6);
    head = list.head;
    for (int a = 1; a < 6; a++) {
        TEST_ASSERT_EQUAL_INT(a, head->data);
        head = head->next;
    };

    TEST_ASSERT_EQUAL_PTR(NULL, head);

    head = list.head;
    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    };
};

void test_remove_middle_node(void) {
    LinkedList list;
    list.head = malloc(sizeof(Node));
    Node* head = list.head;
    Node* next;
    for (int i = 1; i < 6; i++) {
        head->data = i;
        next = malloc(sizeof(Node));
        head->next = next;
        head = head->next;
    };
    head->data = 6;
    head->next = NULL;

    remove_node(&list, 4);

    TEST_ASSERT_EQUAL_INT(5, size(&list));

    head = list.head;
    for (int a = 1; a < 4; a++) {
        TEST_ASSERT_EQUAL_INT(a, head->data);
        head = head->next;
    };

    TEST_ASSERT_EQUAL_INT(5, head->data);

    head = list.head;
    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    };
}





int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_insert_returns_null_on_empty);
    RUN_TEST(test_insert_return_null_on_impossible_position);
    RUN_TEST(test_insert_first_position);
    RUN_TEST(test_insert_out_of_bounds);
    RUN_TEST(test_insert_middle_point);

    RUN_TEST(test_size_on_null);
    RUN_TEST(test_size_no_elements);
    RUN_TEST(test_size_one_element);
    RUN_TEST(test_size_multiple_elements);

    RUN_TEST(test_remove_null_list);
    RUN_TEST(test_remove_empty_list);
    RUN_TEST(test_remove_first_node);
    RUN_TEST(test_remove_last_node);
    RUN_TEST(test_remove_middle_node);

    return UNITY_END();
}