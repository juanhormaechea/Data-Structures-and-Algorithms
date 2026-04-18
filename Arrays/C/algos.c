#include "algos.h"
#include <stdio.h>
#include <stdbool.h>

int* bubble_sort(int* arr, int length) {
    bool swap = false;
    for (int i = 0; i < length; i++) {
        swap = false;
        for (int j = 0; j < length-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int swap_num = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = swap_num;
                swap = true;
            };
        };
        if (!swap) break;
    };

    return arr;
};

int* selection_sort(int* arr, int length) {
    for (int i = 0; i < length; i++) {
        int min = arr[i];
        int index = i;
        for (int j = i; j < length; j++) {
            if (arr[j] < min) {
                min = arr[j];
                index = j;
            };
        };
        int swap_num = arr[index];
        arr[index] = arr[i];
        arr[i] = swap_num;
    };

    return arr;
};

int* insertion_sort(int* arr, int length) {
    for (int i = 0; i < length-1; i++) {
        int index = i+1;
        for (int j = 0; j <= i; j++) {
            if (arr[i+1] > arr[i]) break;
            if (arr[j] > arr[i+1]) {
                index = j;
                break;
            }
        };
        if (index != i+1) {
            int swap_num = arr[i+1];
            for (int a = i; a >= index; a--) {
                arr[a+1] = arr[a];
            };
            arr[index] = swap_num;
        };
    };

    return arr;
};


int partition(int* arr, int length) {
    int i = 0;
    int pivot = arr[length-1];
    for (int j = 0; j < length-1; j++) {
        if (arr[j] < pivot) {
            int swap = arr[j];
            arr[j] = arr[i];
            arr[i] = swap;
            i++;
        };
    };
    arr[length-1] = arr[i];
    arr[i] = pivot;
    return i;
};

int* quicksort(int* arr, int length) {
    if (length == 1 || length == 0) {
        return arr;
    } else {
        int new_length = partition(arr, length);
        quicksort(arr, new_length);
        quicksort(&arr[new_length], length-new_length);
    };
};
