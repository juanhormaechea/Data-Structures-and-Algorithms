#include "algos.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
   int arr[] = {64, 34, 25, 12, 22, 11, 90, 5};
   for (int i = 0; i < sizeof(arr)/sizeof(int); i++) {
      printf("%d ", arr[i]);
   };
   printf("\n");

}