#include "io.h"

#include <stdio.h>
#include <stdlib.h>

void print_subarray(FILE* f, int A[], int l, int r) {
    for(int i=0; i < l; ++i) {
        fprintf(f, " %3s ", "");
    }

    for(int i=l; i <= r; ++i){
        fprintf(f, " %3d ", A[i]);
    }
    fprintf(f, "\n");
}

void print_array(FILE* f, int A[], int n){
    print_subarray(f, A, 0, n-1);
}

int* read_input(FILE* f, int* n) {
    *n=0;
    if(fscanf(f, "%d", n) != 1) {
        fprintf(stderr, "Fehler: Konnte #Schlüssel nicht lesen.\n");
        return NULL;
    }

    int* arr = malloc(*n*sizeof(int));

    int n_read=0;
    while(n_read < *n) {
        int num;

        if(fscanf(f, "%d", &num) != 1){
            // teste, ob Dateiende erreicht
            if(feof(f)) {
                fprintf(stderr, "Falsches Eingabeformat. ");
                fprintf(stderr, "%d Schlüssel erwartet, aber nur %d Schlüssel gefunden.\n", *n, n_read);
                free(arr);
                return NULL;
            }

            // teste, ob sonstiger Fehler
            if(ferror(f)){
                fprintf(stderr, "Ein-/Ausgabefehler.\n");
                free(arr);
                return NULL;
            }

            // ansonsten: Zeile konnte nicht geparst werden
            fprintf(stderr, "Falsches Eingabeformat. ");
            fprintf(stderr, "Zeile %d: Ganze Zahl erwartet.\n", n_read+2);
            free(arr);
            return NULL;
        }

        // erfolgreich gelesen
        arr[n_read++] = num;
    }

    return arr;
}
