#include "tokenizer.h"

#include <stdlib.h>
#include <stdio.h>

/*
 *
 * Verändern Sie diese Datei nicht  :)
 *
 */
int main(void) {
  /* Liest die Eingabe ein */
  int n;
  if(scanf("%d\n", &n) != 1){
    fprintf(stderr, "Konnte Zeile 1 (#Zeichen) nicht lesen.\n");
    return 1;
  }

  char* input = calloc(sizeof(char), n+1);
  for(int i=0; i < n; ++i) {
    if(scanf("%c", &input[i]) != 1) {
      fprintf(stderr, "Konnte Zeichen %d nicht lesen.\n", i);
      return 2;
    }
  }
  input[n] = '\0';

  /* Zerteile Eingabestring an jedem Vorkommen von ',' */
  int n_tokens;
  char** tokens = tokenize(input, ',', &n_tokens);
  free(input);
  input = NULL;

  /* Gib Teilstrings aus */
  for(int i=0; i < n_tokens; ++i) {
    printf("'%s'\n", tokens[i]);
  }

  /* Speicher wieder freigeben */
  free_tokens(tokens, n_tokens);

  return 0;
}
