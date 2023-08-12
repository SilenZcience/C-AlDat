#include "io.h"
#include "dlinkedlist.h"

#include <stdio.h>
#include <stdlib.h>

DList* read_input(FILE* f) {
    int n=0;
    if(fscanf(f, "%d", &n) != 1) {
        fprintf(stderr, "Fehler: Konnte #Schlüssel nicht lesen.\n");
        return NULL;
    }

    DList* L = malloc(sizeof(DList));
    dlist_init(L);

    int n_read=0;
    while(n_read < n) {
        int num;

        if(fscanf(f, "%d", &num) != 1){
            // teste, ob Dateiende erreicht
            if(feof(f)) {
                fprintf(stderr, "Falsches Eingabeformat. ");
                fprintf(stderr, "%d Schlüssel erwartet, aber nur %d Schlüssel gefunden.\n", n, n_read);
                dlist_destroy(L);
                //free(L);

                return NULL;
            }

            // teste, ob sonstiger Fehler
            if(ferror(f)){
                fprintf(stderr, "Ein-/Ausgabefehler.\n");
                dlist_destroy(L);
                free(L);
                return NULL;
            }

            // ansonsten: Zeile konnte nicht geparst werden
            fprintf(stderr, "Falsches Eingabeformat. ");
            fprintf(stderr, "Zeile %d: Ganze Zahl erwartet.\n", n_read+2);
            dlist_destroy(L);
            free(L);
            return NULL;
        }

        // erfolgreich gelesen
        dlist_append(L, num);
        ++n_read;
    }

    return L;
}
