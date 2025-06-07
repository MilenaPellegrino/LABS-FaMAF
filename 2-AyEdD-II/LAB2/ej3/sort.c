#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
    unsigned int i = izq + 1, j = der; 
    unsigned int piv = izq;
    while(i<= j){
        if(!goes_before(a[i],a[piv]) && !goes_before(a[piv],a[j])){
            swap(a, i, j);
        }
        if(goes_before(a[i], a[piv])){
            i++;
        }
        if(goes_before(a[piv], a[j])){
            j--;
        }
    }
    swap(a, piv, j);
    piv = j;
    return piv;
}

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
       if(izq < der){
            unsigned int pivot = partition(a, izq, der);
            if(pivot != 0u) quick_sort_rec(a, izq, pivot-1); 
            quick_sort_rec(a, pivot+1, der);
    }
}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}

