/* ************************************************************************** *
 * Ändern Sie in dieser Datei nur die markierten Methoden, welche Sie ganz    *
 * unten in dieser Datei finden.                                              *
 * ***************************************************************************/

#include "topsort.h"
#include "stack.h"
#include "dlinkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define KREIS "Der Graph ist nicht kreisfrei.\n"

#ifdef LISTE
#include "adjacencyList.h"
#endif
#ifdef MATRIX
#include "adjacencyMatrix.h"
#endif

int read_size(FILE *in);

int main(void){
    int size = read_size(stdin);
    if (size <= 0){
        return 1;
    }
    Graph *g = graph_create(size);
    g = read_graph(g, stdin);
    // Sie können diese Zeile zu Debuggingzwecken einkommentieren.
    // print_graph(g, stdout);
    top_sort(g);
    graph_destroy(g);
    g = NULL;
}

DFSData* create_dfsdata(int size){
    DFSData *data = malloc(sizeof(DFSData));
    dfsdata_init(data, size);
    return data;
}


void dfsdata_init(DFSData *data, int size){
    data->size = size;
    data->time = 0;
    data->color = malloc(size*sizeof(Color));
    data->discovery = malloc(size*sizeof(int));
    data->finish = malloc(size*sizeof(int));
    for(int i = 0; i < size; i++){
        data->color[i] = WHITE;
        data->discovery[i] = -1;
        data->finish[i] = -1;
    }
}


void dfsdata_destroy(DFSData *data){
    free(data->color);
    free(data->discovery);
    free(data->finish);
    free(data);
}


int read_size(FILE *in){
    int size;
    if(fscanf(in, "%d", &size)!= 1){
        fprintf(stderr, "[FEHLER] Graphgröße konnte nicht gelesen werden.\n");
        return -1;
    } else if (size <= 0){
        fprintf(stderr, "[FEHLER] Graphgröße ist ungültig (<= 0).\n");
    }
    return size;
}


void top_sort(Graph *g){
    DFSData* d = create_dfsdata(g->size);

    for (int v = 0; v < g->size; v++) {
        d->color[v] = WHITE;
        d->discovery[v] = -1;
        d->finish[v] = -1;
    }

    d->time = 0;
    // The "Stack" is implemented as an DList
    DList* s = create_dlist();
    bool no_error = true;
    
    for (int v = 0; v < g->size; v++) {
        if (d->color[v] == WHITE) {
            // we have to carry out every error, no matter the depth of recursion
            // therefor we always return a boolean if the method call was succesfull
            no_error = top_sort_dfs(g, v, d, s);
            // if the method had an error, we can stop with the iteration
            if (!no_error)
                break;
        }
    }

    // if we encountered no errors, we can print the stack, otherwise
    // we display the error message
    if (no_error) {
        while (!is_empty(s)) {
            fprintf(stdout, "%d\n", pop(s));
        }
    }
    else {
        fprintf(stdout, KREIS);
    }

    dlist_destroy(s, true);
    dfsdata_destroy(d);
}


bool top_sort_dfs(Graph *g, int v, DFSData* dfs_data, DList *s){
    dfs_data->discovery[v] = dfs_data->time;
    ++dfs_data->time;
    dfs_data->color[v] = GRAY;
    
    DListElement* current = g->nodes[v].edges->head->_next;
    while (current != g->nodes[v].edges->tail) {
        if (dfs_data->color[current->key] == GRAY) {
            // on error: return false
            return false;
        }
        if (dfs_data->color[current->key] == WHITE) {
            // if the recursion call had an error, we have to carry it outwards.
            if (!top_sort_dfs(g, current->key, dfs_data, s)) {
                return false;
            }
        }

        current = current->_next;
    }
    
    dfs_data->color[v] = BLACK;
    push(s, v);
    dfs_data->finish[v] = dfs_data->time;
    ++dfs_data->time;

    return true;
}
