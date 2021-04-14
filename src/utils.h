#ifndef UTILS_H
#define UTILS_H

// server: valor identificador do servidor
// client: valor identificador do cliente
// ratio: razao RTT/RTT*
typedef struct item {
    int server;
    int client;
    double ratio;
} Item;

#endif