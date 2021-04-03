#ifndef GRAPH_H
#define GRAPH_H

#include "./edge.h"
#include "./node.h"

typedef struct graph Graph;

Graph* init_graph(Node** nodes, int n, int* servers, int* monitors, int* clients);

double dijkstra(Graph* graph, int src, int dest, int n_edges);

void destroy_graph(Graph* g);

#endif