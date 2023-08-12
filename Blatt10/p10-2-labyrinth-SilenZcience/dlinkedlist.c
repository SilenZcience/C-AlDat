#include "dlinkedlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define NIL ((Position) {-1, -1})

void delement_init(DListElement* e, Position key, void* data) {
    e->key = key;
    e->data = data;
    e->_next = NULL;
    e->_prev = NULL;
}

DListElement* create_delement(Position key, void* data) {
    DListElement* e = malloc(sizeof(DListElement));
    delement_init(e, key, data);
    return e;
}

void dlist_init(DList* l) {
    l->head = create_delement(NIL, NULL);
    l->tail = create_delement(NIL, NULL);
    l->head->_next = l->tail;
    l->tail->_prev = l->head;
    l->size = 0;
}

DList* create_dlist() {
    DList* l = malloc(sizeof(DList));
    dlist_init(l);
    return l;
}

void dlist_destroy(DList* l, bool free_data) {
    DListElement* cur = l->head;
    DListElement* next = cur->_next;
    while(cur != l->tail) {
        // solange cur != tail ist cur->next != null
        if(free_data) {
            free(cur->data);
        }
        free(cur);

        cur = next;
        next = next->_next;
    }

    free(l->tail);
}

// Fügt hinter e ein
DListElement* dlist_insert(DList* l, DListElement* p, Position key, void* data) {
    assert(p != l->tail);
    DListElement* e = create_delement(key, data);

    // Schritt 1
    e->_prev = p;
    e->_next = p->_next;

    // Schritt 2
    p->_next = e;
    e->_next->_prev = e;

    ++l->size;
    return e;
}

DListElement* dlist_append(DList* l, Position key, void* data) {
    return dlist_insert(l, l->tail->_prev, key, data);
}

void dlist_remove(DList* l, DListElement* e, bool free_data) {
    if(e == l->head || e == l->tail) {
        return;
    }

    // Schritt 1 mit p=e.prev
    e->_prev->_next = e->_next;

    // Schritt 2 mit s=e.next
    e->_next->_prev = e->_prev;

    if(free_data) {
        free(e->data);
    }
    free(e);

    --l->size;
}



