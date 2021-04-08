#include <stdio.h>
#include <stdlib.h>

#include "./edge.h"
#include "./graph.h"
#include "./node.h"
#include "./ratio.h"

/**
 * Reads file of size n and initializes an array with values read from file.
 * (PT: Ler arquivo de tamanho n e inicializa um vetor com valores lido do arquivo.)
 * @param {FILE* fp} - File pointer
 * @param {int n} - Size of array - 1
 * @return array initialized and stores values read from file.
 */
int* read_create_array(FILE* fp, int n) {
    int* array = (int*)malloc(sizeof(int) * (n + 1));
    array[0] = n;  // first index stores the size of the vector
    for (int i = 1; i <= n; i++) {
        fscanf(fp, "%d", &array[i]);
    }

    return array;
}

/**
 * Writes ratio's information in file. The ratio structure must be sorted beforhand by rtt_ratio atribute.
 * (PT: Escreve as informacoes de ratio no arquivo. A estrutura ratio deve estar anteriormente organizado pelo atributo rtt_ratio.)
 * 
 * @param {FILE* fp} - File pointer
 * @param {Ratios** ratios} - Array of ratio
 * @param {int len} - Size of array (|S|*|C|)
 */
void print_rtt(FILE* fp, Ratio** ratios, int len) {
    // len = |S||C|
    for (int i = 0; i < len; i++) {
        Ratio* ratio = ratio_min(ratios, len - i);
        fprintf(fp, "%d %d %lf", get_server(ratio), get_client(ratio), get_rtt_ratio(ratio));
        destroy_ratio(ratio);
    }
}

int main(int argc, char** argv) {
    // open files
    FILE* reader = fopen(argv[1], "r");
    FILE* writer = fopen(argv[2], "w");

    // reads prior information about graph
    int n_monitors, n_clients, n_servers, n_nodes, n_edges, i;
    fscanf(reader, "%d %d", &n_nodes, &n_edges);
    fscanf(reader, "%d %d %d", &n_servers, &n_clients, &n_monitors);

    // reads and stores servers', clients' and monitors' nodes into an array of integers
    int* servers = read_create_array(reader, n_servers);
    int* clients = read_create_array(reader, n_clients);
    int* monitors = read_create_array(reader, n_monitors);

    int ori, des;
    double weight;

    // initializes node vector and reads and adds first edge
    Node** nodes = init_node_vector(n_nodes);
    fscanf(reader, "%d %d %lf", &ori, &des, &weight);
    add_edge(nodes[ori], des, weight);

    // adds other edges to nodes
    for (i = 1; i < n_edges; i++) {
        fscanf(reader, "%d %d %lf", &ori, &des, &weight);
        add_edge(nodes[ori], des, weight);
    }

    // initializes graph with server, monitors and clients
    Graph* graph = init_graph(nodes, n_nodes, servers, monitors, clients, n_edges);
    calc_ratios(graph);

    // double d1 = dijkstra(graph, 0, 4) + dijkstra(graph, 4, 0);
    // printf("%lf\n", d1);

    // double d2 = dijkstra(graph, 0, 1) + dijkstra(graph, 1, 0);
    // double d3 = dijkstra(graph, 1, 4) + dijkstra(graph, 4, 1);
    // double d4 = dijkstra(graph, 0, 2) + dijkstra(graph, 2, 0);
    // double d5 = dijkstra(graph, 2, 4) + dijkstra(graph, 4, 2);
    // printf("%lf %lf %lf %lf\n", d2, d3, d4, d5);
    // if (d2 + d3 > d4 + d5) {
    //     printf("%lf\n", (d4 + d5) / (d1));
    // } else {
    //     printf("%lf\n", (d2 + d3) / (d1));
    // }

    // for (int i = 0; i < n_nodes; i++)
    //     printf("%lf\n", ratios[i]);
    // Ratio** ratios = calc_ratios(graph);
    // print_rtt(writer, ratios, n_servers * n_clients);

    // frees allocated memory
    // destroy_ratio_vector(ratios);
    // free(ratios);
    fclose(reader);
    fclose(writer);
    destroy_graph(graph);

    return 0;
}