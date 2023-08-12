#include "bintree.h"

#include <stdio.h>
#include <stdlib.h>

/* Diese Datei bitte nicht verändern */

int main(void) {
    BinTree* t = create_bintree();

    FILE* f = stdin;
    while(!feof(f)) {
        int key;
        char cmd;

        if(fscanf(f, "%c %d\n", &cmd, &key) < 1) {
            fprintf(stderr, "Fehlerhafte Zeile.\n");
            return 1;
        }

        switch(cmd) {
            case 'a':
                bt_add(t, key);
                break;

            case 'r':
                bt_rotate_right(bt_find_link(t, key));
                break;

            case 'l':
                bt_rotate_left(bt_find_link(t, key));
                break;

            case 'p':
                bt_print_as_dot(t, stdout);
                break;

            default:
                fprintf(stderr, "Fehler: Unbekannter Befehl '%c'.\n", cmd);

                bt_destroy(t);
                free(t);

                return 4;
        }
    }

    bt_destroy(t);
    free(t);

    return 0;
}
