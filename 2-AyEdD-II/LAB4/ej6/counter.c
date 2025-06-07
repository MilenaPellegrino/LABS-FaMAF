#include <stdbool.h>
#include <stdlib.h>

#include "counter.h"

struct _counter {
    unsigned int count;
};

counter counter_init(void) {
    counter p = NULL; 
    p = malloc(sizeof(counter));
    p->count = 0;
    return p;
}

void counter_inc(counter c) {
    c->count +=1;
}

bool counter_is_init(counter c) {
    if(c->count == 0) return true; 
    else return false;
}

void counter_dec(counter c) {
    c->count -= 1;
}

counter counter_copy(counter c) {
    counter c2 = NULL; 
    c2 = malloc(sizeof(counter));
    c2->count = c->count;
    return c2;
}

void counter_destroy(counter c) {
    free(c);
    c= NULL;
}
