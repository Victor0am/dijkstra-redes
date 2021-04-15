#ifndef NODE_H
#define NODE_H

#include "edge.h"

typedef struct node Node;

/**
 * Inicializa um node vazio.
 * 
 * @pre nenhum.
 * @post node eh inicializado e criado.
 * 
 * @return node inicializado vazio.
 */
Node* init_node();

/**
 * Inicializa um vetor de nodes.
 * 
 * @param {int n} Tamanho do vetor de nodes que será inicializados.
 *
 * @pre o tamanho do vetor de nodes a ser inicializado deve ser especificado.
 * @post vetor de vários nodes eh inicializado e criado.
 * 
 * @return vetor de nodes inicializado inicializado.
 */
Node** init_node_vector(int n);

/**
 * Adiciona uma nova edge a lista de edges de um node.
 * 
 * @param {Node* node} Node em que a nova edge sera inserida.
 * @param {int dest} Chave do no do grafo que eh destino da nova edge.
 * @param {double weight} Peso da edge que liga o node do atual ate o seu destino.
 *
 * @pre o node passado como parametro deve estar inicializado.
 * @post a nova edge eh adicionada a lista encadeada de edges daquele node.
 * 
 */
void add_edge(Node* node, int dest, double weight);

/**
 * Retornar o inicio da lista de edges daquele node.
 * 
 * @param {Node* node} Node que deseja-se obter a lista de edges.
 *
 * @pre o node passado como parametro deve estar devidamente inicializado.
 * @post o primeiro elemento da lista de edges do node eh retornado.
 * 
 * @return primeiro elemento da lista de edges do node.
 */
Edge* get_w(Node* node);

/**
 * Libera toda a memoria que foi alocada inicialmente para um node, libera tambem a lista de edges
 * daquele node.
 * 
 * @param {Node* node} Node.
 * 
 * @pre node existe e nao eh vazio.
 * @post memoria eh liberada
 */
void destroy_node(Node* node);

/**
 * Libera toda a memoria que foi alocada inicialmente para um vetor de nodes, libera tambem cada um dos nodes
 * do vetor e toda a lista de edges de cada node.
 * 
 * @param {Node** node} Node.
 * @param {int n_nodes} Tamanho do vetor de nodes.
 * 
 * @pre vetor de nodes deve estar devidamente inicializado e seu tamanho passado deve estar correto.
 * @post memoria eh liberada
 */
void destroy_node_vector(Node** node, int n_nodes);

#endif
