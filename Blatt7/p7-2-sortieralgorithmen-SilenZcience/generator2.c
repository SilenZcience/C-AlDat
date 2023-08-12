/* 
InsertionSort:
 best case: sorted
 worst case: inverse sorted

SelectionSort:
 best case <-> worst case (all the same)

MergeSort:
 best case: sorted
 worst case: special!

QuickSort:
 !best case: special!
 worst case: sorted
*/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int* worstMergeSortInput(int n){
    if(n == 1){
        int* arr = (int*)malloc(sizeof(int));
        arr[0] = 1;
        return arr;
    }
    else{
        double n_half = n / 2.0;
        int* top = worstMergeSortInput((int)floor(n_half));
        int* bottom = worstMergeSortInput((int)ceil(n_half));
        int* result = (int*)malloc(sizeof(int) * n);
        for(int i=0; i<(int)floor(n_half); i++){
            result[i] = top[i] * 2;
        }
        for(int i=0; i<(int)ceil(n_half); i++){
            result[i + (int)floor(n_half)] = bottom[i] * 2 - 1;
        }
        free(top);
        free(bottom);
        return result;
    }
}

int main(){
    int n = 1000000;

    // generate worst case merge sort
    FILE* out_file_ptr = fopen("worstMergeSort.in", "w");
    int* arr = worstMergeSortInput(n);
    fprintf(out_file_ptr, "%d\n", n);
    for(int i=0; i<n; i++){
        fprintf(out_file_ptr, "%d\n", arr[i]);
    }
    free(arr);
    fclose(out_file_ptr);

    return 0;
}