#ifndef EDGE_H
#define EDGE_H

typedef struct edge Edge;

/**
 * Inicializa uma lista de edge nao vazia.
 * 
 * @param {int dest} No destino da aresta direcionada.
 * @param {double weight} Peso da aresta direcionada.
 *
 * @pre valores de dest e weight sao conhecidos.
 * @post lista de edge eh inicializada e nao vazia.
 * 
 * @return lista de edge inicializada com um item
 */
Edge* init_edge_list(int dest, double weight);

/**
 * Retorna o valor de destino do edge.
 * 
 * @param {Edge* edge} lista de arestas.
 * 
 * @pre lista de edge inicializada com pelo menos um item inicializado.
 * @post nenhuma.
 * 
 * @return valor do destino do primeiro item da lista de edge.
 */
int get_dest(Edge* edge);

/**
 * Retorna o valor de peso do edge.
 * 
 * @param {Edge* edge} lista de arestas.
 * 
 * @pre lista de edge inicializada com pelo menos um item inicializado.
 * @post nenhuma.
 * 
 * @return peso do primeiro item da lista de edge.
 */
double get_weight(Edge* edge);

/**
 * Retorna o segundo item da lista de edge.
 * 
 * @param {Edge* edge} lista de edge.
 * 
 * @pre lista de edge inicializada com pelo menos um item inicializado.
 * @post nenhuma.
 * 
 * @return segundo item da lista de edge.
 */
Edge* get_next(Edge* edge);

/**
 * Configura a proxima aresta da estrutura Edge.
 * 
 * @param {Edge* edge} lista de edge que o proximo item sera modificado.
 * @param {Edge* next} lista de edge que vai ser adicionada a edge.
 * 
 * @pre listas de edge existem e possuem pelo menos um item inicializado.
 * @post o proximo item da lista aponta para lista de edge next.
 */
void set_next(Edge* edge, Edge* next);

/**
 * Libera memoria alocada do item da lista de edge.
 * 
 * @param {Edge* edge} lista de edge que memoria sera liberada
 * 
 * @pre lista de edge inicializada com pelo menos um item inicializado.
 * @post item eh liberado.
 */
void destroy_edge(Edge* edge);

/**
 * Libera memoria alocada da lista de de edge
 * 
 * @param {Edge* edge} lista de edge que memoria sera liberada
 * 
 * @pre lista de edge inicializada
 * @post memoria alocada por lista de edge liberada
 */
void destroy_edge_list(Edge* edges);

#endif