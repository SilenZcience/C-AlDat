#include "prioqueue.h"
#include "bintree.h"

#include <stdlib.h>
#include <stdio.h>

void pq_print(const PrioQueue *q, FILE* f) {
    fprintf(f, "Queue: ");
    bt_print_preorder(q->t, f);
    fprintf(f, "\n");
}


void pq_init(PrioQueue* q) {
    q->t = create_bintree();
}

void pq_destroy(PrioQueue* q) {
    bt_destroy(q->t);
    free(q->t);
    q->t = NULL;
}

PrioQueue* create_pq() {
    PrioQueue* q = malloc(sizeof(PrioQueue));
    pq_init(q);
    return q;
}

int pq_extract_min(PrioQueue* q) {
    int min = bt_minimum(q->t);
    bt_remove(q->t, min);
    return min;
}

int pq_extract_max(PrioQueue* q) {
    int max = bt_maximum(q->t);
    bt_remove(q->t, max);
    return max;
}

void pq_insert(PrioQueue* q, int key) {
    bt_add(q->t, key);
}

void pq_update_key(PrioQueue* q, int key, int new_key) {
    bt_remove(q->t, key);
    bt_add(q->t, new_key);
}

size_t pq_size(const PrioQueue *q) {
    return q->t->size;
}