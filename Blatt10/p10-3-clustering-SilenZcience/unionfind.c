#include "unionfind.h"
#include <stdio.h>

#define CA_ID_UFC ku1heic6eePei4aigaitoagheePhuupo

/* Bitte hier nichts verändern */

void uf_init(UFNode* uf, int key) {
    uf->parent = uf; // Konvention: uf hat kein Elter falls uf->parent == uf
    uf->key = key;
    uf->size = 1; // initial enthält Partition genau ein Element
}

UFNode* uf_find(UFNode* x) {
    while(x->parent != x) { // x Wurzel falls x->parent = x
        x = x->parent;
    }

    return x;
}

void uf_print(UFNode* x) {
    printf("%d: %d", x->key, uf_find(x)->key);
}

UFNode* uf_union(UFNode* x, UFNode* y) {
    x = uf_find(x);
    y = uf_find(y);

    if(x == y) return x; // wichtig!

    // Wir möchten x in y einhängen.
    // o.B.d.A.: - y ist nicht die kleinere Partition
    //           - Falls beide Partitionen gleich groß sind:
    //             x ist Partition mit kleinerem Index
    if(y->size < x->size || (x->size == y->size && x->key > y->key) ) {
        UFNode* tmp = x; // swap x und y
        x = y;
        y = tmp;
    }

    // hänge x in y ein
    x->parent = y;
    y->size += x->size;

    return y;
}

void uf_print_all(UFNode uf[], int n) {
    printf(" / ");
    for(int i=0; i < n; ++i){
        uf_print(&uf[i]);
        printf(" / ");
    }
    printf("\n");
}
