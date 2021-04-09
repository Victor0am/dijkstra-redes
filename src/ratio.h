#ifndef RATIO_H
#define RATIO_H

#include "utils.h"

typedef struct ratio Ratio;

Ratio* ratio_init(int max_n);

void ratio_insert(Ratio* ratio, Item item);

int ratio_is_empty(Ratio* ratio);

Item ratio_min(Ratio* ratio);

void ratio_destroy(Ratio* ratio);

#endif