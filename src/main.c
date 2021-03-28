#include <stdio.h>
#include <stdlib.h>

#include "./edge.h"

int main(int argc, char** argv) {
    int n_monitors, n_clients, n_servers, n_knots, n_edges, i;
    FILE* reader = fopen(argv[1], "r");
    FILE* writer = fopen(argv[2], "w");

    fscanf(reader, "%d %d", &n_knots, &n_edges);
    fscanf(reader, "%d %d %d", &n_servers, &n_clients, &n_monitors);

    int* servers = (int*)malloc(sizeof(int) * n_servers);
    for (i = 0; i < n_servers; i++) {
        fscanf(reader, "%d", &servers[i]);
    }

    int* clients = (int*)malloc(sizeof(int) * n_clients);
    for (i = 0; i < n_clients; i++) {
        fscanf(reader, "%d", &clients[i]);
    }

    int* monitors = (int*)malloc(sizeof(int) * n_monitors);
    for (i = 0; i < n_monitors; i++) {
        fscanf(reader, "%d", &monitors[i]);
    }

    Edge** edges = (Edge**)malloc(sizeof(Edge*) * n_edges);
    int ori, des;
    double weight;

    for (i = 0; i < n_edges; i++) {
        fscanf(reader, "%d %d %lf", &ori, &des, &weight);
        edges[i] = init_edge(ori, des, weight);
    }

    free(servers);
    free(clients);
    free(monitors);
    destroy_edge_vector(edges, n_edges);
    fclose(reader);
    fclose(writer);

    return 0;
}