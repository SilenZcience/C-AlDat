#include "prioqueue.h"

/* Diese Datei bitte nicht verändern */

#include <stdlib.h>

int main(void) {
    PrioQueue* q = create_pq();

    FILE* f = stdin;

    while(!feof(f)) {
        int key, arg;
        char cmd;
        if(fscanf(f, "%c %d %d\n", &cmd, &key, &arg) == 0) {
            fprintf(stderr, "Fehlerhafte Zeile.\n");
            return 1;
        }

        switch(cmd) {
            case 'a':
                pq_insert(q, key);
                break;

            case 'm':
                if(pq_size(q) == 0) {
                    fprintf(stderr, "Fehler: extract-min aufgerufen, aber Queue ist leer.\n");
                    pq_destroy(q);
                    free(q);
                    return 2;
                }
                printf("Min: %d\n", pq_extract_min(q));
                break;

            case 'M':
                if(pq_size(q) == 0) {
                    fprintf(stderr, "Fehler: extract-max aufgerufen, aber Queue ist leer.\n");
                    pq_destroy(q);
                    free(q);
                    return 3;
                }

                printf("Max: %d\n", pq_extract_max(q));
                break;

            case 'u':
                pq_update_key(q, key, arg);
                break;

            default:
                fprintf(stderr, "Fehler: Unbekannter Befehl '%c'.\n", cmd);
                pq_destroy(q);
                free(q);
                return 4;
        }
        pq_print(q, stdout);
    }

    pq_destroy(q);
    free(q);

    return 0;
}
