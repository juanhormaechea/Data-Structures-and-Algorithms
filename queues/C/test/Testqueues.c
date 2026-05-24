#include "../../../Unity/src/unity.h"
#include <stdlib.h>
#include "queues.h"

void setUp(void) {

}

void tearDown(void) {

}

// test cases for enqueue

void test_enqueue_null_queue(void) {
    Queue* queue = NULL;
    enqueue(queue, 1);
    TEST_ASSERT_EQUAL_PTR(NULL, queue);
};

void test_enqueue_empty_queue(void) {
    Queue queue;
    enqueue(&queue, 1);
    TEST_ASSERT_EQUAL_INT(1, queue.size);
    TEST_ASSERT_EQUAL_INT(1, queue.back->data);
    TEST_ASSERT_EQUAL_INT(1, queue.front->data);
    TEST_ASSERT_EQUAL_PTR(queue.front, queue.back);
    free(queue.back);
};

void test_enqueue_full_queue(void) {
    Queue queue;
    for (int i = 0; i < 10; i++) {
        enqueue(&queue, i);
    };
    TEST_ASSERT_EQUAL_INT(10, queue.size);
    Node* front = queue.front;
    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL_INT(i, front->data);
        front = front->next;
    };
    
    TEST_ASSERT_EQUAL_INT(9, queue.back->data);
    TEST_ASSERT_EQUAL_PTR(NULL, queue.back->next);
    front = queue.front;
    Node* next;
    while (front != NULL) {
        next = front->next;
        free(front);
        front = next;
    };
};

// test cases for dequeue

void test_dequeue_null_queue(void) {
    Queue* queue = NULL;
    int value;
    TEST_ASSERT_FALSE(dequeue(queue, &value));
    TEST_ASSERT_EQUAL_PTR(NULL, queue);
};

void test_dequeue_empty_queue(void) {
    Queue queue = {0};
    int value;
    TEST_ASSERT_FALSE(dequeue(&queue, &value));
    TEST_ASSERT_EQUAL_PTR(NULL, queue.front);
    TEST_ASSERT_EQUAL_PTR(NULL, queue.back);
};

void test_dequeue_one_node(void) {
    Queue queue = {0};
    int value;
    enqueue(&queue, 1);
    TEST_ASSERT_TRUE(dequeue(&queue, &value));
    TEST_ASSERT_EQUAL_INT(1, value);
    TEST_ASSERT_EQUAL_INT(0, queue.size);
    TEST_ASSERT_EQUAL_PTR(NULL, queue.front);
    TEST_ASSERT_EQUAL_PTR(NULL, queue.back);
};

void test_dequeue_full_queue(void) {
    Queue queue = {0};
    int value;
    for (int i = 0; i < 10; i++) {
        enqueue(&queue, i);
    };

    TEST_ASSERT_TRUE(dequeue(&queue, &value));
    TEST_ASSERT_EQUAL_INT(0, value);
    TEST_ASSERT_EQUAL_INT(9, queue.size);
    TEST_ASSERT_EQUAL_INT(1, queue.front->data);
    TEST_ASSERT_EQUAL_INT(9, queue.back->data);

    Node* front = queue.front;
    Node* next;
    for (int i = 1; i < 10; i++) {
        next = front->next;
        free(front);
        front = next;
    };
};


// test cases for peek

void test_peek_null_queue(void) {
    Queue* queue = NULL;
    int value;
    TEST_ASSERT_FALSE(peek(queue, &value));
};

void test_peek_empty_queue(void) {
    Queue queue = {0};
    int value;
    TEST_ASSERT_FALSE(peek(&queue, &value));
};

void test_peek_one_node(void) {
    Queue queue = {0};
    int value;
    enqueue(&queue, 1);
    TEST_ASSERT_TRUE(peek(&queue, &value));
    TEST_ASSERT_EQUAL_INT(1, queue.size);
    TEST_ASSERT_EQUAL_INT(1, value);
    free(queue.front);
};

void test_peek_full_queue(void) {
    Queue queue = {0}; 
    int value;
    for (int i = 0; i < 10; i++){
        enqueue(&queue, i);
    };
    TEST_ASSERT_TRUE(peek(&queue, &value));
    TEST_ASSERT_EQUAL_INT(10, queue.size);
    TEST_ASSERT_EQUAL_INT(0, value);
    while (queue.size > 0) {
        dequeue(&queue, &value);
    };
};

// test cases for isEmpty

void test_isEmpty_null_queue(void) {
    Queue* queue = NULL;
    TEST_ASSERT_TRUE(isEmpty(queue));
};

void test_isEmpty_empty_queue(void) {
    Queue queue = {0};
    TEST_ASSERT_TRUE(isEmpty(&queue));

};

void test_isEmpty_non_empty(void) {
    Queue queue = {0};
    int value;
    for (int i = 0; i < 10; i++) {
        enqueue(&queue, i);
        TEST_ASSERT_FALSE(isEmpty(&queue));
    };
    while (queue.size > 0) {
        dequeue(&queue, &value);
    };

    TEST_ASSERT_TRUE(isEmpty(&queue));
};

// test cases for queueSize

void test_queueSize_null_queue(void) {
    Queue* queue = NULL;
    TEST_ASSERT_EQUAL_INT(0, queueSize(queue));
};

void test_queueSize_empty_queue(void) {
    Queue queue = {0};
    TEST_ASSERT_EQUAL_INT(0, queueSize(&queue));
};

void test_queueSize_non_empty(void) {
    Queue queue = {0};
    int value;
    for (int i = 1; i < 10; i++) {
        enqueue(&queue, i);
        TEST_ASSERT_EQUAL_INT(i, queueSize(&queue));
    };

    while (queue.size > 0) {
        dequeue(&queue, &value);
    };
};



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_enqueue_null_queue);
    RUN_TEST(test_enqueue_empty_queue);
    RUN_TEST(test_enqueue_full_queue);

    RUN_TEST(test_dequeue_null_queue);
    RUN_TEST(test_dequeue_empty_queue);
    RUN_TEST(test_dequeue_one_node);
    RUN_TEST(test_dequeue_full_queue);

    RUN_TEST(test_peek_null_queue);
    RUN_TEST(test_peek_empty_queue);
    RUN_TEST(test_peek_one_node);
    RUN_TEST(test_peek_full_queue);

    RUN_TEST(test_isEmpty_null_queue);
    RUN_TEST(test_isEmpty_empty_queue);
    RUN_TEST(test_isEmpty_non_empty);

    RUN_TEST(test_queueSize_null_queue);
    RUN_TEST(test_queueSize_empty_queue);
    RUN_TEST(test_queueSize_non_empty);
    return UNITY_END();
}