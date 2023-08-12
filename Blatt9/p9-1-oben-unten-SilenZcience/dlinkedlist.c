#include "dlinkedlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

#define NIL -1

void delement_init(DListElement* e, int key) {
    e->key = key;
    e->_next = NULL;
    e->_prev = NULL;
}

DListElement* create_delement(int key) {
    DListElement* e = malloc(sizeof(DListElement));
    delement_init(e, key);
    return e;
}

void dlist_init(DList* l) {
    l->head = create_delement(INT_MAX);
    l->tail = create_delement(INT_MAX);
    l->head->_next = l->tail;
    l->tail->_prev = l->head;
    l->size = 0;
}

DList* create_dlist() {
    DList* l = malloc(sizeof(DList));
    dlist_init(l);
    return l;
}

void dlist_destroy(DList* l) {
    DListElement* cur = l->head;
    DListElement* next = cur->_next;
    while(cur != l->tail) {
        free(cur);

        cur = next;
        next = next->_next;
    }

    free(l->tail);
}

void dlist_print(const DList* l, FILE* f) {
    DListElement* cur = l->head->_next;
    fprintf(f, "HEAD -> ");
    while(cur != l->tail) {
        fprintf(f, "%d -> ", cur->key);
        cur = cur->_next;
    }
    fprintf(f, "TAIL\n");
}

// Fügt hinter e ein
DListElement* dlist_insert(DList* l, DListElement* p, int key) {
    assert(p != l->tail);
    DListElement* e = create_delement(key);

    // Schritt 1
    e->_prev = p;
    e->_next = p->_next;

    // Schritt 2
    p->_next = e;
    e->_next->_prev = e;

    ++l->size;
    return e;
}

// Liefert TAIL zurück, falls key nicht enthalten
DListElement* dlist_find(const DList* l, int key) {
    DListElement* cur = l->head->_next;
    while(cur != l->tail && cur->key != key) {
        cur = cur->_next;
    }

    return cur;
}

DListElement* dlist_append(DList* l, int key) {
    return dlist_insert(l, l->tail->_prev, key);
}

void dlist_remove(DList* l, DListElement* e) {
    if(e == l->head || e == l->tail) {
        return;
    }

    // Schritt 1 mit p=e.prev
    e->_prev->_next = e->_next;

    // Schritt 2 mit s=e.next
    e->_next->_prev = e->_prev;

    free(e);
    --l->size;
}
