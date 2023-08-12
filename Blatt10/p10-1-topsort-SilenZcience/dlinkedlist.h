#ifndef CA_DLINKED_LIST_H_
#define CA_DLINKED_LIST_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define NIL -1
#define dlist_forall(e, l) for(DListElement* e=l->head->_next; e != l->tail; e=e->_next)
#define dlist_rev_forall(e, l) for(DListElement* e=l->tail->_prev; e != l->head; e=e->_prev)

typedef struct DListElement DListElement;
typedef struct DList DList;

typedef struct DListElement {
    int key;
    void* data;
    DListElement* _next;
    DListElement* _prev;
} DListElement;

typedef struct DList {
    DListElement* head;
    DListElement* tail;
    size_t size;
} DList;

void delement_init(DListElement* e, int key, void* data);

DListElement* create_delement(int key, void* data);

void dlist_init(DList* l);

DList* create_dlist();

void dlist_destroy(DList* l, bool free_data);

void dlist_print(const DList* l, FILE* f);

// Fügt hinter e ein
DListElement* dlist_insert(DList* l, DListElement* p, int key, void* data);

// Liefert TAIL zurück, falls key nicht enthalten
DListElement* dlist_find(const DList* l, int key);

DListElement* dlist_append(DList* l, int key, void* data);

void dlist_remove(DList* l, DListElement* e, bool free_data);

#endif
