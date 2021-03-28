#ifndef GRAPH_H
#define GRAPH_H

#include "./edge.h"

typedef struct graph Graph;

Graph* init_graph(int* nodes, Edge** edges);

void destroy_graph(Graph* g);

#endif