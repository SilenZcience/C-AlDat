#ifndef CA_UNIONFIND_H_
#define CA_UNIONFIND_H_

typedef struct UFNode UFNode;

/* Ein Element der UF-Datenstruktur */
typedef struct UFNode {
    UFNode* parent;
    int key;
    int size;
} UFNode;

/* Initialisiere ein UF-Element */
void uf_init(UFNode* uf, int key);

/* Liefert den Repräsentanten der Partition zurück, die x enthält */
UFNode* uf_find(UFNode* x);

/* Vereinigt die Partion die x enthält mit der Partitition, die y enthält.
 *
 * Der Repräsentant der größeren Partition wird Repräsentant der Vereinigung.
 * Falls beide Partitionen gleich groß sind, wird der Repräsentant der
 * Partition mit dem kleineren Schlüssel Repräsentant der Vereinigung.
 *
 * Gibt den Repräsentanten der Vereinigung zurück.
 */
UFNode* uf_union(UFNode* x, UFNode* y);

/* Gibt die Union-Find-Datenstruktur aus */
void print_all(UFNode uf[], int n);

#endif
