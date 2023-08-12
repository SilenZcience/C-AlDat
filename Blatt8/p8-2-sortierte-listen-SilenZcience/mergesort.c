#include "mergesort.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* Merge L[l,...,m-1] mit L[m,...,r].
 *
 * Annahme: L[l,...,m-1] und L[m,...,r] sind aufsteigend sortiert
 */
void _merge(DList* L, DListElement* l, DListElement* m, DListElement* r) {
    DListElement* l_pos = l;
    DListElement* r_pos = m;
    
    // da wir wissen, dass l <= m <= r, können wir zur abbruchbedingung
    // ungleichheit verwenden, da wir uns nur nach rechts bewegen.
    // wir haben schließlich keine indizes für die pointer positionen in der liste.
    while (l_pos != r_pos && r_pos != r) {
        if (l_pos->key < r_pos->key) {
            l_pos = l_pos->_next;
            continue;
        }

        DListElement* tmp = r_pos;
        r_pos = r_pos->_next;

        dlist_move(L, tmp, l_pos->_prev);
    }
}

/* Bottom-up MergeSort: Mache log n Passes über L, in Pass i, merge alle Teillisten
 * der Größe 2^i */
void merge_sort_bottom_up(DList* L) {
    for(int chunk_size=1; chunk_size < L->size; chunk_size *= 2) { // Teil-Liste in Pass i
        printf("-- Pass %d\n", chunk_size);
        dlist_print(L, stdout);
        DListElement* l = L->head->_next;
        while(l != L->tail) {
            DListElement* m = l;
            for(int i=0; i < chunk_size - 1 && m != L->tail; ++i) m=m->_next;

            // kein erster / zweiter Chunk vorhanden
            if(m == L->tail || m->_next == L->tail) break;

            DListElement* r = m;
            for(int i=0; i < chunk_size && r->_next != L->tail; ++i) r = r->_next;

            DListElement* next_l = r->_next;

            _merge(L, l, m->_next, r->_next);
            l=next_l;
        }
        dlist_print(L, stdout);
    }
}
