#include "./graph.h"
#include "./heap.h"
#include "./edge.h"
#include "./node.h"
#include <stdio.h>
#include <stdlib.h>

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

Graph* init_graph(Node** nodes, int n_nodes, int* servers, int* monitors, int* clients, int n_edges){
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

double dijkstra(Graph* graph, int src, int dest){
    int n_edges = graph->n_edges;
    Heap* heap = heap_init(graph->n_edges, graph->n_nodes, src);
    double distance;
    heap_insert(heap, src, 0);  
    
    while(!heap_is_empty(heap)){
        int u = heap_min(heap); // remove
        Node* node = graph->nodes[u];

        for(Edge* edge = get_w(node); edge != NULL; edge = get_next(edge)){
            // Get vertex label and weight of current adjacent
            // of u.

            int v = get_dest(edge);
            double weight = get_weight(edge);
            double dist_u = get_heap_dist(heap, u);
            double dist_v = get_heap_dist(heap, v);
            
            //  If there is shorted path to v through u.
            if (dist_v > dist_u + weight) {
                // Updating distance of v
                heap_insert(heap, v, dist_u + weight); 
            }
        }
    }

    for(int i =0; i < 5; i++){
        double aux = (get_heap_dist(heap, i) > 1000) ? 1000 : get_heap_dist(heap, i);
    }

    distance = get_heap_dist(heap, dest);

    heap_destroy(heap);

    return distance;
}

//calcula e retorna o RTT(source, destiny)
double calc_RTT(Graph* graph, int source, int destiny){
    return dijkstra(graph, source, destiny) + dijkstra(graph, destiny, source);
}

//retorna o RTT 
double calc_RTT_with_monitor(Graph* graph, int source, int monitor, int destiny){
    return calc_RTT(graph, source, monitor) + calc_RTT(graph, destiny, monitor);
}

//escolhe o menor RTT dentro do vetor
double get_min_RTT_monitor(Graph* graph, int client, int server){
    int* monitors = graph->csm[2];
    
    double min = calc_RTT_with_monitor(graph, client, monitors[1], server);
    for (int i = 2; i <= monitors[0]; i++){
        double aux = calc_RTT_with_monitor(graph, client, monitors[i], server);        
        if(aux<min){
            min = aux;
        }
    }

    return min;
}

double RTT_ratio(double RTT, double RTT_m) {
    return RTT_m / RTT;
}

Ratio** calc_ratios(Graph* graph){
    int* clients = graph->csm[0];
    int* servers = graph->csm[1];
    int n_clients = clients[0];
    int n_servers = servers[0];
    
    Ratio** ratios = init_ratio_vector(n_clients, n_servers);
    for(int i = 1; i <= n_clients; i++){
        for(int j = 1; j<= n_servers; j++){
            double ratio = RTT_ratio(calc_RTT(graph, servers[j], clients[i]), get_min_RTT_monitor(graph, clients[i], servers[j]));
            Ratio* item = init_ratio(clients[i], servers[j], ratio);
            insert_ratio(ratios, item, i*(j-1) + j);
        }
    }

    return ratios;
}