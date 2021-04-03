#ifndef GRAPH_H
#define GRAPH_H

#include "./edge.h"
#include "./node.h"

typedef struct graph Graph;

Graph* init_graph(Node** nodes, Edge** edges, double* w, int** csm);

void destroy_graph(Graph* g);

#endif