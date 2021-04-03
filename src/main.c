#include <stdio.h>
#include <stdlib.h>

#include "./graph.h"
#include "./edge.h"
#include "./node.h"

int* read_create_array(FILE* fp, int n) {
    int* array = (int*)malloc(sizeof(int) * (n + 1));
    array[0] = n; //primeira posição armazena o tamanho do vetor
    for (int i = 1; i <= n; i++) {
        fscanf(fp, "%d", &array[i]);
    }

    return array;
}

int main(int argc, char** argv) {
    int n_monitors, n_clients, n_servers, n_nodes, n_edges, i;
    FILE* reader = fopen(argv[1], "r");
    FILE* writer = fopen(argv[2], "w");

    fscanf(reader, "%d %d", &n_nodes, &n_edges);
    fscanf(reader, "%d %d %d", &n_servers, &n_clients, &n_monitors);
    
    int* servers = read_create_array(reader, n_servers);
    int* clients = read_create_array(reader, n_clients);
    int* monitors = read_create_array(reader, n_monitors);

    int ori, des;
    double weight;

    Node** nodes = init_node_vector(n_nodes);
    fscanf(reader, "%d %d %lf", &ori, &des, &weight);
    add_edge(nodes[ori], des, weight);

    for (i = 1; i < n_edges; i++) {
        fscanf(reader, "%d %d %lf", &ori, &des, &weight);
        add_edge(nodes[ori], des, weight);
    }

    Graph* graph = init_graph(nodes, n_nodes, servers, clients, monitors);

    // Printa as arestas
    // for(int i = 0; i < n_nodes; i++){
    //     Node* node = nodes[i];
    //     printf("Arestas de %d\n", i);
    //     for(Edge* edge = get_w(node); edge != NULL; edge = get_next(edge)){
    //         printf("\tDEST: %d", get_dest(edge));
    //         printf("\tWEIG: %lf\n", get_weight(edge));
    //     }
    //     printf("\n");
    // }

    double dist1 = dijkstra(graph, servers[1], clients[1], n_edges);
    double dist2 = dijkstra(graph, clients[1], servers[1], n_edges);

    printf("RESULTADO: %lf\n", dist1+dist2);
    
    fclose(reader);
    fclose(writer);
    destroy_graph(graph);

    return 0;
}