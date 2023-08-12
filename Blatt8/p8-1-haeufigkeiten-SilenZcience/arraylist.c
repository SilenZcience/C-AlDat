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
  l->arr = malloc(initial_capacity*sizeof(char*));
  l->size = 0;
  l->capacity = initial_capacity;
}

void al_destroy(ArrayList* l) {
  free(l->arr);
  l->arr = NULL;
}

int al_append(ArrayList* l, char* key) {
  if(l->size == l->capacity) {
    if(!_al_resize(l, 2*l->capacity)) {
      return 0;
    }
  }

  l->arr[l->size++] = key;
  return 1;
}

int al_insert(ArrayList* l, int pos, char* key) {
  if(l->size == l->capacity) {
    if(!_al_resize(l, 2*l->capacity)){
      fprintf(stderr, "Konnte Arrayliste nicht vergrößern.\n");
      return 0;
    }
  }

  for(int i=l->size; i > pos; --i) {
    l->arr[i] = l->arr[i-1];
  }
  l->arr[pos] = key;
  ++l->size;

  return 1;
}

char* al_delete(ArrayList* l, int pos) {
  char* e = l->arr[pos];
  for(int i=pos; i < l->size; ++i) {
    l->arr[i] = l->arr[i+1];
  }

  --l->size;

  if(3*l->size < l->capacity) {
    _al_resize(l, 0.5*l->capacity);
  }

  return e;
}

int _al_resize(ArrayList* l, int new_capacity) {
  if(new_capacity < 11){
    return 1;
  }

  char** new_mem = realloc(l->arr, sizeof(char*)*new_capacity);
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

/* Liefert das Element an Position pos zurück */
char* al_get(ArrayList* l, int pos) {
  return l->arr[pos];
}

void al_print(FILE* f, const ArrayList* l) {
  fprintf(f, "[ ");
  for(int i=0; i < l->size; ++i) {
    fprintf(f, "%3s ", l->arr[i]);
  }
  for(int i=l->size; i < l->capacity; ++i) {
    fprintf(f, "%3s ", "");
  }
  fprintf(f, " ][ size: %3d capacity: %3d ]\n", l->size, l->capacity);
}
