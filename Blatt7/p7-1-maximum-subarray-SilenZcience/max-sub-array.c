#include <stdio.h>
#include <stdlib.h>

int max_sub_array(const int* arr, int n) {
    // Algorithmus B:
    int* m = malloc(n*sizeof(int));
    int* r = malloc(n*sizeof(int));

    // check if the array has any values at all
    if (n == 0) {
        return -1;
    }
    

    m[0] = arr[0];
    r[0] = arr[0];

    for (int i = 1; i < n; i++) {
        // max{A[k + 1], A[k + 1] + Rk}:
        r[i] = (arr[i] > (arr[i] + r[i-1])) ? arr[i] : (arr[i] + r[i-1]);
        // max{Mk, Rk+1}:
        m[i] = (m[i-1] > r[i]) ? m[i-1] : r[i];
    }
    

    return m[n-1];
}

/* Unterhalb dieser Zeile muss nichts verändert werden */

int* read_input(FILE* f, int* n) {
    *n = 0;
    if(fscanf(f, "%d", n) != 1 || n < 0) {
        fprintf(stderr, "[FEHLER] Zeile 1: Natürliche Zahl erwartet.\n");
        return NULL;
    }

    int* arr = malloc(*n*sizeof(int));
    for(int i=0; i < *n; ++i) {
        if(fscanf(f, "%d", &arr[i]) != 1) {
            fprintf(stderr, "[FEHLER] Zeile %d: Zahl erwartet.\n", i+2);
            free(arr);
            return NULL;
        }
    }

    return arr;
}

int main(void) {
    int n;
    int* input = read_input(stdin, &n);

    printf("Max: %d\n", max_sub_array(input, n));

    free(input);

    return 0;
}
