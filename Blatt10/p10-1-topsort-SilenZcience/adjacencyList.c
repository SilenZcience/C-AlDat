#include <stdio.h>
#include "adjacencyList.h"
#include "dlinkedlist.h"
#include <stdbool.h>

int _read_edges(Graph *g, FILE *in);
void _print_edges(const DList* edges, FILE *out);


Graph* graph_create(int size){
    Graph *g = malloc(sizeof(Graph));
    graph_init(g, size);
    return g;
}


void graph_init(Graph* g, int size){
    g->size = size;
    g->nodes = malloc(size*sizeof(Node));
    for(int i = 0; i < g->size; i++){
        node_init(&(g->nodes[i]), i);
    }
}


void node_init(Node* n, int key){
    n->key = key;
    n->edges = create_dlist();
}

void graph_destroy(Graph *g){
    for(int i = 0; i < g->size; i++){
        dlist_destroy(g->nodes[i].edges, false);
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
            dlist_append(g->nodes[start].edges, end, NULL);
            edge_count++;
        } else if (edge_count > 0){
            fprintf(stderr, "[FEHLER] Kante fehlerhaft.\n");
            return -1;
        }
    }
    return edge_count;
}


void print_graph(const Graph *g, FILE *out){
    for(int i = 0; i < g->size; i++){
        fprintf(out, "Knoten %d verbunden mit ", i);
        _print_edges(g->nodes[i].edges, out);
    }
}


void _print_edges(const DList* edges, FILE *out){
    DListElement* cur = edges->head->_next;
    if(cur == edges->tail){
        printf("keinem Knoten");
    }
    while(cur != edges->tail) {
        fprintf(out, "%d ", cur->key);
        cur = cur->_next;
    }
    fprintf(out, "\n");
}


