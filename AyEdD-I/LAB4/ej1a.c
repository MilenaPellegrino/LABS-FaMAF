// EJERCICIO 1 a) 
#include<stdio.h>
#include <assert.h>

void hola_hasta(int n);
int main(){
    int x; 
    printf("Ingresa un valor para x: \n");
    scanf("%d", &x);
    assert(x > 0);
    hola_hasta(x);
    return 0;
}

void hola_hasta(int n){
    while(n--){
        printf("Hola ");
    }
}
