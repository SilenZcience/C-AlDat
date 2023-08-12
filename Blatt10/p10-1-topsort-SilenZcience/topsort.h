#ifndef CA_DFS_TOPSORT_H_
#define CA_DFS_TOPSORT_H_

#include <stdbool.h>
#include "dlinkedlist.h"


#ifdef LISTE
#include "adjacencyList.h"
#endif
#ifdef MATRIX
#include "adjacencyMatrix.h"
#endif

typedef enum Color {
    WHITE, GRAY, BLACK
} Color;

typedef struct DFSData {
    Color *color;
    int *discovery;
    int *finish;
    int size;
    int time;
} DFSData;

DFSData* create_dfsdata(int size);
void dfsdata_init(DFSData *data, int size);
void dfsdata_destroy(DFSData *data);

void top_sort(Graph *g);
bool top_sort_dfs(Graph *g, int v, DFSData* dfs_data, DList *s);
#endif
