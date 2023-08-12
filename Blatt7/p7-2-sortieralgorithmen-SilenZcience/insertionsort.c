#include "insertionsort.h"

// Implementierung von InsertionSort, s. AlDat-Skript
void insertion_sort(int A[], int n){
  // Sortiere Element ein, das an Position i steht
  for(int i=1; i < n; ++i) {
    int key = A[i];
    int j = i-1;
    // Suche die Position für i in A[0,...i-1];
    // wenn A[i] vor A[j] stehen muss, schiebe A[j]
    // eine Position nach rechts um Platz für A[i]
    // zu schaffen.
    while(j >= 0 && key < A[j]){
      A[j+1] = A[j];
      --j;
    }
    // A[j+1] ist jetzt die richtige Position für A[i]
    A[j+1] = key;
  }  
}
