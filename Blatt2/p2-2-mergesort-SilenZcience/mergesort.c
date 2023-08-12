#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <tgmath.h>


#ifndef NDEBUGOUT
#define debug(x) x
#else
#define debug(x)
#endif


/* Gibt Elemente aus Array A[l...r] auf Standardeingabe (Konsole) aus */
void print_subarray(int A[], int l, int r) {
    for(int i=0; i < l; ++i) {
        printf(" %3s ", "");
    }

    for(int i=l; i <= r; ++i){
        printf(" %3d ", A[i]);
    }
    printf("\n");
}

/* Gibt n Elemente aus Array A auf Standardeingabe (Konsole) aus
 */
void print_array(int A[], int n){
    print_subarray(A, 0, n-1);
}

/* Testet, ob A[l...r] aufsteigend sortiert ist. */
bool is_sorted(int A[], int l, int r) {
    // CHANGED: entire logic. we cannot just return true
    // if one instance is sorted...
    for(int i=l; i < r; ++i) {
        if(A[i] > A[i+1]) {
            return false;
        }
    }

    return true;
}


/* Liest n ganze Zahlen in ein Array mit mindestens n Plätzen. 
 *
 * Rückgabe: 0 falls erfolgreich, Fehlercode > 0 sonst.
 *
 * Erwartetes Eingabeformat:
 *
 * <Anzahl Schlüssel>
 * <Schlüssel 1>
 * ...
 * <Schlüssel n>
 */
int read_array(int A[], int n) {
    int n_read=0;
    while(n_read < n) {
        int num;

        // scanf liest aus 'virtueller' Datei stdin ("Konsoleneingabe")
        if(scanf("%d", &num) < 1){ 
            // teste, ob Dateiende erreicht
            if(feof(stdin)) {
                printf("Falsches Eingabeformat. ");
                printf("%d Schlüssel erwartet, aber nur %d Schlüssel gefunden.\n", n, n_read);
                return 2;
            }
         
            // teste, ob sonstiger Fehler
            if(ferror(stdin)){
                printf("Ein-/Ausgabefehler.\n");
                return 3;
            }
         
            // ansonsten: Zeile konnte nicht geparst werden
            printf("Falsches Eingabeformat. ");
            printf("Zeile %d: Ganze Zahl erwartet.\n", n_read+2);
            return 4;
        }

        // erfolgreich gelesen
        // CHANGED: '++' missing
        A[n_read++] = num;
    }

    return 0;
}

/* Merge A[l,...,m] mit A[m+1,...,r]. 
 * Benutzt Hilfsarray H, H[l,...,r] wird überschrieben.
 *
 * Annahme: A[l,...,m] und A[m+1,...,r] sind aufsteigend sortiert */
void merge(int A[], int l, int m, int r, int H[]) {
    // kopiere A in Hilfsarray
    for(int i=l; i <= r; ++i) { 
        H[i] = A[i];
    }

    int out_pos = l; // Schreibposition in A
    int l_pos = l;   // Leseposition linker Teil
    int r_pos = m+1; // Leseposition rechter Teil

    // verschmelze bis eines der Teilarrays leer ist
    while(l_pos <= m && r_pos <= r) {
        if(H[l_pos] < H[r_pos]){
            // CHANGED: removed ++ in both indices
            A[out_pos] = H[l_pos];
            // CHANGED: added following line
            ++l_pos;
        }
        else {
            // CHANGED: removed ++ in both indices
            A[out_pos] = H[r_pos];
            // CHANGED: added following line
            ++r_pos;
        }

        // CHANGED: added following line
        ++out_pos;
    }

    // CHANGED: added following loop
    while(l_pos <= m) {
        A[out_pos] = H[l_pos];        
        ++l_pos;
        ++out_pos;
    }
}

/* ruft MergeSort auf Teilarray A[l...r] auf */
void merge_sort_(int A[], int l, int r, int H[]) {
    if(l < r) {
        const int m = (l+r) / 2;
        merge_sort_(A, l, m, H);
        merge_sort_(A, m+1, r, H);
        merge(A, l, m, r, H);
        debug(print_subarray(A, l, r));
        // maybe this is not a useful assertion because
        // we test sortness anyways in full at the end...
        assert(is_sorted(A, l, r));
    }
}

/* ruft MergeSort auf Array a mit n Elementen auf */
void merge_sort(int A[], int n) {
    int H[n]; // Hilfsarray
    // CHANGED: n -> n-1
    merge_sort_(A, 0, n-1, H);
}

int main(void) {
    int n;
    if(scanf("%d", &n) < 1) {
        printf("Falsches Eingabeformat. ");
        printf("Zeile 1: Ganze Zahl (Anzahl Schlüssel) erwartet.\n");
        return 1;
    }

    int A[n]; // Eingabearray
    int error = read_array(A, n);
    if(error > 0) {
        return error;
    }

    merge_sort(A, n);

    debug(print_array(A, n));
    assert(is_sorted(A, 0, n-1));

    return 0;
}
