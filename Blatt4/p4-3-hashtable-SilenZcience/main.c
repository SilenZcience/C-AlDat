#include "hashtable.h"

#include <stdio.h>

int main(void) {
    int n_birds, n_queries;
    if(scanf("%d %d", &n_birds, &n_queries) != 2) {
        printf("Fehler: Zeile der Form <n> <m> erwartet.");
        return 1;
    }

    int a, b, p;
    if(scanf("%d %d %d", &a, &b, &p) != 3) {
        printf("Fehler: Zeile der Form <a> <b> <p> erwartet.");
        return 2;
    }

    // declare and init the hashtable
    HashTable h;
    init(&h, a, b, p);
    
    for(int i=0; i < n_birds; ++i) {
        Bird b;
        if(scanf("%d %d %d", &b.id, &b.x, &b.y) != 3) {
            printf("Fehler: Konnte Vogel %d nicht lesen.\n", i+1);
            return 3;
        }
        if(insert(&h, b) == TABLE_SIZE) {
            printf("Fehler: Hashtabelle voll\n");
            return 4;
        }
        print_table(&h);
    }

    for(int i=0; i < n_queries; ++i) {
        int query;
        if(scanf("%d", &query) != 1) {
            printf("Fehler: Konnte Query %d nicht lesen.\n", i+1);
            return 4;
        }
        Bird b = get(&h, query);
        if(b.id == -1) {
            printf("Vogel %d nicht beobachtet.\n", query);
        }
        else {
            printf("Vogel %d bei (%d, %d) beobachtet.\n", query, b.x, b.y);
        }
    }

    printf("%d Kollisionen beim Einfügen.\n", h.n_collisions);

    return 0;
}
