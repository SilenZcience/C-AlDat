#include "bintree.h"

#include <stdio.h>
#include <stdlib.h>

/* Diese Datei bitte nicht verändern */

BinTree* read_tree(FILE* f) {
    BinTree* t = create_bintree();
    while(!feof(f)) {
        int x;
        if(fscanf(f, "%d\n", &x) != 1) {
            fprintf(stderr, "Fehlerhafte Zeile.\n");
            free(t);
            return NULL;
        }
        bt_add(t, x);
    }

    return t;
}

int main(int argn, char** argv) {
    if(argn < 2){
        fprintf(stderr, "Parameter erwartet:\n");
        fprintf(stderr, "\tm: Minimum:\n");
        fprintf(stderr, "\tM: Maximum:\n");

        return 1;
    }

    BinTree* t = read_tree(stdin);

    switch(argv[1][0]) {
        case 'm':
            printf("Min: %d\n", bt_minimum(t));
            break;

        case 'M':
            printf("Max: %d\n", bt_maximum(t));
            break;

        default:
            fprintf(stderr, "Unbekannter Parameter '%c'\n", argv[1][0]);
    }

    bt_destroy(t);
    free(t);

    return 0;
}
