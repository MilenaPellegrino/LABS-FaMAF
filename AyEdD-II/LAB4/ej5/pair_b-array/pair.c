#include<stdio.h>
#include<stdlib.h>


typedef struct s_pair_t pair_t;

struct s_pair_t {
    int values[2];
};

pair_t pair_new(int x, int y){
    pair_t pair; 
    pair.values[0] =x;
    pair.values[1] = y;
    return pair;
}

int pair_first(pair_t p){
    return p.values[0];
}

int pair_second(pair_t p){
    return p.values[1];
}

pair_t pair_swapped(pair_t p){
    pair_t pair; 
    pair.values[0] = p.values[1];
    pair.values[1] = p.values[0]; 
    return pair;
}

pair_t pair_destroy(pair_t p){
    return p;
}