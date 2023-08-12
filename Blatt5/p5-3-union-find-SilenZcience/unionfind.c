#include "unionfind.h"
#include <stdio.h>

void uf_init(UFNode* uf, int key) {
    uf->parent = uf; // Konvention: uf hat kein Elter falls uf->parent == uf
    uf->key = key;
    uf->size = 1; // initial enthält Partition genau ein Element
}

UFNode* uf_find(UFNode* x) {
    // climb parent references until it points to itself
    while (x->parent != x) {
        x = x->parent;
    }
    return x;
}

UFNode* uf_union(UFNode* x, UFNode* y) {
    // find parent representatives for both Nodes
    x = uf_find(x);
    y = uf_find(y);

    // Stop if both Nodes are in the same Partition already.
    if (x == y) {
        return x;
    }

    // swap pointers such that |x| > |y|
    // in case of |x| = |y|, swap pointers such that x.key > y.key
    if (x->size < y->size || (x->size == y->size && x->key < y->key)) {
        UFNode* tmp = x;
        x = y;
        y = tmp;
    }
    
    // append y-tree onto x-tree
    y->parent = x;
    x->size += y->size;

    return x;
}

void uf_print(const UFNode* x) {
    printf("%d: %d", x->key, x->parent->key); // parent ist niemals null
}

void print_all(UFNode uf[], int n) {
    printf(" / ");
    for(int i=0; i < n; ++i){
        uf_print(&uf[i]);
        printf(" / ");
    }
    printf("\n");
}
