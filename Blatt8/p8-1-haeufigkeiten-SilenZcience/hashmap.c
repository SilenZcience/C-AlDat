#include "hashmap.h"

#include "ilist.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

const int default_initial_capacity = 11;

HashElement* create_element(char* key, int value) {
    HashElement* h = malloc(sizeof(HashElement));
    h->key = key;
    h->value = value;

    dl_init_element(h);
    return h;
}

void hashmap_init(HashMap* h, HashFunction hash_func) {
    hashmap_init_ic(h, hash_func, default_initial_capacity);
}

void hashmap_init_ic(HashMap* h, HashFunction hash_func, int initial_capacity) {
    h->capacity = initial_capacity;
    // vielleicht blamiere ich mich hier, aber muessten diese parameter nicht vertauscht sein?
    h->table = calloc(h->capacity, sizeof(HashElement*));

    h->n_collisions = 0;
    h->n_items = 0;
    h->hash_func = hash_func;
    h->first_key = NULL;
}

void hashmap_destroy(HashMap* h) {
    HashElement* e=h->first_key;
    if(e) {
        for( ; e->next != NULL; e=e->next) {
            free(e->prev);
        }

        free(e->prev);
        free(e);
    }
    free(h->table);
    h->table = NULL;

    h->capacity = 0;
    h->n_items = 0;
}

unsigned int str2int(char* key) {
    unsigned int hash = 0;
    int R = 256;

    for (int i = 0; i < strlen(key); i++) {
        hash = R*hash + (int) key[i];
    }

    return hash;
}

unsigned int hash(const HashFunction* hash_func, char* key) {
    return (hash_func->a*str2int(key) + hash_func->b) % hash_func->p;
}

int _find_pos(HashElement** table, unsigned int size, const HashFunction* hash_func, char* key) {
    unsigned int x = hash(hash_func, key);
    for(int i=0; i < size; ++i) {
        const unsigned int probe_pos = (x+i) % size;
        if(!table[probe_pos]) {
            return probe_pos;
        }
    }

    return -1;
}

bool _hashmap_resize(HashMap* h, unsigned int new_capacity) {
    if(new_capacity < 11) return true;

    // vielleicht blamiere ich mich hier, aber muessten diese parameter nicht vertauscht sein?
    HashElement** new_table = calloc(new_capacity, sizeof(HashElement*));
    if(!new_table) {
        return false;
    }

    for(HashElement* e=h->first_key; e != NULL; e=e->next) {
        int pos = _find_pos(new_table, new_capacity, &h->hash_func, e->key);
        if(pos == -1){
            fprintf(stderr, "Fehler: Konnte %s nicht einfuegen.", e->key);
            free(new_table);
            return h->capacity;
        }
        new_table[pos] = e;
    }

    free(h->table);

    h->capacity = new_capacity;
    h->table = new_table;

    return true;
}

unsigned int hashmap_insert(HashMap* h, char* key, int value) {
    if(1.5*h->n_items >= h->capacity) _hashmap_resize(h, 2*h->capacity);

    int pos = _find_pos(h->table, h->capacity, &h->hash_func, key);
    if(pos == -1){
        fprintf(stderr, "Fehler: Konnte %s nicht einfuegen.", key);
        return h->capacity;
    }

    HashElement* new_e = create_element(key, value);
    if(h->first_key == NULL) {
        h->first_key = new_e;
    }
    else {
        new_e->next = h->first_key;
        h->first_key->prev = new_e;
        h->first_key = new_e;
    }

    h->n_items++;
    h->table[pos] = new_e;

    return pos;
}

HashElement* hashmap_get(const HashMap* h, char* key) {
    unsigned int x = hash(&h->hash_func, key);
    for(int i=0; i < h->capacity; ++i) {
        const unsigned int probe_pos = (x+i) % h->capacity;
        if(!h->table[probe_pos]) {
            return NULL;
        }

        if(strcmp(h->table[probe_pos]->key, key) == 0) {
            return h->table[probe_pos];
        }
    }

    return NULL;
}

