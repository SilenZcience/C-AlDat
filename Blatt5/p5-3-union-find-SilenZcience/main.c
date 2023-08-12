#include "unionfind.h"

#include <stdio.h>

int main(void) {
    int n; // #Partitionen
    int m; // #Operationen

    if(scanf("%d %d\n", &n, &m) != 2) {
        printf("Fehler: Konnte erste Zeile nicht lesen.\n");
        return 1;
    }

    // Initialisiere Union-Find-Datenstruktur
    UFNode uf[n];
    for(int i=0; i < n; ++i) {
        uf_init(&uf[i], i);
    }
    print_all(uf, n);

    // Lies Operationen; funktioniert nur mit Unix-Zeilenenden!
    for(int i=0; i < m; ++i) {
        int x;
        int y;

        // find: Zeile beginnt mit f
        if(scanf("f %d\n", &x) == 1) {
            UFNode* r = uf_find(&uf[x]);
            printf("find %d: %d\n", x, r->key);
            print_all(uf, n);
            continue;
        }

        // union: Zeile beginng mit u
        if(scanf("u %d %d\n", &x, &y) == 2) {
            UFNode* r = uf_union(&uf[x], &uf[y]);
            printf("union %d, %d: %d\n", x, y, r->key);
            print_all(uf, n);
            continue;
        }

        printf("Konnte Zeile %d nicht lesen.\n", i+2);
    }

    return 0;
}
