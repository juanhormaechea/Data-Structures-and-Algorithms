#include "algos.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
   int arr[] = {1,7,2,2,5,2,5,2,1,5,8};
   for (int i = 0; i < sizeof(arr)/sizeof(int); i++) {
      printf("%d ", arr[i]);
   };
   printf("\n");
   int* sorted_arr = merge_sort(arr, sizeof(arr)/sizeof(int));
   for (int j = 0; j < sizeof(arr)/sizeof(int); j++) {
      printf("%d ", sorted_arr[j]);
   }
   printf("\n");
    for (int i = 0; i < sizeof(arr)/sizeof(int); i++) {
      printf("%d ", arr[i]);
   };

   
   return 0;

}