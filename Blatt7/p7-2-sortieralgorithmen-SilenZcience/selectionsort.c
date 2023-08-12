#include "selectionsort.h"

void selection_sort(int A[], int n) {
    for(int i=0; i < n-1; ++i) {
        // Suche kleinstes Element aus A[i...n-1]
        int min_pos = i;
        for(int j=i+1; j < n; ++j) {
            if(A[j] < A[min_pos]) {
                min_pos = j;
            }
        }
        int tmp = A[i];
        A[i] = A[min_pos];
        A[min_pos] = tmp;
    }
}
