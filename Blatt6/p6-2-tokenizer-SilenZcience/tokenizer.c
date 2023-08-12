#include "tokenizer.h"

#include <stdio.h>
#include <stdlib.h>

/* Liefert den Teilstring str[l,...,r] als Kopie in einem neuen Array der
 * Länge r-l+1 zurück.
 *
 * Der Aufrufer ist dafür verantwortlich, die Kopie zu löschen.
 */
char* substring(char* str, int l, int r) {
  int n = r-l+1;
  // allocate enough memory to also place the null-byte.
  char* substring = calloc(sizeof(char), n+1);

  // simply copy the cutout of the original string
  for (int i = l; i <= r; i++) {
    substring[i-l] = str[i];
  }
  substring[n] = '\0';

  return substring;
}

/* Zerteilt einen String an jedem Vorkommen des Separators sep in Teilstrings.
 * Liefert die Teilstrings in einem Array und die Länge dieses Arrays in
 * *n_tokens zurück.
 *
 * Die zurückgelieferten Teilstrings sind Kopien des ursprünglichen Strings.
 *
 * Der Aufrufer ist dafür verantwortlich, das zurückgelieferte Array und alle
 * Teilstrings zu löschen.
 */
char** tokenize(char* str, char sep, int* n_tokens) {
  *n_tokens = 0;
  // initialize values to express to substring position
  int pos_start = 0;
  int pos_end = 0;
  
  char** subs = (char**) malloc(0);

  while (1) {
    // if the seperator or the null-byte is encountered, we
    // reallocate memory for another substring-pointer, which we use
    // to point to the new allocated substring from the 'substring' method
    if (str[pos_end] == sep || str[pos_end] == '\0') {
      (*n_tokens)++;
      subs = (char**) realloc(subs, sizeof(char*) * (*n_tokens));
      subs[*n_tokens-1] = substring(str, pos_start, pos_end-1);
      pos_start = pos_end + 1;
    }
    // if we encounter the null-byte we also break from the loop
    // because the original string has reached it's end.
    if (str[pos_end] == '\0') {
      break;
    }
    pos_end++;
  }
  
  return subs;
}

/* Löscht alle in tokens enthaltenen Teilstrings und das Array tokens selbst */
void free_tokens(char** tokens, int n) {
  for (int i = 0; i < n; i++) {
    free(tokens[i]);
  }
  free(tokens);
  tokens = NULL;
}

