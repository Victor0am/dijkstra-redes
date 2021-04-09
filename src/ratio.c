#include "ratio.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @param client id of client
 * @param server id of server
 * @param rtt_ratio ratio between RTT and RTT*
 */

struct ratio {
    int n;
    int max_n;
    Item *pq;
};

Ratio *ratio_init(int max_n) {
    Ratio *r = (Ratio *)malloc(sizeof(Ratio));
    r->n = 0;
    r->max_n = max_n;
    r->pq = (Item *)malloc(max_n * sizeof(Item));

    return r;
}

static void ratioify_bottom_top(Ratio *r, int index) {
    Item temp;
    int parent_node = (index - 1) / 2;

    if (r->pq[parent_node].ratio > r->pq[index].ratio) {
        temp = r->pq[parent_node];
        r->pq[parent_node] = r->pq[index];
        r->pq[index] = temp;
        ratioify_bottom_top(r, parent_node);
    }
}

static void ratioify_top_bottom(Ratio *h, int parent_node) {
    int left = parent_node * 2 + 1;
    int right = parent_node * 2 + 2;
    int min;
    Item temp;

    if (left >= h->n || left < 0)
        left = -1;
    if (right >= h->n || right < 0)
        right = -1;

    if (left != -1 && h->pq[left].ratio < h->pq[parent_node].ratio)
        min = left;
    else
        min = parent_node;
    if (right != -1 && h->pq[right].ratio < h->pq[min].ratio)
        min = right;

    if (min != parent_node) {
        temp = h->pq[min];
        h->pq[min] = h->pq[parent_node];
        h->pq[parent_node] = temp;

        ratioify_top_bottom(h, min);
    }
}

void ratio_insert(Ratio *h, Item item) {
    if (h->n < h->max_n) {
        h->pq[h->n] = item;
        ratioify_bottom_top(h, h->n);
        h->n++;
    }
}

int ratio_is_empty(Ratio *ratio) {
    return ratio->n == 0;
}

Item ratio_min(Ratio *h) {
    Item pop;
    pop = h->pq[0];
    h->pq[0] = h->pq[h->n - 1];
    h->n--;

    ratioify_top_bottom(h, 0);
    return pop;
}

void ratio_destroy(Ratio *ratio) {
    free(ratio->pq);
    free(ratio);
}