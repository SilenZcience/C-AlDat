#include "quicksort.h"

#include <stdbool.h>

void swap(int* i, int* j) {
    int buf=*i;
    *i=*j;
    *j=buf;
}

int partition(int* A, int l, int r) {
    int i=l+1;
    int j=r;

    while(true) {
        while(i < r && A[i] <= A[l]) ++i;
        while(j > l && A[j] >= A[l]) --j;

        if(i >= j) break;

        swap(&A[i], &A[j]);

        ++i;
        --j;
    }

    swap(&A[l], &A[j]);

    return j;
}

void _quick_sort(int* A, int l, int r) {
    if(l >= r) return;

    int p = partition(A, l, r);
    _quick_sort(A, l, p-1);
    _quick_sort(A, p+1, r);
}

void quick_sort(int* A, int n) {
    _quick_sort(A, 0, n-1);
}
