/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    return x.rank <= y.rank;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}
void swap(player_t a[], unsigned int i, unsigned int j){
    player_t aux = a[i]; 
    a[i] = a[j];
    a[j] = aux;
}
static void insert(player_t a[], unsigned int pos){
    unsigned int i =  pos;
    while(i>0 && goes_before(a[i], a[i-1])){
        swap(a, i, i-1);
        i--;
    }
}
void sort(player_t a[], unsigned int length) {
    for(unsigned int i = 1u; i<length; i++){
        insert(a, i);
    }
}

