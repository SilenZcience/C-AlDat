#ifndef CA_BINHEAP_ARRAY_H_
#define CA_BINHEAP_ARRAY_H_

#include "project.h"
#include <stdbool.h>

// TODO passen Sie die Funktionssignatur an
void heapify_down(Project heap[], int i, int size);

// TODO passen Sie die Funktionssignatur an
void heapify_up(Project heap[], int i, int n);

// TODO passen Sie die Funktionssignatur an
Project extract_max(Project heap[], int n);

// TODO passen Sie die Funktionssignatur an
void insert(Project heap[], Project x, int n);

#endif
