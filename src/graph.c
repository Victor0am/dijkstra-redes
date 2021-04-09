#include "./graph.h"

#include <float.h>
#include <stdio.h>
#include <stdlib.h>

#include "./edge.h"
#include "./heap.h"
#include "./node.h"
#include "./utils.h"

/**
 * @param nodes nodes with edges 
 * @param n_nodes number of nodes
 * @param n_nodes number of edges
 * @param csm array of clients (index 0), servers (index 1) and monitors (index 2)
 */
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
// double dijkstra(Graph* graph, int src, int* dest1, int* dest2);
//     int* n_dest_v = (int*) malloc (sizeof(int) * graph->n_nodes);
//     n_dest = dest1[0];
//     for (int i = 1; i < n_dest; i++){
//         n_dest_v[dest1[i]] = 1;
//     }
//     n_dest = dest2[0];
//     for (int i = 1; i <n_dest; i++) {
//          n_dest_v[dest2[i]] = 1;
//     }
// ou
// int max;
// if (dest1[0] > dest2[0])
//    max = dest1[0];
// else
//    max = dest2[0];
//
// for (int i = 1; i < max; i++) {
//  n_dest_v[dest1[i]] = ?;
//  n_dest_v[dest2[i]] = ?;
//}
//

double* dijkstra(Graph* graph, int src, int* dest1, int* dest2) {
    int n_dest1 = dest1[0], n_dest2 = dest2[0];
    double* destinies = malloc(sizeof(double) * (n_dest1 + n_dest2));
    int n_edges = graph->n_edges;
    Heap* heap = heap_init(graph->n_edges);
    double dists[graph->n_nodes];
    int flag = 0;

    for (int i = 0; i < graph->n_nodes; i++)
        dists[i] = DBL_MAX;

    heap_insert(heap, src, 0);
    dists[src] = 0;

    while (!heap_is_empty(heap)) {
        int u = heap_min(heap);  // remove
        Node* node = graph->nodes[u];

        for (Edge* edge = get_w(node); edge != NULL; edge = get_next(edge)) {
            // Get vertex label and weight of current adjacent
            // of u.

            int v = get_dest(edge);
            double weight = get_weight(edge);
            double dist_u = dists[u];
            double dist_v = dists[v];

            //  If there is shorted path to v through u.
            if (dist_v > dist_u + weight) {
                // Updating distance of v
                dists[v] = dist_u + weight;
                heap_insert(heap, v, dist_u + weight);
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

//calcula e retorna o RTT(source, destiny)
//double calc_RTT(Graph* graph, int source, int destiny) {
//    return dijkstra(graph, source, destiny) + dijkstra(graph, destiny, source);
//}

//retorna o RTT
//double calc_RTT_with_monitor(Graph* graph, int source, int monitor, int destiny) {
//    return calc_RTT(graph, source, monitor) + calc_RTT(graph, destiny, monitor);
//}

//escolhe o menor RTT dentro do vetor
// double get_min_RTT_monitor(Graph* graph, int client, int server) {
//     int* monitors = graph->csm[2];

//     double min = calc_RTT_with_monitor(graph, client, monitors[1], server);
//     for (int i = 2; i <= monitors[0]; i++) {
//         double aux = calc_RTT_with_monitor(graph, client, monitors[i], server);
//         if (aux < min) {
//             min = aux;
//         }
//     }

//     return min;
// }

// double RTT_ratio(double RTT, double RTT_m) {
//     return RTT_m / RTT;
// }

double* calc_rtt(double** dists_clients, double** dists_servers, int n_clients, int n_servers) {
    int count = 0;
    double rtt;

    double* rtt_cs = malloc(sizeof(double) * (n_clients * n_servers));
    for (int i = 0; i < n_servers; i++) {
        for (int j = 0; j < n_clients; j++) {
            rtt = dists_clients[j][i] + dists_servers[i][j];
            rtt_cs[count++] = rtt;
        }
    }

    return rtt_cs;
}

double* calc_rtt_monitor(double** dists_clients, double** dists_servers, double** dists_monitors, int n_clients, int n_servers, int n_monitor) {
    int count = 0;
    double rtt, rtt1, rtt2, rtt_min;

    double* rtt_m = malloc(sizeof(double) * (n_clients * n_servers));
    for (int i = 0; i < n_servers; i++) {
        for (int j = 0; j < n_clients; j++) {
            rtt_min = dists_clients[j][n_servers] + dists_monitors[0][j + n_servers] + dists_servers[i][n_clients] + dists_monitors[0][i];

            for (int k = 1; k < n_monitor; k++) {
                rtt1 = dists_servers[i][k + n_clients] + dists_monitors[k][i];              // S->M + M->S
                rtt2 = dists_monitors[k][j + n_servers] + dists_clients[j][k + n_servers];  // M->C + C->M
                rtt = rtt1 + rtt2;

                if (rtt < rtt_min)
                    rtt_min = rtt;
                printf("[rtt min] c: %d s: %d rtt: %lf\n", j, i, rtt);
            }

            rtt_m[count++] = rtt_min;
        }
    }

    return rtt_m;
}

// Ratio** calc_ratios_heap(double* rtt_m, double* rtt_cs, int n_clients, int n_servers) {
//     int count = 0;

//     for (int i = 0; i < n_clients; i++) {
//         for (int j = 0; j < n_servers; j++) {
//             //printf("ANTES\n");
//             double rtt_ratio = rtt_m[count] / rtt_cs[count];
//             //printf("c %d s %d ratio: %lf\n", clients[i + 1], servers[j + 1], rtt);
//             ratio = init_ratio(clients[i + 1], servers[j + 1], rtt_ratio);
//             insert_ratio(ratios, ratio, count++);
//         }
//     }
// }

Ratio** calc_ratios(Graph* graph) {
    int* clients = graph->csm[0];
    int* servers = graph->csm[1];
    int* monitors = graph->csm[2];
    int n_clients = clients[0];
    int n_servers = servers[0];
    int n_monitors = monitors[0];
    // Ratio** ratios =  init_ratio_vector(n_clients, n_servers);
    Ratio* ratios[n_clients * n_servers];
    int count = 0;
    double** dists_clients = malloc(sizeof(double*) * n_clients);
    double** dists_servers = malloc(sizeof(double*) * n_servers);
    double** dists_monitors = malloc(sizeof(double*) * n_monitors);

    // matriz clients * (servidores + monitores)
    for (int i = 1; i <= n_clients; i++) {
        dists_clients[i - 1] = dijkstra(graph, clients[i], servers, monitors);
    }

    // matriz servidores * (clientes + monitores)
    for (int i = 1; i <= n_servers; i++) {
        dists_servers[i - 1] = dijkstra(graph, servers[i], clients, monitors);
    }

    // matriz monitores * (servidores + clientes)
    for (int i = 1; i <= n_monitors; i++) {
        dists_monitors[i - 1] = dijkstra(graph, monitors[i], servers, clients);
    }

    double rtt;
    // Ratio* ratio;
    count = 0;

    double* rtt_cs = malloc(sizeof(double) * (n_clients * n_servers));
    for (int i = 0; i < n_clients; i++) {
        for (int j = 0; j < n_servers; j++) {
            rtt = dists_clients[i][j] + dists_servers[j][i];
            //ratio = init_ratio(graph->csm[0][i + 1], graph->csm[1][j + 1], rtt);
            rtt_cs[count++] = rtt;
            printf("[rtt] c: %d s: %d rtt: %lf\n", clients[i + 1], servers[j + 1], rtt);
        }
    }
    count = 0;

    double* rtt_m = malloc(sizeof(double) * (n_clients * n_servers));
    for (int i = 0; i < n_servers; i++) {
        // S->M + M->C

        for (int j = 0; j < n_clients; j++) {
            double rtt_min;
            rtt_min = dists_clients[j][n_servers] + dists_monitors[0][j + n_servers] + dists_servers[i][n_clients] + dists_monitors[0][i];
            for (int k = 1; k < n_monitors; k++) {
                double rtt1 = dists_servers[i][k + n_clients] + dists_monitors[k][i];              // S->M + M->S
                double rtt2 = dists_monitors[k][j + n_servers] + dists_clients[j][k + n_servers];  // M->C + C->M
                rtt = rtt1 + rtt2;

                if (rtt < rtt_min)
                    rtt_min = rtt;
            }

            rtt_m[count++] = rtt_min;
            printf("[rtt m] c: %d s: %d rtt: %lf\n", clients[j + 1], servers[i + 1], rtt_min);
        }
    }
    // double* rtt_m = calc_rtt_monitor(dists_clients, dists_servers, dists_monitors, n_clients, n_servers, n_monitors);
    // double* rtt_m = calc_rtt_monitor(dists_clients, dists_servers, dists_monitors, n_clients, n_servers, n_monitors);
    rtt_cs = calc_rtt(dists_clients, dists_servers, n_clients, n_servers);

    count = 0;
    Ratio* ratio_heap = ratio_init(n_clients * n_servers);
    Item item;
    for (int i = 0; i < n_clients; i++) {
        for (int j = 0; j < n_servers; j++) {
            //printf("ANTES\n");
            double rtt_ratio = rtt_m[count] / rtt_cs[count];
            // printf("%lf / %lf = %lf\n", rtt_m[count], rtt_cs[count], rtt_ratio);

            //printf("c %d s %d ratio: %lf\n", clients[i + 1], servers[j + 1], rtt);
            item.client = clients[i + 1];
            item.server = servers[j + 1];
            item.ratio = rtt_ratio;
            printf("c: %d s: %d ratio: %lf\n", item.client, item.server, rtt_ratio);
            ratio_insert(ratio_heap, item);
            count++;
        }
    }

    free(rtt_m);
    free(rtt_cs);

    for (int i = 0; i < n_clients; i++) {
        // for (int j = 0; j < n_servers + n_monitors; j++) {
        // }
        free(dists_clients[i]);
    }
    free(dists_clients);

    for (int i = 0; i < n_servers; i++) {
        // for (int j = 0; j < n_clients + n_monitors; j++) {
        // }
        free(dists_servers[i]);
    }
    free(dists_servers);

    for (int i = 0; i < n_monitors; i++) {
        // for (int j = 0; j < n_servers + n_clients; j++) {
        // }
        free(dists_monitors[i]);
    }
    free(dists_monitors);

    ratio_destroy(ratio_heap);
    //destroy_ratio_vector(rtt_cs, n_servers, n_clients);
    return NULL;
}