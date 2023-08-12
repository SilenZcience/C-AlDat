#include "hashtable.h"

#include <stdio.h>
#include <stdbool.h>

unsigned int hash(const HashTable* h, int key) {
    // use the given hash algorithm and size the value
    // to the current TABLE_SIZE using the modulo operator.
    return ((h->a * key + h->b) % h->p) % TABLE_SIZE;
}

bool is_pos_empty(const HashTable* h, unsigned int pos) {
    return h->table[pos].id == EMPTY;
}

void init(HashTable* h, int a, int b, int p) {
    // initialise all table-values as empty.
    for (int i = 0; i < TABLE_SIZE; i++) {
        h->table[i].id = EMPTY;
    }
    // initiliase collisions and items as zero.
    h->n_collisions = 0;
    h->n_items = 0;
    // initiliase the given values used for the hash-algorithm.
    h->a = a;
    h->b = b;
    h->p = p;
}

unsigned int insert(HashTable* h, Bird b) {
    // if the table is full we cannot insert another
    // value, therefor we return TABLE_SIZE.
    if (h->n_items == TABLE_SIZE) {
        return TABLE_SIZE;
    }
    
    // we start by trying to insert at the index
    // given by our hash-algorithm.
    unsigned int hashIndex = hash(h, b.id);
    // we use linear probing if the position is already in use.
    while (h->table[hashIndex].id != EMPTY) {
        ++hashIndex;
        hashIndex %= TABLE_SIZE;
        // also we increment our collision-counter.
        h->n_collisions++;
    }

    // on successfull insertion we increment our item-counter.
    h->n_items++;
    
    // insert the value b and return it's position.
    h->table[hashIndex] = b;
    return hashIndex;
}

Bird get(const HashTable* h, int key) {
    // calculate the starting position within the table.
    unsigned int hashIndex = hash(h, key);

    // by default the bird has the id -1, in case
    // it is not found within the table.
    Bird bird;
    bird.id = -1;

    // we use linear probing in case the position is already in use
    // by another value.
    // we need to keep track of our amount of tries, otherwise we could
    // iterate over the table endlessly, if it is full without having the
    // desired value. (not neccessary to pass all tests ...)
    int anzahlVersuche = 0;
    while (h->table[hashIndex].id != EMPTY && anzahlVersuche < TABLE_SIZE) {
        // if we have found the desired value we copy it's
        // values to our bird variable and exit the loop.
        if (h->table[hashIndex].id == key) {
            bird.id = key;
            bird.x = h->table[hashIndex].x;
            bird.y = h->table[hashIndex].y;
            break;
        }
        
        ++hashIndex;
        hashIndex %= TABLE_SIZE;
        ++anzahlVersuche;
    }

    return bird;
}

void print_table(const HashTable* h) {
    printf("#");
    for(int i=0; i < TABLE_SIZE; ++i) {
        printf("  %03d#", i);
    }
    printf("\n");

    printf("#");
    for(int i=0; i < TABLE_SIZE; ++i) {
        if(is_pos_empty(h, i)){
            printf("%5s#", "");
        }
        else {
            printf("%5d#", h->table[i].id);
        }
    }
    printf("\n\n");
}
