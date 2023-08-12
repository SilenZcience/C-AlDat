#ifndef CA_GRAPH_H_
#define CA_GRAPH_H_

#include "unionfind.h"

#include <stdio.h>

typedef struct Edge {
    unsigned int src;
    unsigned int tgt;
    size_t length;
} Edge;

Edge* read_edges(FILE* f, int* n_nodes, int* n_edges, int* n_clusters);

void print_edge(FILE* f, Edge e);

void print_edges(FILE* f, Edge* adj, int n_edges);

void print_clusters(FILE* f, UFNode* clusters, int n_points, int n_clusters);
#endif
