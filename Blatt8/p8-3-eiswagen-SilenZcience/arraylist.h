#ifndef CA_ARRAYLIST_H_
#define CA_ARRAYLIST_H_

// import Junction struct
#include "eiswagen.h"

#include <stdio.h>

typedef struct ArrayList {
  // change array to Junction type
  Junction* arr;      // eigentliche Liste
  int size;      // #Elemente in Liste
  int capacity;  // Größe von arr
} ArrayList;

void al_init(ArrayList* l);

void al_destroy(ArrayList* l);

// change method signature
int al_append(ArrayList* l, Junction key);

void al_print(FILE* f, const ArrayList* l);

void al_print_with_streets(FILE* f, const ArrayList* l);


#endif
