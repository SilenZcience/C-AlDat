#ifndef LABYRINTH_H_
#define LABYRINTH_H_

#include <stdbool.h>
#include <stdio.h>

typedef struct Position Position;
typedef struct Labyrinth Labyrinth;

// Eine Position im Labyrinth
struct Position {
  int x; // Spalte
  int y; // Zeile
};

// Ein Labyrinth
struct Labyrinth {
    bool** is_wall; // Adressierung ab 0: walls[spalten_idx][zeilen_idx],

    int width;  // Anzahl Spalten
    int height; // Anzahl Zeilen

    Position start;
    Position target;
};

// Erzeugt und initialisiert ein Labyrinth
Labyrinth* create_labyrinth(int width, int height);

// Gibt den Heap-Speicher frei, auf den Member-Variablen von l zeigen
void labyrinth_destroy(Labyrinth* l);

// Liest ein Labyrinth aus einer Datei f
Labyrinth* read_labyrinth(FILE* f);

// Gibt ein Labyrinth in die Datei f aus
void labyrinth_print(const Labyrinth* l, FILE* f);

#endif
