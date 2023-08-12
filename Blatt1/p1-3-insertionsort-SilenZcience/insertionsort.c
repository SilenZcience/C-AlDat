#include <stdio.h>

void insertion_sort(int A[], int n) {
  int currentValue;
  int j;
  for (int i = 1; i < n; i++) {
    currentValue = A[i];
    j = i - 1;
    /*
    for each element currentValue from the Array
    we check every element to the left of it and
    shift these values to the right, such that
    the element currentValue is in the correct
    place within the sorted subarray of length i.
    */
    while (A[j] > currentValue && j >= 0) {
        A[j + 1] = A[j];
        j = j - 1;
    }
    A[j + 1] = currentValue;
  }
}

int main(void) {
  // read the length of the array in n
  int n; scanf("%d", &n);
  
  // declare array of size n and read n lines from stdin
  // to fill the array
  int A[n];
  for (int i = 0; i < n; i++) {
    scanf("%d", &A[i]);
  }
  
  // call the insertion_sort and print the array
  insertion_sort(A, n);
  for (int i = 0; i < n; i++) {
    printf("%d ", A[i]);
  }
  printf("\n");

  return 0;
}

