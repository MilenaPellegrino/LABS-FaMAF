#include<stdio.h>

int pedirEntero(char* n); 
void imprimirEntero(char* n, int);

int main(){
    int n;
    n = pedirEntero("n");
    imprimirEntero("n", n);

    return 0;
}

int pedirEntero(char* n){
    int x;
    printf("Ingresa un numero para %s\n", n); 
    scanf("%d", &x);
    return x;
}

void imprimirEntero(char* n, int x){
    printf("El valor de %s = %d\n", n, x);
}