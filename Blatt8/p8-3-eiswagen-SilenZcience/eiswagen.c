#include <stdbool.h>
#include "eiswagen.h"
#include "dlinkedlist.h"
#include "arraylist.h"

//Legt Kreuzung mit leerer Straßenliste an.
void junction_init(Junction *j, int ID){
    j->ID = ID;
    j->streets = malloc(sizeof(DList));
    // initiale the DList
    dlist_init(j->streets);
}

void junction_destroy(Junction *j) {
    // free all mem
    dlist_destroy(j->streets);
    free(j->streets);
    j->streets = NULL;
}

// Wenn alle Kreuzungen eingelesen sind, soll die ArrayList einmal mit der
// Funktion al_print ausgegeben werden.
bool _read_junctions(FILE* f, ArrayList *junctions){
    // read the number of junction inputs
    int n;
    if (fscanf(f, "%d\n", &n) != 1) {
        return false;
    }
    
    // read all junctions
    int id;
    for (int i = 0; i < n; i++) {
        if (fscanf(f, "%d\n", &id) != 1) {
            return false;
        }
        // create new junction by the read id and append it in the al
        Junction new;
        junction_init(&new, id);
        al_append(junctions, new);
    }
    
    al_print(stdout, junctions);

    return true;
}


bool _read_streets(FILE *f, ArrayList *junctions){
    int start;
    int stop;
    char mode;

    while(!feof(f)) {
        if(fscanf(f, "%c %d %d\n",&mode, &start, &stop) == 3) {
            // loop through the al to find the correct DList
            DList* reachable;
            for (int i = 0; i < junctions->size; i++) {
                if (junctions->arr[i].ID == start) {
                    reachable = junctions->arr[i].streets;
                    break;
                }
            }
            
            if(mode == 'a'){
                // insert a new element
                dlist_insert(reachable, stop);

            } else if (mode == 'r'){
                // remove an element
                dlist_remove(reachable, stop);
            }
            else {
                fprintf(stderr, "Einlesefehler: Unbekannter Modus %c.\n", mode);
                return false;
            }
        } else {
            fprintf(stderr, "Fehler. Fehlerhafte Zeile.\n");
            return false;
        }
        // print
        al_print_with_streets(stdout, junctions);
    }
    return true;
}

int main(void){
    FILE* f = stdin;

    ArrayList *junctions = malloc(sizeof(ArrayList));
    al_init(junctions);
    if (!_read_junctions(f, junctions)){
        fprintf(stderr, "Fehler beim Einlesen der Kreuzungen.\n");
        return 1;
    }

    if (!_read_streets(f, junctions)){
        fprintf(stderr, "Fehler beim Einlesen der Straßen.\n");
        return 1;
    }

    for(int i=0; i < junctions->size; ++i) {
        junction_destroy(&junctions->arr[i]);
    }

    al_destroy(junctions);
    free(junctions);
    junctions=NULL;

    return 0;
}


