#ifndef CA_MERGESORT_H_
#define CA_MERGESORT_H_

#include "graph.h"

/* Bottom-up MergeSort: Sortiert das Kantenarray A nach
 * Kantenlängen. Kanten mit gleiche Länge werden lexikografisch
 * nach Start-/Zielindex sortiert. */
void merge_sort_bottom_up(Edge A[], int n);

void _merge(Edge A[], int l, int m, int r, Edge H[]);


#endif
