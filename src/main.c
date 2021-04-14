#include <stdio.h>
#include <stdlib.h>

#include "./edge.h"
#include "./graph.h"
#include "./io.h"
#include "./node.h"
#include "./utils.h"

int main(int argc, char** argv) {
    // abre arquivos
    FILE* reader = fopen(argv[1], "r");
    FILE* writer = fopen(argv[2], "w");

    // ler informacao sobre quanto e quem sao os nos monitores, clientes e servidores
    int n_monitors, n_clients, n_servers, n_nodes, n_edges, i;
    fscanf(reader, "%d %d", &n_nodes, &n_edges);
    fscanf(reader, "%d %d %d", &n_servers, &n_clients, &n_monitors);

    // ler e armazena informacoes dos nos em um vetor de inteiros
    int* servers = read_create_array(reader, n_servers);
    int* clients = read_create_array(reader, n_clients);
    int* monitors = read_create_array(reader, n_monitors);

    int ori, des;
    double weight;

    // inicialida vetor de no em que cada indice eh referente a um no e ler e adiciona primeira aresta.
    Node** nodes = init_node_vector(n_nodes);
    fscanf(reader, "%d %d %lf", &ori, &des, &weight);
    add_edge(nodes[ori], des, weight);

    // adiciona as outras arestas
    for (i = 1; i < n_edges; i++) {
        fscanf(reader, "%d %d %lf", &ori, &des, &weight);
        add_edge(nodes[ori], des, weight);
    }

    // inicializa grafo preenchido com informacoes
    Graph* graph = init_graph(nodes, n_nodes, servers, monitors, clients, n_edges);

    // gera razoes RTT/RTTs* dos clientes e servidores
    Item* ratios = generate_ratios(graph);

    // armazena em um arquivo servidor, cliente e razao RTT/RTT*
    print_rtt(writer, ratios, n_servers * n_clients);

    // libera memoria alocada
    free(ratios);
    fclose(reader);
    fclose(writer);
    destroy_graph(graph);

    return 0;
}