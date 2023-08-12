#include "dlinkedlist.h"

#include <stdio.h>

int main(void) {
    FILE* f = stdin;

    int n=0;
    if(fscanf(f, "%d", &n) != 1) {
        fprintf(stderr, "Fehler: Konnte #Schlüssel nicht lesen.\n");
        return 1;
    }

    DListElement* elems[n];

    int m=0;
    if(fscanf(f, "%d", &m) != 1) {
        fprintf(stderr, "Fehler: Konnte #Ops nicht lesen.\n");
        return 2;
    }

    DList* L = malloc(sizeof(DList));
    dlist_init(L);
    for(int i=0; i < n; ++i) {
        elems[i] = dlist_append(L, i);
    }

    dlist_print(L, stdout);

    int n_read=0;
    while(n_read < m) {
        int x, y;

        if(fscanf(f, "%d %d", &x, &y) != 2){
            // teste, ob Dateiende erreicht
            if(feof(f)) {
                fprintf(stderr, "Falsches Eingabeformat. ");
                fprintf(stderr, "%d Schlüssel erwartet, aber nur %d Schlüssel gefunden.\n", n, n_read);
                dlist_destroy(L);
                free(L);

                return 3;
            }

            // teste, ob sonstiger Fehler
            if(ferror(f)){
                fprintf(stderr, "Ein-/Ausgabefehler.\n");
                dlist_destroy(L);
                free(L);
                return 4;
            }

            // ansonsten: Zeile konnte nicht geparst werden
            fprintf(stderr, "Falsches Eingabeformat. ");
            fprintf(stderr, "Zeile %d: Zwei ganze Zahlen erwartet.\n", n_read+2);
            dlist_destroy(L);
            free(L);
            return 5;
        }

        // erfolgreich gelesen
        dlist_move(L, elems[x], elems[y]);
        dlist_print(L, stdout);
        ++n_read;
    }

    dlist_destroy(L);

    return 0;
}
