#include <stdio.h>
#include "adjacencyMatrix.h"
#include "dlinkedlist.h"
#include <stdbool.h>

int _read_edges(Graph *g, FILE *in);
void _print_edges(const int* edges, int size, FILE *out);


Graph* graph_create(int size){
    Graph *g = malloc(sizeof(Graph));
    graph_init(g, size);
    return g;
}


void graph_init(Graph* g, int size){
    g->size = size;
    g->nodes = malloc(size*sizeof(Node));
    for(int i = 0; i < g->size; i++){
        node_init(&(g->nodes[i]), i, size);
    }
}


void node_init(Node* n, int key, int size){
    n->key = key;
    n->edges = calloc(sizeof(int), size);
}

void graph_destroy(Graph *g){
    for(int i = 0; i < g->size; i++){
        free(g->nodes[i].edges);
    }
    free(g->nodes);
    g->nodes = NULL;
    free(g);
}


Graph* read_graph(Graph *g, FILE *in){
    if (_read_edges(g, in) < 0){
        graph_destroy(g);
        g = NULL;
    }
    return g;
}



int _read_edges(Graph *g, FILE *in){
    int start, end;
    int edge_count = 0;
    while(!feof(in)) {
        if(fscanf(in, "%d %d\n",&start, &end) == 2) {
            g->nodes[start].edges[end] = 1;
            edge_count++;
        } else if (edge_count > 0) {
            fprintf(stderr, "[FEHLER] Kante fehlerhaft.\n");
            return -1;
        }
    }
    return edge_count;
}


void print_graph(const Graph *g, FILE *out){
    for(int i = 0; i < g->size; i++){
        fprintf(out, "Knoten %d verbunden mit ", i);
        _print_edges(g->nodes[i].edges, g->size, out);
    }
}


void _print_edges(const int* edges, int size, FILE *out){
    int out_deg = 0;
    for(int i = 0; i < size; i++){
        if (edges[i]){
            fprintf(out, "%d ", i);
            out_deg++;
        }
    }
    if(out_deg == 0){
        printf("keinem Knoten");
    }

    fprintf(out, "\n");
}


