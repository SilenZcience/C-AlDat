#include "io.h"
#include "quicksort.h"
#include "mergesort.h"
#include "selectionsort.h"
#include "insertionsort.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argn, char** args) {
    if(argn < 2) {
        fprintf(stderr, "Fehler: Parameter <algorithmus> [n] mit Parameter aus {i, m, q, s} erwartet.\n");
        fprintf(stderr, "   i: insertion sort.\n");
        fprintf(stderr, "   m: (bottom up) merge sort.\n");
        fprintf(stderr, "   q: quick sort.\n");
        fprintf(stderr, "   s: selection sort.\n");
        return 1;
    }

    int forced_n = -1;
    if(argn > 2){
        forced_n = atoi(args[2]);
    }

    int n=0;
    int* input = read_input(stdin, &n);

    if(forced_n >= 0 && n != forced_n) {
        fprintf(stderr, "Testfall enthält nicht die richtige Anzahl an Schlüsseln: Genau %d Schlüssel erwartet.\n", forced_n);
        return 3;
    }

    switch(args[1][0]) {
        case 'i':
            insertion_sort(input, n);
            break;

        case 'm':
            merge_sort_bottom_up(input, n);
            break;

        case 'q':
            quick_sort(input, n);
            break;

        case 's':
            selection_sort(input, n);
            break;


        default:
            fprintf(stderr, "Fehler: Ungültige Algorithmenauswahl '%c'.\n", args[1][0]);
            return 2;
    }

//    print_array(stdout, input, n);
    free(input);
    input=NULL;


    return 0;
}
