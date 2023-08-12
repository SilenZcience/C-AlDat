#include "project.h"

// TODO passen Sie die Struct so an, dass der Heap Project* enthält
typedef struct BinHeap {
    Project* heap;
    int size; // Anzahl Elemente im Heap
    int capacity; // Groesse des Arrays
} BinHeap;

// TODO passen Sie die Funktionssignatur an
void heap_init(BinHeap* h);

// TODO passen Sie die Funktionssignatur an
void heap_destroy(BinHeap* h);

// TODO passen Sie die Funktionssignatur an
int heap_insert(BinHeap* h, Project x);

// TODO passen Sie die Funktionssignatur an
Project heap_extract_max(BinHeap* h);
