#ifndef MODULO_ORDENACION_H
#define MODULO_ORDENACION_H
#include <stdlib.h>

struct Par {
    int first;
    char second;
};

void quick_sort(struct Par arr[], size_t size);

#endif
