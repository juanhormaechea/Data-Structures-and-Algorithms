#include "algos.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

 //worst case time complexity of O(n^2)
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

//time complexity of O(n^2)
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

//time complexity of O(n^2)
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

//partition function for quicksort, moves all elements less than pivot to the left
//and all elements greater or equal to pivot to the right
int partition(int* arr, int length) {
    if (length == 0) {
        return 0;
    }
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
    if (i == 0){
        return 1;
    }
    return i;
};

//worst case time complexity of O(n^2), occurs when array is already sorted.
//average time complexity of O(n·log_2(n))
int* quicksort(int* arr, int length) {
   if (length > 1) {
        int new_length = partition(arr, length);
        quicksort(arr, new_length);
        quicksort(&arr[new_length], length-new_length);
    };
    return arr;
};


// O(n+k) time complexity where k is the max value in array
int* counting_sort(int* arr, int length) {
    if (length <= 0) {
        return arr;
    };

    int max = 0;
    for (int i = 0; i < length; i++) {
        if (arr[i] < 0) {
            return NULL;
        }
        if (arr[i] > max) {
            max = arr[i];
        };
    };

    int* sorted_arr = calloc(max+1, sizeof(int));


    
    for (int i = 0; i < length; i++) {
        sorted_arr[arr[i]] += 1;
    };

    int index = 0;
    for (int i = 0; i < max+1; i++) {
        for (int a = 0; sorted_arr[i] > 0; a++){
            arr[index] = i;
            index++;
            sorted_arr[i]--;
        };
    };

    return arr;
}

int* merge(int* arr1, int* arr2, int length1, int length2) {
    if (length1 == 0) {
        return arr2;
    };

    if (length2 == 0) {
        return arr1;
    };

    int* new_arr = malloc((length1 + length2) * sizeof(int));
    int i = 0, j = 0, z = 0;

    if(!new_arr) {
        perror("Memory allocation failed");
        exit(1);
    };
    
    while (i < length1 && j < length2) {
        if (arr1[i] <= arr2[j]) {
            new_arr[z] = arr1[i];
            i++;
            z++;
        } else {
            new_arr[z] = arr2[j];
            j++;
            z++;
        }
    };

    while (i < length1) {
        new_arr[z] = arr1[i];
        i++;
        z++;
    }

    while (j < length2) {
        new_arr[z] = arr2[j];
        j++;
        z++;
    }

    if (arr1 != NULL && length1 >= 2) {
        free(arr1);
    };

    if (arr2 != NULL && length2 >= 2) {
        free(arr2);
    }
    return new_arr;
}

// time complexity of O(n·log_2(n))
int* merge_sort(int* arr, int length){
    if (length <= 1) {
        return arr;
    }
    int mid = length/2;
    int* sorted_left = merge_sort(arr, mid);
    int* sorted_right = merge_sort(&arr[length/2], length - mid);

    int* merged = merge(sorted_left, sorted_right, mid, length - mid);
    for (int i = 0; i < length; i++) {
        arr[i] = merged[i];
    };

    return merged;
    
    

}

// time complexity of O(n)
int linear_search(int* arr, int length, int target) {
    for (int i = 0; i < length; i++) {
        if (arr[i] == target) {
            return i;
        };
    };

    return -1;
};

// time complexity of O(log_2(n))
int binary_search(int* arr, int length, int target) {
    int left = 0;
    int right = length - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == target) {
            return mid;
        }

        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    };

    return -1;
}
