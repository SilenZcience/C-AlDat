#ifndef CA_ADJ_LIST_H_
#define CA_ADJ_LIST_H_

#include "dlinkedlist.h"


typedef struct Node {
    int key;
    DList *edges;
} Node;


typedef struct Graph {
    int size;
    Node *nodes;
} Graph;

Graph* graph_create(int size);
void graph_init(Graph* g, int size);
void graph_destroy(Graph *g);

void node_init(Node* n, int key);

Graph* read_graph(Graph* g, FILE *in);
void print_graph(const Graph *g, FILE *out);
#endif
