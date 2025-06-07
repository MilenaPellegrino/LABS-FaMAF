#include<stdlib.h>
#include<stdio.h>

void swap(int *a, int *b){
    int aux; 
    aux = *a;
    *a = *b; 
    *b = aux; 
}


int main(void){
    int x, y; 
    x = 6;
    y = 4;
    printf("Los valores originales son: x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("Los valores despues del swap son: x = %d, y = %d\n", x, y);
    return EXIT_SUCCESS;
}