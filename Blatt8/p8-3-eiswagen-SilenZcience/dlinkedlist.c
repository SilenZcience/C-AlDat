#include "dlinkedlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

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
    // removed unnecessary arguments
    l->head = create_delement(NIL);
    l->tail = create_delement(NIL);
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
        // solange cur != tail ist cur->next != null
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

// changed method signature to receive just the key instead of an element
DListElement* dlist_insert(DList* l, int key) {
    DListElement* cur = l->head->_next;
    DListElement* e = create_delement(key);

    // search for the element to insert the new key after
    while (cur != l->tail) {
        if (cur->key > e->key) {
            break;
        }
        
        cur = cur->_next;
    }
    cur = cur->_prev;

    // insert the element 
    cur->_next->_prev = e;
    e->_next = cur->_next;
    cur->_next = e;
    e->_prev = cur;

    ++l->size;
    return e;
}

// changed method signature to receive just the key instead of an element
void dlist_remove(DList* l, int key) {
    DListElement* cur = l->head->_next;

    // loop through the datastructure until we find the element
    while (cur != l->tail) {
        // if found we delete it by changing the pointers of the
        // elements before and behind it, also free the mem
        if (cur->key == key) {
            cur->_prev->_next = cur->_next;
            cur->_next->_prev = cur->_prev;

            free(cur);          
            break;
        }
        cur = cur->_next;
    }

    --l->size;
}
