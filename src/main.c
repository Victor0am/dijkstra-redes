#include <stdio.h>
#include <stdlib.h>

#include "./edge.h"
#include "./node.h"

int* read_create_array(FILE* fp, int n) {
    int* array = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d", &array[i]);
    }

    return array;
}

int main(int argc, char** argv) {
    int n_monitors, n_clients, n_servers, n_knots, n_edges, i;
    FILE* reader = fopen(argv[1], "r");
    FILE* writer = fopen(argv[2], "w");

    fscanf(reader, "%d %d", &n_knots, &n_edges);
    fscanf(reader, "%d %d %d", &n_servers, &n_clients, &n_monitors);

    int* servers = read_create_array(reader, n_servers);
    int* clients = read_create_array(reader, n_clients);
    int* monitors = read_create_array(reader, n_monitors);

    int ori, des;
    double weight;

    fscanf(reader, "%d %d %lf", &ori, &des, &weight);
    // Edge* edges = init_edge_list();
    Node** nodes = init_node_vector(n_knots);

    for (i = 1; i < n_edges; i++) {
        fscanf(reader, "%d %d %lf", &ori, &des, &weight);
        add_edge(nodes[ori], des, weight);
    }

    free(servers);
    free(clients);
    free(monitors);
    destroy_node_vector(nodes, n_knots);
    fclose(reader);
    fclose(writer);

    return 0;
}