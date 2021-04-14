#include "./graph.h"

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./edge.h"
#include "./heap.h"
#include "./node.h"
#include "./utils.h"

// nodes: nos do grafo
// n_nodes: numero de nos no grafo
// n_edges: numero de arestas
// csm: vetor de vetores de clients (indice 0), servers (indice 1) e monitors (indice 2). Indice 0 de cada vetor possui o seu tamanho.
struct graph {
    Node** nodes;
    int n_nodes;
    int n_edges;
    int* csm[3];
};

Graph* init_graph(Node** nodes, int n_nodes, int* servers, int* monitors, int* clients, int n_edges) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));

    graph->nodes = nodes;
    graph->n_nodes = n_nodes;
    graph->n_edges = n_edges;
    graph->csm[0] = clients;
    graph->csm[1] = servers;
    graph->csm[2] = monitors;

    return graph;
}

void destroy_graph(Graph* g) {
    destroy_node_vector(g->nodes, g->n_nodes);
    free(g->csm[0]);
    free(g->csm[1]);
    free(g->csm[2]);
    free(g);
}

double* dijkstra(Graph* graph, int src, int* dest1, int* dest2) {
    int n_dest1 = dest1[0], n_dest2 = dest2[0];
    int n_edges = graph->n_edges;

    double* destinies = malloc(sizeof(double) * (n_dest1 + n_dest2));
    double dists[graph->n_nodes];

    Heap* heap = heap_init(graph->n_edges);
    int flag = 0;

    for (int i = 0; i < graph->n_nodes; i++)
        dists[i] = DBL_MAX;

    heap_insert(heap, src, 0);
    dists[src] = 0;

    while (!heap_is_empty(heap)) {
        // valor do indice com menor peso
        int u = heap_min(heap);
        heap_delmin(heap);
        Node* node = graph->nodes[u];

        for (Edge* edge = get_w(node); edge != NULL; edge = get_next(edge)) {
            // recebe vertice destino e peso da aresta adjacente do no inicial
            int v = get_dest(edge);
            double weight = get_weight(edge);
            double dist_u = dists[u];
            double dist_v = dists[v];

            // verifica se a distancia ate v eh maior que de u + peso da aresta adjacente
            if (dist_v > dist_u + weight) {
                // atualiza a distancia de v
                dists[v] = dist_u + weight;
                heap_insert(heap, v, dist_u + weight);
                heap_decrease_key(heap, v, dist_u);
            }
        }
    }

    heap_destroy(heap);

    // os vetores dest1 e dest2 possuem valores de indices
    for (int i = 1; i <= n_dest1; i++) {
        int pos = dest1[i];             // pega o valor de dest1[i] para ser usado como indice de dists
        destinies[i - 1] = dists[pos];  // coloca em vetor destinies a distancia da posicao pos
    }

    for (int j = 1; j <= n_dest2; j++) {
        int pos = dest2[j];                       // pega o valor de dest2[i] para ser usado como indice de dists
        destinies[j - 1 + n_dest1] = dists[pos];  // coloca em vetor destinies a distancia da posicao pos, apos os valores armazenados anteriores
    }

    return destinies;
}

Item* calc_ratios(Graph* graph, double** dists_clients, double** dists_servers, double** dists_monitors) {
    int* clients = graph->csm[0];
    int* servers = graph->csm[1];
    int n_clients = clients[0];
    int n_servers = servers[0];
    int n_monitor = graph->csm[2][0];

    Item item;
    Item* items = (Item*)malloc(n_clients * n_servers * sizeof(Item));

    int count = 0;
    double rtt_m, rtt_cs, rtt1, rtt2, rtt_min, rtt_ratio;

    for (int i = 0; i < n_servers; i++) {
        for (int j = 0; j < n_clients; j++) {
            rtt_cs = dists_clients[j][i] + dists_servers[i][j];  // Cj->Si + Si->Cj

            rtt1 = dists_servers[i][n_clients] + dists_monitors[0][i];              // S->M + M->S
            rtt2 = dists_clients[j][n_servers] + dists_monitors[0][j + n_servers];  // M->C + C->M
            rtt_m = rtt1 + rtt2;

            for (int k = 1; k < n_monitor; k++) {
                rtt1 = dists_servers[i][k + n_clients] + dists_monitors[k][i];              // S->M + M->S
                rtt2 = dists_monitors[k][j + n_servers] + dists_clients[j][k + n_servers];  // M->C + C->M
                rtt_min = rtt1 + rtt2;

                // verifica se rtt* eh menor que o anterior
                if (rtt_m > rtt_min)
                    rtt_m = rtt_min;
            }

            rtt_ratio = rtt_m / rtt_cs;
            item.client = clients[j + 1];
            item.server = servers[i + 1];
            item.ratio = rtt_ratio;

            items[count++] = item;
        }
    }

    return items;
}

static double** init_matrix(Graph* graph, int n_size, int* src, int* dest1, int* dest2) {
    double** dists = malloc(sizeof(double) * n_size);
    for (int i = 1; i <= n_size; i++) {
        dists[i - 1] = dijkstra(graph, src[i], dest1, dest2);
    }

    return dists;
}

static void free_matrix(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
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

Item* generate_ratios(Graph* graph) {
    // armazenando o grafo localmente
    int* clients = graph->csm[0];
    int* servers = graph->csm[1];
    int* monitors = graph->csm[2];
    int n_clients = clients[0];
    int n_servers = servers[0];
    int n_monitors = monitors[0];

    int count = 0;

    // matriz clients * (servers + monitors)
    double** dists_clients = init_matrix(graph, n_clients, clients, servers, monitors);

    // matriz servers * (clients + monitors)
    double** dists_servers = init_matrix(graph, n_servers, servers, clients, monitors);

    // matriz monitors * (servers + clients)
    double** dists_monitors = init_matrix(graph, n_monitors, monitors, servers, clients);

    // insere razoes na heap
    Item* ratios = calc_ratios(graph, dists_clients, dists_servers, dists_monitors);

    qsort(ratios, servers[0] * clients[0], sizeof(Item), compare_item);

    // libera matrizes
    free_matrix(dists_clients, n_clients);
    free_matrix(dists_monitors, n_monitors);
    free_matrix(dists_servers, n_servers);

    return ratios;
}