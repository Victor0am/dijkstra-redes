#ifndef GRAPH_H
#define GRAPH_H

#include "./edge.h"
#include "./node.h"
#include "./utils.h"

typedef struct graph Graph;

/**
 * Inicializa um graph (grafo) com suas informacoes.
 * 
 * @param {Node** nodes} Vetor de lista de nos, onde cada indice eh referente a um no do mesmo valor.
 * @param {int n_nodes} Quantidade de nos do grafo.
 * @param {int* servers} Vetor de nos servidores, cada valor armazenado eh referente ao numero do servidor.
 * @param {int* monitors} Vetor de nos monitores, cada valor armazenado eh referente ao numero do monitor.
 * @param {int* clients} Vetor de nos clientes, cada valor armazenado eh referente ao numero do cliente.
 * @param {int n_edges} Quantidade de arestas do grafo.
 *
 * @pre vetor de lista de nos, vetores de servidores, monitores e clientes inicializadas e quantidade de nos
 *      e arestas eh conhecido.
 * @post grafo eh inicializado e criado.
 * 
 * @return grafo inicializado nao vazio.
 */
Graph* init_graph(Node** nodes, int n_nodes, int* servers, int* monitors, int* clients, int n_edges);

/**
 * Algortimo de Dijkstra. Percorre os caminhos considerando a fonte (source) e verifica qual a menor 
 * distancia do no fonte ate os outros nos. Como alguns nos nao sao uteis (nao sao do tipo servidor, 
 * monitor ou cliente), eh importante informar os nos destinos uteis (vetores dest1 e dest2 com os valores
 * dos nos). 
 * 
 * @param {Graph* graph} Grafo.
 * @param {int src} Valor do no fonte.
 * @param {int* dest1} Vetor de nos destino 1, cada valor armazenado eh referente ao numero do item. Pode ser
 * clientes, servidores ou monitores.
 * @param {int* dest2} Vetor de nos destino 2, cada valor armazenado eh referente ao numero do item. Pode ser
 * clientes, servidores ou monitores.
 * 
 * @pre grafo existe e nao eh vazio, vetores de servidores, monitores ou clientes inicializadas.
 * @post distancias da fonte ate os nos destinos sao conhecidas.
 * 
 * @return vetor de distancias da fonte ate o destino, na ordem de src -> dest1 e depois src -> dest2.  
 */
double* dijkstra(Graph* graph, int src, int* dest1, int* dest2);

/**
 * Algortimo de Dijkstra. Percorre os caminhos considerando a fonte (source) e verifica qual a menor 
 * distancia do no fonte ate os outros nos. Como alguns nos nao sao uteis (nao sao do tipo servidor, 
 * monitor ou cliente), eh importante informar os nos destinos uteis (vetores dest1 e dest2 com os valores
 * dos nos). 
 * 
 * @param {Graph* graph} Grafo.
 * 
 * @pre grafo existe e nao eh vazio.
 * @post memoria eh liberada
 */
void destroy_graph(Graph* g);

/**
 * Calcula os RTTs e RTT*s de cliente e servidor
 * 
 * @param {Graph* graph} Grafo.
 * @param {double** dists_clients} Distancias de clientes ate outros nos.
 * @param {double** dists_servers} Distancias de servidores ate outros nos.
 * @param {double** dists_monitors} Distancias de monitores ate outros nos.
 *
 * @pre grafo inicializado e nao vazio, matriz de distancias de:
 *      clientes x (servidores + monitores), 
 *      servidores x (clientes + monitores),
 *      monitores x (servidores + clientes).
 * 
 * @post RTTs e RTTs* sao inicializado e conhecidos.
 * 
 * @return vetor de Item com os Item inicializados. 
 */
Item* calc_ratios(Graph* graph, double** dists_clients, double** dists_servers, double** dists_monitors);

/**
 * Calcula matriz de distancias entre servidor, cliente e monitor usando algortimo de dijkstra e 
 * gera os RTTs e RTT*s.
 * 
 * @param {Graph* graph} Grafo.
 *
 * @pre grafo inicializado e nao vazio 
 * @post RTTs e RTTs* sao inicializado e conhecidos.
 * 
 * @return vetor de Item com os Item inicializados. 
 */
Item* generate_ratios(Graph* graph);

#endif