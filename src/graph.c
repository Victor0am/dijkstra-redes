#include "./graph.h"

#include <stdlib.h>

struct graph {
    Node** nodes;
    Edge** edges;
    double* w;
    int* csm[3];
};

Graph* init_graph(Node** nodes, Edge** edges, double* w, int** csm) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));

    graph->nodes = nodes;
    graph->edges = edges;
    graph->w = w;
    for (int i = 0; i < 3; i++)
        graph->csm[0] = csm;

    return graph;
}

void destroy_graph(Graph* g) {
}