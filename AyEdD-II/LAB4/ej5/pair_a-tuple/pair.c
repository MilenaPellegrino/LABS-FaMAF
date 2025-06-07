#include<stdlib.h>
#include<stdio.h>

typedef struct s_pair_t pair_t;

struct s_pair_t {
    int fst;
    int snd;
};

pair_t pair_new(int x, int y){
    pair_t pair;
    pair.fst = x; 
    pair.snd = y; 
    return pair;
}

int pair_first(pair_t p){
    return p.fst;
}

int pair_second(pair_t p){
    return p.snd;
}

pair_t pair_swapped(pair_t p){
    pair_t pair; 
    pair.fst = p.snd; 
    pair.snd = p.fst; 
    return pair;
}

pair_t pair_destroy(pair_t p){
    return p;
}