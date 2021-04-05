#ifndef EDGE_H
#define EDGE_H

typedef struct edge Edge;

/**
 * Initializes a non-empty edge list.
 * (PT: Inicializa uma lista de edge nao vazia.)
 * 
 * @param {int dest} Node value of the destiny of directed edge 
 * @param {double weight} Value of edge's weight
 * 
 * @return edge list with new edge
 */
Edge* init_edge_list(int dest, double weight);

/**
 * Returns edge's destiny value
 * (PT: Retorna o valor de destino do edge.)
 * 
 * @param {Edge* edge} 
 * 
 * @return value of edge's destiny
 */
int get_dest(Edge* edge);

/**
 * Returns edge's weight value
 * (PT: Retorna o valor de peso do edge.)
 * 
 * @param {Edge* edge} 
 * 
 * @return value of edge's weight
 */
double get_weight(Edge* edge);

/**
 * Set edge's weight value
 * (PT: Configura o valor de peso do edge.)
 * 
 * @param {Edge* edge} 
 * @param {double weight} new weight
 *  */
void set_weight(Edge* edge, double weight);

/**
 * Return next edge.
 * (PT: Retorna a proxima aresta)
 * 
 * @param {Edge* edge}
 * 
 * @return the next edge
 */
Edge* get_next(Edge* edge);

/**
 * Set edge's next edge.
 * (PT: Configura a proxima aresta da estrutura Edge.)
 * 
 * @param {Edge* edge} 
 * @param {Edge* next}
 */
void set_next(Edge* edge, Edge* next);

/**
 * Frees edge's allocated memory
 * (PT: libera memoria alocada da aresta)
 * 
 * @param {Edge* edge}
 */
void destroy_edge(Edge* edge);

/**
 * Frees edge's allocated memory
 * (PT: libera memoria alocada da aresta)
 * 
 * @param {Edge* edge}
 */
void destroy_edge_list(Edge* edges);

#endif