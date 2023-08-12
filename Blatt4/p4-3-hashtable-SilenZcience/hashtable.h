#define TABLE_SIZE 23
#define EMPTY -1

struct Bird {
    int id;
    int x;
    int y;
};

typedef struct Bird Bird;

struct HashTable {
    Bird table[TABLE_SIZE];
    int n_collisions;
    int n_items;
    int a;
    int b;
    int p;
};

typedef struct HashTable HashTable;

/* Initialisiert eine leere Hashtabelle.
 *
 * Die Tabelle hat eine feste Größe von TABLE_SIZE und hasht mit der
 * Hashfunktion
 *
 *                     (a*key + b) % p
 *
 * mit den hier gegebenen Werten für a, b und p
 */
void init(HashTable* h, int a, int b, int p);

/* Fügt ein neues Element in die Hashtabelle ein. Liefert die Position des
 * eingefügten Elements in der Hashtabelle zurück, oder TABLE_SIZE wenn die
 * Hashtabelle voll ist */
unsigned int insert(HashTable* h, Bird b);

/* Liefert das Element mit Schlüssel key zurück. Ist kein Element mit Schlüssel
 * key in der Tabelle enthalten, liefert die Funktion ein Dummy-Element mit
 * id -1 und beliebigen Werten für x und y zurück
 */
Bird get(const HashTable* h, int key);

/* Gibt die Hashtabelle auf der Standardausgabe aus */
void print_table(const HashTable* h);

