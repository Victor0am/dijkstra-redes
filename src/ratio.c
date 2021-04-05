#include <stdlib.h>
#include <stdio.h>
#include "ratio.h"

/**
 * @param client id of client
 * @param server id of server
 * @param rtt_ratio ratio between RTT and RTT*
 */
struct ratio{
    int client;
    int server;
    double rtt_ratio;
};

Ratio* init_ratio(int client, int server, double ratio){
    Ratio* new_ratio = (Ratio*) malloc(sizeof(Ratio));
    
    new_ratio->client = client;
    new_ratio->server = server;
    new_ratio->rtt_ratio = ratio;

    return new_ratio;
}

Ratio** init_ratio_vector(int n_clients, int n_servers){
    Ratio** new_ratio_vector = (Ratio**)malloc(sizeof(Ratio*)*(n_clients*n_servers + 1));

    return new_ratio_vector;
}


 
static void exchange(Ratio* r1, Ratio* r2){
    Ratio* aux;
    aux = r1;
    r1 = r2;
    r2 = aux;    
}

static int less(Ratio* r1, Ratio* r2) {
    if (r1->rtt_ratio < r2->rtt_ratio) {
        return 1;
    }
    return 0;
}

static void fix_up(Ratio** ratios, int k) {
    while (k > 1 && less(ratios[k/2], ratios[k])) {
        exchange(ratios[k/2], ratios[k]); 
        k = k/2;
    }
}

static void fix_down(Ratio** ratios, int sz, int k) {
    int aux;

    while (2 * k <= sz) {
        aux = 2*k;
       
        if (aux < sz &&  ratios[aux+1]->rtt_ratio < ratios[aux]->rtt_ratio) 
            aux++;
        
        if (ratios[aux]->rtt_ratio <= ratios[k]->rtt_ratio)
            break;

        exchange(ratios[k], ratios[aux]);
        k = aux;
    }
}

void insert_ratio(Ratio** ratio_v, Ratio* ratio, int n){
    ratio_v[n] = ratio;
    fix_up(ratio_v, n);
}

Ratio* ratio_min(Ratio** ratios, int sz) {
    Ratio* ratio = ratios[1];

    exchange(ratios[1], ratios[sz--]);
    fix_down(ratios, sz, 1);

    return ratio;
}

int get_client(Ratio* ratio){
    return ratio->client;
}

int get_server(Ratio* ratio){
    return ratio->server;
}

double get_rtt_ratio(Ratio* ratio){
    return ratio->rtt_ratio;
}

void destroy_ratio(Ratio* ratio){
    free(ratio);
}

void destroy_ratio_vector(Ratio** ratio_v){
    free(ratio_v);
}
