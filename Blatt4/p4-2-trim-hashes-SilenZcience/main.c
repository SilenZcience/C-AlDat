#include "trim.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // Lies n = Anzahl Zeichen im Eingabestring
  int n;
  if(scanf("%d\n", &n) != 1) {
    printf("Fehler: Konnte nicht 'Anzahl Zeichen' lesen.\n");
    return 1;
  }

  // lies Eingabe
  char input[n+1];
  for(int i=0; i < n; ++i) {
    if(scanf("%c", &input[i]) != 1) {
      printf("Konnte nicht %d Zeichen lesen.\n", n);
      return 2;
    }
  }
  input[n] = '\0';

  printf("'%s'\n", trim(input));

  return 0;
}
