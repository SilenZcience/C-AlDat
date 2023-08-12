#include "mergesort.h"
#include "graph.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* Bitte hier nichts verändern! */

int imin(int a, int b) {
    return (a <= b ? a : b);
}

// Kommt e vor f?
bool less_than(const Edge* e, const Edge* f) {
    if(e->length < f->length) return true;
    if(e->length > f->length) return false;

    // beide Kanten haben die gleiche Länge
    if(e->src < f->src) return true;
    if(e->src > f->src) return false;

    // beide Kanten hanen den gleichen Startindex
    if(e->tgt < f->tgt) return true;

    // der Zielindex von f ist kleiner oder gleich dem von e
    return false;
}

/* Merge A[l,...,m] mit A[m+1,...,r].
 * Benutzt Hilfsarray H, H[l,...,r] wird überschrieben.
 *
 * Annahme: A[l,...,m] und A[m+1,...,r] sind aufsteigend sortiert
 */
void _merge(Edge A[], int l, int m, int r, Edge H[]) {
    // kopiere A in Hilfsarray
    for(int i=l; i <= r; ++i) {
        H[i] = A[i];
    }

    int out_pos = l; // Schreibposition in A
    int l_pos = l;   // Leseposition linker Teil
    int r_pos = m+1; // Leseposition rechter Teil

    // verschmelze bis eines der Teilarrays leer ist
    while(l_pos <= m && r_pos <= r) {
        if(less_than(&H[l_pos], &H[r_pos])){
            A[out_pos++] = H[l_pos++];
        }
        else {
            A[out_pos++] = H[r_pos++];
        }
    }

    // kopiere restlichen Elemente falls rechter Teil leer
    while(l_pos <= m) {
        A[out_pos++] = H[l_pos++];
    }
}

/* Bottom-up MergeSort: Mache log n Passes über A, in Pass i, merge alle Teilarrays
 * der Größe 2^i */
void merge_sort_bottom_up(Edge A[], int n) {
    Edge* H = malloc(n*sizeof(Edge)); // Hilfsarray
    for(int chunk_size=1; chunk_size < n; chunk_size *= 2) { // Arraygröße in Pass i
        // Pass i
        for(int l=0; l < n - chunk_size; l += 2*chunk_size) { // linke Grenze des Chunks
            const int m = l + chunk_size - 1;
            const int r = imin(m + chunk_size, n-1);
           
            _merge(A, l, m, r, H);
        }
    }    

    free(H);
}
