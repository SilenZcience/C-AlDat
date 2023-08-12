#include "arraylist.h"

#include <stdio.h>
#include <stdlib.h>

/* Initiale Kapazität der Arrayliste */
const int initial_capacity = 11;

/* Hilfsfunktion: Ändert die Kapazität der Liste
 * auf new_capacity; new_capacity kann größer
 * oder kleiner als die aktuelle Kapazität sein. */
int _al_resize(ArrayList* l, int new_capacity);

void al_init(ArrayList* l) {
  // changed allocated size to Junction struct
  l->arr = malloc(initial_capacity*sizeof(Junction));
  l->size = 0;
  l->capacity = initial_capacity;
}

void al_destroy(ArrayList* l) {
  free(l->arr);
  l->arr = NULL;
}

// changed parameter from int to Junction struct
int al_append(ArrayList* l, Junction key) {
  if(l->size == l->capacity) {
    if(!_al_resize(l, 2*l->capacity)) {
      return 0;
    }
  }

  l->arr[l->size++] = key;
  return 1;
}

// TODO Gegebenenfalls anpassen!
int _al_resize(ArrayList* l, int new_capacity) {
  // replaced const by global var
  if(new_capacity < initial_capacity){
    return 1;
  }
  
  if(new_capacity < l->capacity){
    // Verkleinerung wird fuer die Aufgabe nicht benoetigt und muss nicht implementiert werden.
    printf("ACHTUNG: Korrekte Speicherfreigabe bei Listenverkleinerung ist nicht implementiert.\n");
  }

  // allocate Junction structs instead of ints
  Junction* new_mem = realloc(l->arr, sizeof(Junction)*new_capacity);
  if(new_mem) {
    l->capacity = new_capacity;
    l->arr = new_mem;
    return 1;
  }
  else {
    fprintf(stderr, "Nicht genügend Speicher.\n");
    return 0;
  }
}

void al_print(FILE* f, const ArrayList* l) {
  fprintf(f, "[ ");
  for(int i=0; i < l->size; ++i) {
    fprintf(f, "%3d ", l->arr[i].ID);
  }
  for(int i=l->size; i < l->capacity; ++i) {
    fprintf(f, "%3s ", "");
  }
  fprintf(f, " ][ size: %3d capacity: %3d ]\n", l->size, l->capacity);
}

void al_print_with_streets(FILE* f, const ArrayList* l) {
    printf("********************************************\n");
  for(int i=0; i < l->size; ++i) {
    fprintf(f, "%i   | ", l->arr[i].ID);
    dlist_print(l->arr[i].streets, stdout);
  }
}
