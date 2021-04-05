#ifndef RATIO_H
#define RATIO_H

typedef struct ratio Ratio;

Ratio* init_ratio(int client, int server, double ratio);

Ratio** init_ratio_vector(int n_clients, int n_servers);

void insert_ratio(Ratio** ratio_v, Ratio* ratio, int n);

Ratio* ratio_min(Ratio** ratios, int sz);

int get_client(Ratio* ratio);

int get_server(Ratio* ratio);

double get_rtt_ratio(Ratio* ratio);

void destroy_ratio(Ratio* ratio);

void destroy_ratio_vector(Ratio** ratio_v);

#endif