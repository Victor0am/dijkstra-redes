#ifndef GRAPH_H
#define GRAPH_H

#include "./edge.h"
#include "./node.h"
#include "ratio.h"

typedef struct graph Graph;

Graph* init_graph(Node** nodes, int n, int* servers, int* monitors, int* clients, int n_edges);

double dijkstra(Graph* graph, int src, int dest);

void destroy_graph(Graph* g);

double calc_RTT(Graph* graph, int source, int destiny);

double calc_RTT_with_monitor(Graph* graph, int source, int monitor, int destiny);

double get_min_RTT_monitor(Graph* graph, int client, int server);

double RTT_ratio(double RTT, double RTT_m);

Ratio** calc_ratios(Graph* graph);

#endif