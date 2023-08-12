#include "mergesort.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int imin(int a, int b) {
    return (a <= b ? a : b);
}

/* Merge A[l,...,m] mit A[m+1,...,r]. 
 * Benutzt Hilfsarray H, H[l,...,r] wird überschrieben.
 *
 * Annahme: A[l,...,m] und A[m+1,...,r] sind aufsteigend sortiert
 */
void _merge(char** A, int l, int m, int r, char** H) {
    // kopiere A in Hilfsarray
    for(int i=l; i <= r; ++i) { 
        H[i] = A[i];
    }

    int out_pos = l; // Schreibposition in A
    int l_pos = l;   // Leseposition linker Teil
    int r_pos = m+1; // Leseposition rechter Teil

    // verschmelze bis eines der Teilarrays leer ist
    while(l_pos <= m && r_pos <= r) {
        if(strcmp(H[l_pos], H[r_pos]) < 0){
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
void merge_sort_bottom_up(char** A, int n) {
    char** H = malloc(n*sizeof(char*)); // Hilfsarray
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
