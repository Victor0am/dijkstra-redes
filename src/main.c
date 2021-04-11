#include <stdio.h>
#include <stdlib.h>

#include "./edge.h"
#include "./graph.h"
#include "./node.h"
#include "./ratio.h"
#include "./utils.h"

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
void print_rtt(FILE* fp, Item* ratios, int n) {
    // len = |S||C|
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d %d %.16lf\n", ratios[i].server, ratios[i].client, ratios[i].ratio);
    }
}

static int compare_item(const void* a, const void* b) {
    Item a1 = *(Item*)a;
    Item a2 = *(Item*)b;

    if (a1.ratio < a2.ratio) return -1;
    if (a1.ratio > a2.ratio) return 1;

    if (a1.server < a2.server) return -1;
    if (a1.server > a2.server) return 1;

    if (a1.client < a2.client) return -1;
    if (a1.client > a2.client) return 1;

    return 0;
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
    Item* ratios = generate_ratios(graph);

    qsort(ratios, servers[0] * clients[0], sizeof(Item), compare_item);

    print_rtt(writer, ratios, n_servers * n_clients);

    // frees allocated memory
    // ratio_destroy(ratios);
    free(ratios);
    fclose(reader);
    fclose(writer);
    destroy_graph(graph);

    return 0;
}