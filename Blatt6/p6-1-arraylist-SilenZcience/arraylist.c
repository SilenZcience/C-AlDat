#include "arraylist.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Initiale Kapazität der Arrayliste */
const int initial_capacity = 11;

int _resize(ArrayList* l, int new_capacity);

/* Konstruktur; initialisiert l als leere Liste
 * mit einem Array der Größe initial_capacity.*/
void al_init(ArrayList* l) {
  l->arr = (int*) malloc(sizeof(int)*initial_capacity);
  l->size = 0;
  l->capacity = initial_capacity;
}

/* Destruktor; gibt sämtlichen von der Arrayliste
 * dynamisch allokierten Speicher wieder frei */
void al_destroy(ArrayList* l) {
  free(l->arr);
  l->arr = NULL;
}

/* Hängt den Schlüssel key an das Ende der
 * Arrayliste an. Wenn die aktuelle Kapazität
 * der Arrayliste nicht ausreicht, wird die Kapazität
 * der Arrayliste verdoppelt. */
int al_append(ArrayList* l, int key) {
  // unklar, was der rückgabewert von typ 'int' sein soll?!
  // hier verwendet als boolean, ob die methode erfolgreich
  // war oder nicht.
  if (l->size >= l->capacity) {
    if (!_resize(l, 2*l->capacity)) {
      return 0;
    }
  }

  l->arr[l->size] = key;
  l->size++;
  
  return 1;
}

/* Fügt den Schlüssel key an Position pos ein.
 * Schiebt dazu die Elemente l->arr[pos,...,l->size-1]
 * um eine Position nach rechts. Wenn die aktuelle
 * Kapazität der Arrayliste nicht ausreicht,
 * wird die Kapazität der Arrayliste verdoppelt.
 *
 * Wenn pos == l->size ist die Funktion äquivalent
 * zu al_append. Es muss 0 <= pos <= l->size gelten.
 */
int al_insert(ArrayList* l, int pos, int key) {
  // unklar, was der rückgabewert von typ 'int' sein soll?!
  // hier verwendet als boolean, ob die methode erfolgreich
  // war oder nicht.
  if (pos < 0 || pos > l->size) {
    fprintf(stderr, "Invalid position in al_insert.\n");
    return 0;
  }
  if (l->size >= l->capacity) {
    // wenn das resizen nicht funktioniert hat, wird
    // in dem Fall auch das appenden nicht funktionieren.
    if (!_resize(l, 2*l->capacity)) {
      return 0;
    }
  }

  // verschiebe vorhandene einträge und setze key.
  for (int i = l->size; i > pos; i--) {
    l->arr[i] = l->arr[i-1];
  }
  l->arr[pos] = key;
  
  l->size++;

  return 1;
}

/* Löscht den Schlüssel an Position pos und
 * schiebt die Elemente l->arr[pos+1,...,l->size-1]
 * um eine Position nach links. Falls nach der
 * Operation die Kapazität mehr als dreimal so groß
 * wie die Anzahl der Elemente in der Liste ist,
 * wird die Kapazität der Liste halbiert.
 * Die Kapazität der Liste wird niemals unter 11
 * reduziert. Es muss 0 <= pos < l->size gelten.
 */
void al_delete(ArrayList* l, int pos) {
  if (pos < 0 || pos > l->size) {
    fprintf(stderr, "Invalid position in al_delete.\n");
    return;
  }

  // verschiebe vorhandene einträge.
  // key an pos wird damit überschrieben.
  for (int i = pos; i < l->size-1; i++) {
    l->arr[i] = l->arr[i+1];
  }
  l->size--;
  
  if (l->capacity >= 3*l->size) {
    _resize(l, l->capacity/2);
  }
}

/* Hilfsfunktion: Ändert die Kapazität der Liste
 * auf new_capacity; new_capacity kann größer
 * oder kleiner als die aktuelle Kapazität sein.
 *
 * Die Kapazität der Liste soll immer mindestens
 * 11 sein; daher soll die Funktion nichts tun,
 * wenn new_capacity < 11 ist.
 */
int _resize(ArrayList* l, int new_capacity) {
  // unklar, was der rückgabewert von typ 'int' sein soll?!
  // hier verwendet als boolean, ob die methode erfolgreich
  // war oder nicht.
  if (new_capacity < initial_capacity) {
    fprintf(stderr, "Error at shrinking al in _resize.\n");
    return 0;
  }

  // teste mit einem temporären array, ob der speicher allokiert werden kann.
  int* new_arr = (int*) realloc(l->arr, sizeof(int)*new_capacity);
  if (!new_arr) {
    fprintf(stderr, "Error at enlarging al in _resize.\n");
    return 0;
  }

  // wenn es keine fehler gab, können die neuen Werte
  // gesetzt werden
  l->arr = new_arr;
  l->capacity = new_capacity;

  return 1;
}

/* Gibt die Liste in die Datei f aus
 * Verändern Sie diese Funktion bitte nicht :)
 */
void al_print(FILE* f, const ArrayList* l) {
  fprintf(f, "[ ");
  for(int i=0; i < l->size; ++i) {
    fprintf(f, "%3d ", l->arr[i]);
  }
  for(int i=l->size; i < l->capacity; ++i) {
    fprintf(f, "%3s ", "");
  }
  fprintf(f, " ][ size: %3d capacity: %3d ]\n", l->size, l->capacity);
}
