#ifndef TOKENIZER_H_
#define TOKENIZER_H_

/* Verändern Sie diese Datei nicht :) */

/* Spezifikation s. tokenizer.c */
char* substring(char* str, int l, int r);

/* Spezifikation s. tokenizer.c */
char** tokenize(char* str, char sep, int* n_tokens);

/* Spezifikation s. tokenizer.c */
void free_tokens(char** tokens, int n);

#endif
