#include "arraylist.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  /* Deklarieren Sie hier eine Arrayliste mit dem Namen l.
   * Initialisieren Sie die Liste passend und geben Sie
   * initialisierte Liste auf die Standardausgabe aus */

  ArrayList l;
  al_init(&l);

  /* Initiale Liste ausgeben */
  al_print(stdout, &l);

  /* Liest die Anzahl durchzuführender Operationen von der
   * Standardeingabe */
  int n_ops;
  if(scanf("%d\n",&n_ops) != 1) {
    fprintf(stderr, "Konnte Anzahl Operationen nicht lesen, stop.\n");
    return 1;
  }

  /* Liest die durchzuführenden Operationen von der Standardeingabe */
  for(int i=0; i < n_ops; ++i) {
    int key, pos;
    if(scanf("a %d\n", &key) == 1) {
      /* Rufen Sie hier die Methode append der Liste l auf, um key an das Ende
       * der Liste anzuhängen */

      al_append(&l, key);

      /* Die Liste soll nach dem Anhängen von key ausgegeben werden */
      al_print(stdout, &l);
      continue;
    }
    if(scanf("i %d %d\n", &pos, &key) == 2){
      /* Rufen Sie hier die Methode insert der Liste l auf, um key an Position
       * pos der Liste einzufügen */

      al_insert(&l, pos, key);

      /* Die Liste soll nach dem Einfügen von key ausgegeben werden */
      al_print(stdout, &l);
      continue;
    }
    if(scanf("d %d\n", &pos) == 1){
      /* Rufen Sie hier die Methode delete der Liste l auf, um den Schlüssel
       * an Position pos der Liste zu löschen. */

      al_delete(&l, pos);

      /* Die Liste soll nach dem Löschen der Position pos ausgegeben werden */
      al_print(stdout, &l);
      continue;
    }
    fprintf(stderr, "Zeile %d nicht lesbar\n", i+1);
  }

  al_destroy(&l);

  return 0;
}



