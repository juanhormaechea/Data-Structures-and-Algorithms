#include "algos.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
   int arr[] = {84, 39, 12, 95, 56, 23, 78, 41, 67, 4,
    91, 18, 52, 33, 89, 7, 64, 29, 75, 11,
    48, 82, 15, 96, 59, 21, 73, 38, 66, 2};
   for (int i = 0; i < sizeof(arr)/sizeof(int); i++) {
      printf("%d ", arr[i]);
   };
   printf("\n");
   int* sorted_arr = quicksort(arr, sizeof(arr)/sizeof(int));
   for (int j = 0; j < sizeof(arr)/sizeof(int); j++) {
      printf("%d ", arr[j]);
   }

}