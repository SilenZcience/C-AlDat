#ifndef CA_TREE_QUEUE
#define CA_TREE_QUEUE

/* Diese Datei bitte nicht verändern */

#include "bintree.h"

typedef struct PrioQueue PrioQueue;

struct PrioQueue {
    BinTree* t;
};

// Gibt den zugrundeliegenden Baum in Pre-Order aus
void pq_print(const PrioQueue* q, FILE* f);

// TODO implementieren Sie alle folgenden Methoden in prioqueue.c

/* initialisiert die Attribute von q */
void pq_init(PrioQueue* q);

/* gibt den Speicher frei, der von q allokiert wurde */
void pq_destroy(PrioQueue* q);

/* allokiert Speicher für q und initialisiert die Attribute der
 * allokierten Instanz von q. Gibt die Instanz zurück.
 * Der aufrufende Code muss die Instanz freigeben */
PrioQueue* create_pq();

/* Gibt den kleinsten Schlüssel aus q zurück und entfernt ihn aus q. */
int pq_extract_min(PrioQueue* q);

/* Gibt den größten Schlüssel aus q zurück und entfernt ihn aus q. */
int pq_extract_max(PrioQueue* q);

/* Fügt einen neuen Schlüssel key in q ein. */
void pq_insert(PrioQueue* q, int key);

/* Ändert den Schlüssel key auf new_key */
void pq_update_key(PrioQueue* q, int key, int new_key);

/* Gibt die Anzahl der Schlüssel in q zurück */
size_t pq_size(const PrioQueue *q);

#endif
