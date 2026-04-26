#include "algos.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
   int arr[] = {-1, -9, -2, -7, -5, -3, -12, -24, -1};
   for (int i = 0; i < sizeof(arr)/sizeof(int); i++) {
      printf("%d ", arr[i]);
   };
   printf("\n");
   int* sorted_arr = quicksort(arr, sizeof(arr)/sizeof(int));
   for (int j = 0; j < sizeof(arr)/sizeof(int); j++) {
      printf("%d ", sorted_arr[j]);
   }

}