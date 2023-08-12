#ifndef CA_DLINKED_LIST_H_
#define CA_DLINKED_LIST_H_

#include "labyrinth.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct DListElement DListElement;
typedef struct DList DList;

typedef struct DListElement {
    Position key;
    void* data;
    DListElement* _next;
    DListElement* _prev;
} DListElement;

typedef struct DList {
    DListElement* head;
    DListElement* tail;
    size_t size;
} DList;

void delement_init(DListElement* e, Position key, void* data);

DListElement* create_delement(Position key, void* data);

void dlist_init(DList* l);

DList* create_dlist();

void dlist_destroy(DList* l, bool free_data);

// Fügt hinter e ein
DListElement* dlist_insert(DList* l, DListElement* p, Position key, void* data);

DListElement* dlist_append(DList* l, Position key, void* data);

void dlist_remove(DList* l, DListElement* e, bool free_data);

#endif
