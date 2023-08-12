#include <stdbool.h>

// h(x) = (ax + b) % p
struct HashFunction {
    int a;
    int b;
    int p;
};

typedef struct HashFunction HashFunction;

struct HashElement {
    char* key;
    int value;

    struct HashElement* next; // fuer die implizite Liste
    struct HashElement* prev;
};

typedef struct HashElement HashElement;

struct HashMap {
    HashElement** table;
    int n_collisions;
    unsigned int capacity;
    int n_items;
    HashElement* first_key;
    HashFunction hash_func;
};

typedef struct HashMap HashMap;

/* Initialisiert eine leere Hashtabelle.
 *
 * Die Tabelle hat eine feste Größe von TABLE_SIZE und hasht mit der
 * Hashfunktion
 *
 *                     (a*key + b) % p
 *
 * mit den hier gegebenen Werten für a, b und p
 */
void hashmap_init(HashMap* h, HashFunction hash_func);
void hashmap_init_ic(HashMap* h, HashFunction hash_func, int initial_cap);

/* Gibt Speicher frei, den das HashMap allokiert hat */
void hashmap_destroy(HashMap* h);

/* Fügt ein neues Element in die Hashtabelle ein. Liefert die Position des
 * eingefügten Elements in der Hashtabelle zurück */
unsigned int hashmap_insert(HashMap* h, char* key, int value);

/* Liefert das Element mit Schlüssel key zurück. Ist kein Element mit Schlüssel
 * key in der Tabelle enthalten, liefert die Funktion NULL zurueck.
 */
HashElement* hashmap_get(const HashMap* h, char* key);

