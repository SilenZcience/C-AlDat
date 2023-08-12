#include "binheap.h"
#include "binheap_array.h"

#include <stdio.h>
#include <stdlib.h>

const int initial_capacity=11;

int heap_resize(BinHeap* h, int new_capacity);

void heap_init(BinHeap* h) {
     h->size = 0;
     h->capacity = initial_capacity;
     // malloc Projects instead of ints
     h->heap = malloc(h->capacity*sizeof(Project));
}

void heap_destroy(BinHeap* h) {
    free(h->heap);
    h->heap = NULL;
}

int heap_insert(BinHeap* h, Project x) {
    if(h->size == h->capacity) {
        if(!heap_resize(h, 2*h->capacity)) {
            fprintf(stderr, "Konnte Heap nicht vergrößern.\n");
            return 0;
        }
    }

    insert(h->heap, x, h->size);
    ++h->size;

    return 1;
}

Project heap_extract_max(BinHeap* h) {
    Project max_key = extract_max(h->heap, h->size);
     --h->size;

    if(3*h->size < h->capacity) {
        heap_resize(h, 0.5*h->capacity);
    }

    return max_key;
}

int heap_resize(BinHeap* h, int new_capacity) {
    if(new_capacity < 11) return 1;

    // malloc Projects instead of ints
    Project* new_mem = realloc(h->heap, new_capacity*sizeof(Project));
    if(new_mem) {
        h->capacity = new_capacity;
        h->heap = new_mem;
        return 1;
    }

    fprintf(stderr, "Nicht genuegend Speicher.\n");
    return 0;
}
