#include "binheap_array.h"
#include <assert.h>
#include <stdio.h>

/*
 * Implementierung mit 'nacktem' Array ohne Struct.
 */


#define left(i) 2*(i) + 1
#define right(i) 2*(i) + 2
#define parent(i) (((i) - 1) / 2)

void swap(int* x, int* y);

// Dreieckstausch mit Pointer, da sonst die Werte
// außerhalb von swap nicht vertauscht werden.
void swap(int* x, int* y){
    int buf = *x;
    *x = *y;
    *y = buf;
}

// versickert den Schlüssel an Stelle i:
//   Solange Heap-Eigenschaft bei i verletzt, tausche i
// mit größerem Kind.
void heapify_down(int heap[], int i, int size) {
    // Solange A[i] linkes Kind hat
    while(left(i) < size) {
        int max_child = left(i);

        // max_child wird Index des groesseren Kindes
        if(right(i) < size && heap[right(i)] > heap[max_child]) {
            max_child = right(i);
        }

        // Heapeigenschaft?
        if(heap[max_child] < heap[i]) {
            break;
        }

        // sonst: tausche Wurzel mit groesserem Kind
        //swap(&heap[max_child], &heap[i]);
        macro_swap(heap[max_child], heap[i]);

        i = max_child;
    }
}

// tausche solange mit Elter, bis Eltern den größeren Schlüsesl enthält
void heapify_up(int heap[], int i, int n) {
    assert(i < n); // letzte gültige Position ist n-1

    while(i != 0 && heap[i] > heap[parent(i)]){
        swap(&heap[i], &heap[parent(i)]);
        i = parent(i);
    }
}

void make_heap(int arr[], int n) {
    for(int i=(n/2 -1); i >= 0; --i) {
        heapify_down(arr, i, n);
    }
}

int extract_max(int heap[], int n) {
    int max_key = heap[0];
    swap(&heap[0], &heap[n-1]);
    n -= 1;

    heapify_down(heap, 0, n);
    return max_key;
}

void insert(int heap[], int x, int n) {
    heap[n] = x;
    heapify_up(heap, n, n+1);
}

// testet, ob Array zwischen l (einschließlich) und r (ausschließlich) Heap ist
bool is_heap(int arr[], int l, int r) {
    for(int i=l; i < r; ++i) {
        if(right(i) < r && arr[right(i)] > arr[i]){
            fprintf(stderr, "Heapeigenschaft bei %d -> %d verletzt.\n", i, right(i));
            return false;
        }
        if(left(i) < r && arr[left(i)] > arr[i]){
            fprintf(stderr, "Heapeigenschaft bei %d -> %d verletzt.\n", i, left(i));
            return false;
        }
    }
    return true;
}
