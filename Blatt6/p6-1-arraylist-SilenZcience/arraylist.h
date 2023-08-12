#ifndef CA_ARRAYLIST_H_
#define CA_ARRAYLIST_H_

#include <stdio.h>

typedef struct ArrayList {
  int* arr;      // eigentliche Liste
  int size;      // #Elemente in Liste
  int capacity;  // Größe von arr
} ArrayList;

/* Spezifikation s. arraylist.c */
void al_init(ArrayList* l);

/* Spezifikation s. arraylist.c */
void al_destroy(ArrayList* l);

/* Spezifikation s. arraylist.c */
int al_append(ArrayList* l, int key);

/* Spezifikation s. arraylist.c */
int al_insert(ArrayList* l, int pos, int key);

/* Spezifikation s. arraylist.c */
void al_delete(ArrayList* l, int pos);

/* Spezifikation s. arraylist.c */
void al_print(FILE* f, const ArrayList* l);

#endif
