#include<stdio.h>

int pedirEntero(void); 
void imprimirEntero(int);

int main(){
    pedirEntero();
    imprimirEntero(3);

    return 0;
}

int pedirEntero(void){
    int x;
    printf("Ingresa un numero para x: \n"); 
    scanf("%d", &x);
    return x;
}

void imprimirEntero(int x){
    printf("El valor de x es: %d\n", x);
}