#include "./io.h"

#include <stdio.h>
#include <stdlib.h>

#include "./utils.h"

int* read_create_array(FILE* fp, int n) {
    int* array = (int*)malloc(sizeof(int) * (n + 1));
    array[0] = n;  // primeiro indice armazena tamanho do vetor
    for (int i = 1; i <= n; i++) {
        fscanf(fp, "%d", &array[i]);
    }

    return array;
}

void print_rtt(FILE* fp, Item* ratios, int n) {
    // n = |S||C|
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d %d %.16lf\n", ratios[i].server, ratios[i].client, ratios[i].ratio);
    }
}
