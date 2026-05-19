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
    if (!list.head) {
        perror("memory allocation failed");
        exit(1);
    }
    list.head->data = 1;
    list.head->next = NULL;

    TEST_ASSERT_EQUAL_INT(1, size(&list));
    free(list.head);
};

void test_size_multiple_elements(void) {
    LinkedList list;
    list.head = malloc(sizeof(Node));
    if (!list.head) {
        perror("memory allocation failed");
        exit(1);
    }
    Node* head = list.head;
    for (int i = 0; i < 9; i++) {
        head->data = i;
        Node* new_node = malloc(sizeof(Node));
        if (!new_node) {
        perror("memory allocation failed");
        exit(1);
        }
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
    if (!input.head) {
        perror("memory allocation failed");
        exit(1);
    }
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
    if (!input.head) {
        perror("memory allocation failed");
        exit(1);
    }
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
    if (!input.head) {
        perror("memory allocation failed");
        exit(1);
    }
    Node* head = input.head;
    for (int i = 1; i < 4; i++) {
        head->data = i;
        Node* new_node = malloc(sizeof(Node));
        if (!new_node) {
        perror("memory allocation failed");
        exit(1);
        }
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
    if (!input.head) {
        perror("memory allocation failed");
        exit(1);
    }
    Node* head = input.head;
    for (int i = 1; i < 6; i++) {
        head->data = i;
        Node* new_node = malloc(sizeof(Node));
        if (!new_node) {
        perror("memory allocation failed");
        exit(1);
        }
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
    if (!list1.head) {
        perror("memory allocation failed");
        exit(1);
    }
    list1.head->data = 1;
    list1.head->next = NULL;

    list2.head = malloc(sizeof(Node));
    if (!list2.head) {
        perror("memory allocation failed");
        exit(1);
    }
    Node* head = list2.head;
    Node* next;
    for (int i = 1; i < 5; i++) {
        head->data = i;
        next = malloc(sizeof(Node));
        if (!next) {
        perror("memory allocation failed");
        exit(1);
        }
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
    if (!list.head) {
        perror("memory allocation failed");
        exit(1);
    }
    Node* head = list.head;
    Node* next;
    for (int i = 1; i < 6; i++) {
        head->data = i;
        next = malloc(sizeof(Node));
        if (!next) {
        perror("memory allocation failed");
        exit(1);
        }
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
    if (!list.head) {
        perror("memory allocation failed");
        exit(1);
    }
    Node* head = list.head;
    Node* next;
    for (int i = 1; i < 6; i++) {
        head->data = i;
        next = malloc(sizeof(Node));
        if (!next) {
        perror("memory allocation failed");
        exit(1);
        }
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
};

// tests for search node

void test_search_null_list(void) {
    LinkedList* list = NULL;

    TEST_ASSERT_EQUAL_PTR(NULL, search_node(list, 1));
};

void test_search_empty_list(void) {
    LinkedList list;
    list.head = NULL;

    TEST_ASSERT_EQUAL_PTR(NULL, search_node(&list, 1));

};

void test_search_first_node(void) {
    LinkedList list1;
    LinkedList list2;
    list1.head = malloc(sizeof(Node));
    list1.head->data = 1;
    list1.head->next = NULL;

    list2.head = malloc(sizeof(Node));
    Node* head = list2.head;
    for (int i = 1; i < 5; i++) {
        head->data = i;
        Node* next = malloc(sizeof(Node));
        head->next = next;
        head = next;
    };
    head->data = 5;
    head->next = NULL;

    Node* result1 = search_node(&list1, 1);
    Node* result2 = search_node(&list2, 1);

    TEST_ASSERT_EQUAL_INT(1, result1->data);
    TEST_ASSERT_EQUAL_PTR(NULL, result1->next);

    TEST_ASSERT_EQUAL_INT(1, result2->data);
    TEST_ASSERT_EQUAL_INT(2, result2->next->data);
    TEST_ASSERT_EQUAL_PTR(list2.head->next, result2->next);

    free(list1.head);

    head = list2.head;
    Node* next;
    while(head != NULL) {
        next = head->next;
        free(head);
        head = next;
    };
};

void test_search_last_node(void) {
    LinkedList list;
    list.head = malloc(sizeof(Node));
    Node* head = list.head;
    for (int i = 1; i < 7; i++) {
        head->data = i;
        Node* next = malloc(sizeof(Node));
        head->next = next;
        head = next;
    };
    head->data = 7;
    head->next = NULL;

    Node* result = search_node(&list, 7);

    TEST_ASSERT_EQUAL_INT(7, result->data);
    TEST_ASSERT_EQUAL_PTR(NULL, result->next);

    head = list.head;
    Node* next;
    while(head != NULL) {
        next = head->next;
        free(head);
        head = next;
    };
};

void test_search_middle_node(void) {
    LinkedList list;
    list.head = malloc(sizeof(Node));
    Node* head = list.head;
    for (int i = 1; i < 7; i++) {
        head->data = i;
        Node* next = malloc(sizeof(Node));
        head->next = next;
        head = next;
    };
    head->data = 7;
    head->next = NULL;

    Node* result = search_node(&list, 4);

    TEST_ASSERT_EQUAL_INT(4, result->data);
    TEST_ASSERT_EQUAL_INT(5, result->next->data);

    head = list.head;
    Node* next;
    while(head != NULL) {
        next = head->next;
        free(head);
        head = next;
    };
};

// tests for sort list

void test_sort_empty_list(void) {
    LinkedList list;
    list.head = NULL;
    Node* output = sort_list(list.head, 0);
    list.head = output;

    int list_size = size(&list);

    TEST_ASSERT_EQUAL_PTR(NULL, list.head);
    TEST_ASSERT_EQUAL_INT(0, list_size);
};

void test_sort_one_element(void) {
    LinkedList list;
    list.head = malloc(sizeof(Node));
    list.head->data = 1;
    list.head->next = NULL;
    list.head = sort_list(list.head, 1);
    int list_size = size(&list);

    TEST_ASSERT_EQUAL_INT(1, list_size);
    TEST_ASSERT_EQUAL_INT(1, list.head->data);
    TEST_ASSERT_EQUAL_PTR(NULL, list.head->next);

    free(list.head);
};

void test_sort_even_size(void) {
    int input_array[10] = {1,8,2,6,12,4,24,-1,3,63};
    int expected[10] = {-1, 1, 2, 3, 4, 6, 8, 12, 24, 63};
    int output_array[10];
    LinkedList input_list;
    LinkedList output_list;
    input_list.head = malloc(sizeof(Node));
    Node* head = input_list.head;
    for (int i = 0; i < 9; i++) {
        head->data = input_array[i];
        Node* next = malloc(sizeof(Node));
        head->next = next;
        head = head->next;
    };
    head->data = input_array[9];
    head->next = NULL;

    output_list.head = sort_list(input_list.head, 10);
    int size_list = size(&output_list);

    head = output_list.head;
    for (int i = 0; i < 10; i++) {
        output_array[i] = head->data;
        head = head->next;
    };

    TEST_ASSERT_EQUAL_INT(10, size_list);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, output_array, 10);
    
    Node* next;
    head = output_list.head;
    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    };
    

};

void test_sort_odd_size(void) {
    int input_array[9] = {1,8,2,6,12,4,24,-1,3};
    int expected[9] = {-1, 1, 2, 3, 4, 6, 8, 12, 24};
    int output_array[9];
    LinkedList input_list;
    LinkedList output_list;
    input_list.head = malloc(sizeof(Node));
    Node* head = input_list.head;
    for (int i = 0; i < 8; i++) {
        head->data = input_array[i];
        Node* next = malloc(sizeof(Node));
        head->next = next;
        head = head->next;
    };
    head->data = input_array[8];
    head->next = NULL;

    output_list.head = sort_list(input_list.head, 9);
    int size_list = size(&output_list);

    head = output_list.head;
    for (int i = 0; i < 9; i++) {
        output_array[i] = head->data;
        head = head->next;
    };

    TEST_ASSERT_EQUAL_INT(9, size_list);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, output_array, 9);
    
    Node* next;
    head = output_list.head;
    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    };
}

void test_sort_negatives(void) {
    int input_array[10] = {-5, -3, -8, -2, -7, -4, -9, -6, -1, -0};
    int expected[10] = {-9, -8, -7, -6, -5, -4, -3, -2, -1, -0};
    int output_array[10];
    LinkedList input_list;
    LinkedList output_list;
    input_list.head = malloc(sizeof(Node));
    Node* head = input_list.head;
    for (int i = 0; i < 9; i++) {
        head->data = input_array[i];
        Node* next = malloc(sizeof(Node));
        head->next = next;
        head = head->next;
    };
    head->data = input_array[9];
    head->next = NULL;
    output_list.head = sort_list(input_list.head, 10);
    int size_list = size(&output_list);

    head = output_list.head;
    for (int i = 0; i < 10; i++) {
        output_array[i] = head->data;
        head = head->next;
    };

    TEST_ASSERT_EQUAL_INT(10, size_list);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, output_array, 10);

    Node* next;
    head = output_list.head;
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

    RUN_TEST(test_search_null_list);
    RUN_TEST(test_search_empty_list);
    RUN_TEST(test_search_first_node);
    RUN_TEST(test_search_last_node);
    RUN_TEST(test_search_middle_node);

    RUN_TEST(test_sort_empty_list);
    RUN_TEST(test_sort_even_size);
    RUN_TEST(test_sort_odd_size);
    RUN_TEST(test_sort_one_element);
    RUN_TEST(test_sort_negatives);

    return UNITY_END();
}