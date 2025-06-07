#include<stdio.h>

void imprimir_hola();
void imprimir_chau();
int main(){
    imprimir_hola();
    imprimir_hola(); 
    imprimir_chau();
    imprimir_chau();
    return 0;
}

void imprimir_hola(){
    printf("Hola ");
}

void imprimir_chau(){
    printf("Chau ");
}