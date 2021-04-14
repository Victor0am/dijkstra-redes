#ifndef IO_H
#define IO_H

#include <stdio.h>
#include "./utils.h"

/**
 * Ler arquivo de tamanho n e inicializa um vetor com valores lido do arquivo.
 * @param {FILE* fp} - ponteiro para arquivo.
 * @param {int n} - tamanho do array - 1.
 * 
 * @pre Ponteiro para um arquivo valido e tamanho do vetor eh conhecido.
 * @post Vetor eh iniciazliado e preenchido.
 * 
 * @return vetor de inteiros
 */
int* read_create_array(FILE* fp, int n);

/**
 * Escreve as informacoes de ratio no arquivo. A estrutura ratio deve estar anteriormente organizado pelo 
 * atributo rtt_ratio.
 * 
 * @param {FILE* fp} - ponteiro para arquivo.
 * @param {Item* ratios} - vetor de Item.
 * @param {int len} - tamanho do vetor (|S|*|C|).
 * 
 * @pre 
 */
void print_rtt(FILE* fp, Item* ratios, int n);

#endif