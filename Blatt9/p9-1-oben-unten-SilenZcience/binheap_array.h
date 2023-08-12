#ifndef CA_BINHEAP_ARRAY_H_
#define CA_BINHEAP_ARRAY_H_

#include <stdbool.h>

void heapify_down(int heap[], int i, int size);

void heapify_up(int heap[], int i, int n);

void make_heap(int arr[], int n);

int extract_max(int heap[], int n);

void insert(int heap[], int x, int n);

bool is_heap(int arr[], int l, int r);

#endif
