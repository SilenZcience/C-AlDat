#include "mergesort.h"
#include "hashmap.h"
#include "arraylist.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 255
#define RESULT_MSG "%s %d\n"

// Diese Methode ist schon fertig
char* get_next_word(FILE* f) {
    char c;
    int n_word_chars=0;
    char word_buffer[MAX_WORD_LENGTH+1];

    while(fscanf(f, "%c", &c) == 1 && n_word_chars < MAX_WORD_LENGTH) {
        if(!isalpha(c)) break;
        word_buffer[n_word_chars++] = c;
    }
    if(n_word_chars == 0) return NULL;

    word_buffer[n_word_chars++] = '\0';

    char* next_word = malloc(sizeof(char)*n_word_chars);
    strncpy(next_word, word_buffer, n_word_chars);
    return next_word;
}

void normalize(char* str) {
    for(int i = 0; i < strlen(str); i++){
        str[i] = tolower(str[i]);
    }
}

int main(void) {
    HashFunction hash_func = {4789, 1789, INT_MAX};

    HashMap hash_map;
    hashmap_init(&hash_map, hash_func);

    ArrayList arr_list;
    al_init(&arr_list);

    FILE* infile = stdin;
    while(!feof(infile)) {
        char* next_word = get_next_word(infile);

        if(next_word == NULL) {
            continue;
        }

        normalize(next_word);

        HashElement* current_element = hashmap_get(&hash_map, next_word);
        if (current_element == NULL) {
            hashmap_insert(&hash_map, next_word, 1);
            al_append(&arr_list, next_word);
        }
        else {
            ++current_element->value;
            free(next_word);
        }
    }

    merge_sort_bottom_up(arr_list.arr, arr_list.size);

    for (int i = 0; i < arr_list.size; i++) {
        char* next_word = al_get(&arr_list, i);
        fprintf(stdout, "%s %d\n", next_word, hashmap_get(&hash_map, next_word)->value);
    }
    
    for (int i = 0; i < arr_list.size; i++) {
        free(al_get(&arr_list, i));
    }
    al_destroy(&arr_list);
    hashmap_destroy(&hash_map);

    return 0;
}
