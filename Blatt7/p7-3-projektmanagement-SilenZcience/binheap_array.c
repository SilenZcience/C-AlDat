#include "binheap_array.h"
#include <assert.h>
#include <stdio.h>

#define left(i) 2*(i) + 1
#define right(i) 2*(i) + 2
#define parent(i) (((i) - 1) / 2)

// Dreieckstausch mit Pointer, da sonst die Werte
// außerhalb von swap nicht vertauscht werden.
// simply replaced int by Project
void swap(Project* x, Project* y){
    Project buf = *x;
    *x = *y;
    *y = buf;
}

// versickert den Schlüssel an Stelle i:
//   Solange Heap-Eigenschaft bei i verletzt, tausche i mit größerem Kind.
void heapify_down(Project heap[], int i, int size) {
    // Solange A[i] linkes Kind hat
    while(left(i) < size) {
        int max_child = left(i);

        // max_child wird Index des groesseren Kindes
        if(right(i) < size && heap[right(i)].value > heap[max_child].value) {
            max_child = right(i);
        }

        // Heapeigenschaft?
        if(heap[max_child].value < heap[i].value) {
            break;
        }

        // sonst: tausche Wurzel mit groesserem Kind
        //swap(&heap[max_child], &heap[i]);
        swap(&heap[max_child], &heap[i]);

        i = max_child;
    }
}

// tausche solange mit Elter, bis Eltern den größeren Schlüssel enthält
void heapify_up(Project heap[], int i, int n) {
    assert(i < n); // letzte gültige Position ist n-1

    while(i != 0 && heap[i].value > heap[parent(i)].value){
        swap(&heap[i], &heap[parent(i)]);
        i = parent(i);
    }
}

// we noe extract a whole Project instead of an int
Project extract_max(Project heap[], int n) {
    Project max_key = heap[0];
    swap(&heap[0], &heap[n-1]);
    n -= 1;

    heapify_down(heap, 0, n);
    return max_key;
}

void insert(Project heap[], Project x, int n) {
    heap[n] = x;
    heapify_up(heap, n, n+1);
}
