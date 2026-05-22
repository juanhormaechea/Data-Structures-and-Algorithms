#include "../../../Unity/src/unity.h"
#include <stdlib.h>
#include "stacks.h"

void setUp(void) {

}

void tearDown(void) {

}

// test cases for push

void test_push_null_stack(void) {
    Stack* stack = NULL;
    push(stack, 1);
    TEST_ASSERT_EQUAL_PTR(NULL, stack);
    
};

void test_push_stack_empty(void) {
    Stack stack;
    push(&stack, 1);
    TEST_ASSERT_EQUAL_INT(1, stack.size);
    TEST_ASSERT_EQUAL_INT(1, stack.head->data);
    TEST_ASSERT_EQUAL_PTR(NULL, stack.head->next);

    free(stack.head);
};

void test_push_stack_full(void) {
    Stack stack;
    for (int i = 0; i < 5; i++) {
        push(&stack, i);
    };

    Node* head = stack.head;
    TEST_ASSERT_EQUAL_INT(5, stack.size);
    
    for (int a = 4; a >= 0; a--) {
        TEST_ASSERT_EQUAL_INT(a, head->data);
        head = head->next;
    };

    TEST_ASSERT_EQUAL_PTR(NULL, head);
    
    head = stack.head;
    Node* next;
    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    };
};

void test_push_stack_same_node(void) {
    Stack stack;
    for (int i = 0; i < 5; i++) {
        push(&stack, i);
    };

    push(&stack, 4);

    TEST_ASSERT_EQUAL_INT(6, stack.size);
    TEST_ASSERT_EQUAL_INT(4, stack.head->data);

    Node* head = stack.head->next;
    for (int a = 4; a >= 0; a--) {
        TEST_ASSERT_EQUAL_INT(a, head->data);
        head = head->next;
    };
    
    TEST_ASSERT_EQUAL_PTR(NULL, head);
    
    head = stack.head;
    Node* next;
    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    };
}


// test cases for isEmpty

void test_isEmpty_null_stack(void) {
    Stack* stack = NULL;
    bool empty = isEmpty(stack);
    TEST_ASSERT_TRUE(empty);
    
};

void test_isEmpty_stack(void) {
    Stack stack;
    bool empty = isEmpty(&stack);
    TEST_ASSERT_TRUE(empty);
};

void test_isEmpty_non_empty_stack(void) {
    Stack stack;
    for (int i = 0; i < 5; i++) {
        push(&stack, i);
    };

    bool empty = isEmpty(&stack);

    TEST_ASSERT_FALSE(empty);

    Node* head = stack.head;
    Node* next;
    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    };
};

// test cases for stackSize

void test_stackSize_null_list(void) {
    Stack* stack = NULL;
    TEST_ASSERT_EQUAL_INT(0, stackSize(stack));
};

void test_stackSize_empty_list(void) {
    Stack stack;
    TEST_ASSERT_EQUAL_INT(0, stackSize(&stack));

};

void test_stackSize_full_list(void) {
    Stack stack;
    for (int i = 0; i < 10; i++) {
        push(&stack, i);
    };

    TEST_ASSERT_EQUAL_INT(10, stackSize(&stack));
};

// test cases for peek

void test_peek_null_list(void) {
    Stack* stack = NULL;
    int value;
    TEST_ASSERT_FALSE(peek(stack, &value));
};

void test_peek_empty_list(void) {
    Stack stack;
    int value;
    TEST_ASSERT_FALSE(peek(&stack, &value));
};

void test_peek_one_node(void) {
    Stack stack;
    int value;
    push(&stack, 1);
    TEST_ASSERT_TRUE(peek(&stack, &value));
    TEST_ASSERT_EQUAL_INT(1, value);
    free(stack.head);
};

void test_peek_full_list(void) {
    Stack stack;
    int value;
    for (int i = 0; i < 10; i++) {
        push(&stack, i);
    };

    TEST_ASSERT_TRUE(peek(&stack, &value));
    TEST_ASSERT_EQUAL_INT(9, value);
    Node* head = stack.head;
    Node* next;
    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    };    

};

// test cases for pop

void test_pop_null_list(void) {
    Stack* stack = NULL;
    int value;
    TEST_ASSERT_FALSE(pop(stack, &value));
};

void test_pop_empty_list(void) {
    Stack stack;
    int value;
    TEST_ASSERT_FALSE(pop(&stack, &value));
};

void test_pop_one_node(void) {
    Stack stack;
    int value;
    push(&stack, 1);
    TEST_ASSERT_TRUE(pop(&stack, &value));
    TEST_ASSERT_EQUAL_INT(1, value);
    TEST_ASSERT_TRUE(isEmpty(&stack));
    TEST_ASSERT_EQUAL_PTR(NULL, stack.head);

};

void test_pop_full_list(void) {
    Stack stack;
    int value;
    for (int i = 0; i < 10; i++) {
        push(&stack, i);
    };
    pop(&stack, &value);
    TEST_ASSERT_EQUAL_INT(9, stackSize(&stack));
    TEST_ASSERT_EQUAL_INT(9, value);
    TEST_ASSERT_EQUAL_INT(8, stack.head->data);
    Node* head = stack.head;
    Node* next;
    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    };
};






int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_push_null_stack);
    RUN_TEST(test_push_stack_empty);
    RUN_TEST(test_push_stack_full);
    RUN_TEST(test_push_stack_same_node);
    
    RUN_TEST(test_isEmpty_null_stack);
    RUN_TEST(test_isEmpty_stack);
    RUN_TEST(test_isEmpty_non_empty_stack);

    RUN_TEST(test_stackSize_null_list);
    RUN_TEST(test_stackSize_empty_list);
    RUN_TEST(test_stackSize_full_list);

    RUN_TEST(test_peek_null_list);
    RUN_TEST(test_peek_empty_list);
    RUN_TEST(test_peek_one_node);
    RUN_TEST(test_peek_full_list);

    RUN_TEST(test_pop_null_list);
    RUN_TEST(test_pop_empty_list);
    RUN_TEST(test_pop_one_node);
    RUN_TEST(test_pop_full_list);

    return UNITY_END();
}