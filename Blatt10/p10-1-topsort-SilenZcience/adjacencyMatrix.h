#ifndef CA_ADJ_MATRIX_H_
#define CA_ADJ_MATRIX_H_

#include <stdio.h>

typedef struct Node {
    int key;
    int *edges;
} Node;


typedef struct Graph {
    int size;
    Node *nodes;
} Graph;

Graph* graph_create(int size);
void graph_init(Graph* g, int size);
void graph_destroy(Graph *g);

void node_init(Node* n, int key, int size);

Graph* read_graph(Graph* g, FILE *in);
void print_graph(const Graph *g, FILE *out);

#endif
