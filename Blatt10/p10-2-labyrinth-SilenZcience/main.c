#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "labyrinth.h"
#include "dlinkedlist.h"
#include "queue.h"

#define RESULT_MSG "Von [%d, %d] nach [%d, %d] gelangt man mit %d Schritten.\n"

Position move(Position from, Position movement) {
    return (Position) {from.x + movement.x, from.y + movement.y};
}

bool position_equal(Position p, Position q) {
    return (p.x == q.x) && (p.y == q.y);
}

/* Erzeugt ein 2d-int-Array arr[0...width-1][0...height-1] auf dem Heap
 * und initialisiert es mit default_val. */
int** create_array_2d(int width, int height, int default_val) {
    int** array_2d = (int**) malloc(width * sizeof(int*));
    for (int i = 0; i < width; i++)
        array_2d[i] = (int*) malloc(height * sizeof(int));

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            array_2d[i][j] = default_val;    
    
    return array_2d;
}

/* Gegenstück zu create_array_2d; gibt den von arr belegten Speicher wieder frei */
void destroy_array_2d(int** arr, int width) {
    for (int i = 0; i < width; i++)
        free(arr[i]);

    free(arr);        
}

/* Liefert true zurück, falls Position p nicht betreten werden kann
 * (weil p außerhalb des Spielfeldes liegt oder durch eine Wand blockiert ist */
bool blocked(const Labyrinth* l, Position p) {
    // check boundaries
    if (p.x < 0 || p.x >= l->width || p.y < 0 || p.y >= l->height)
        return true;

    // check wall
    if (l->is_wall[p.x][p.y] == true)
        return true;

    return false;
}

/* Sucht einen Weg von l->start nach l->target, der möglichst wenige
 * Züge enthält. Gibt die Anzahl Züge auf diesem Weg zurück.
 * Die Funktion erzeugt keine Ausgabe */
int count_steps(const Labyrinth* l) {
    const int n_directions = 4;
    Position moves[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    Position moves_inverted[] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    int white = 0;
    int gray = 1;
    int black = 2;
    
    // default Breadth-First-Search
    int** colors = create_array_2d(l->width, l->height, white);
    int** d = create_array_2d(l->width, l->height, INT_MAX);
    int** p = create_array_2d(l->width, l->height, -1);

    DList* q = create_dlist();
    
    d[l->start.x][l->start.y] = 0;
    
    colors[l->start.x][l->start.y] = gray;
    enqueue(q, l->start);
    
    while (!is_empty(q)) {
        Position v = dequeue(q);
        for (int i = 0; i < n_directions; i++) {
            Position e_tgt = move(v, moves[i]);

            // every neighbouring cell is connected if it is not a blocked position
            if (colors[e_tgt.x][e_tgt.y] == white && !blocked(l, e_tgt)) {
                d[e_tgt.x][e_tgt.y] = d[v.x][v.y]+1;
                // instead of saving the parent Node we jsut save the orientation we took
                // to get to this node
                p[e_tgt.x][e_tgt.y] = i;

                colors[e_tgt.x][e_tgt.y] = gray;
                enqueue(q, e_tgt);
            }
        }
        colors[v.x][v.y] = black;
    }

    int steps_amount = 0;

    // using the inverted moves we can now simply backtrack our movement
    // by going in the opposite direction until we are at the start agin.
    Position backtrace = {l->target.x, l->target.y};
    while (backtrace.x != l->start.x || backtrace.y != l->start.y) {
        // if the default value (-1) is encountered, there is no valid path vom start to target
        if (p[backtrace.x][backtrace.y] == -1) {
            steps_amount = -1;
            break;
        }
        backtrace = move(backtrace, moves_inverted[p[backtrace.x][backtrace.y]]);
        steps_amount++;
    }

    dlist_destroy(q, false);
    free(q);
    destroy_array_2d(colors, l->width);
    destroy_array_2d(d, l->width);
    destroy_array_2d(p, l->width);

    return steps_amount;
}

int main(void) {
    /* Hier bitte nichts ändern :) */
    Labyrinth* l = read_labyrinth(stdin);
    if(!l) {
        fprintf(stderr, "Fehler: Konnte Eingabe nicht lesen.\n");
        return 1;
    }
    labyrinth_print(l, stdout);

    printf(RESULT_MSG, l->start.x, l->start.y, l->target.x, l->target.y, count_steps(l));
    
    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 42; j++)
    //     {
    //         printf("%d", blocked(l, (Position) {j,i}));
    //     }
    //     printf("\n");
    // }
    
    labyrinth_destroy(l);
    free(l);

    return 0;
}
