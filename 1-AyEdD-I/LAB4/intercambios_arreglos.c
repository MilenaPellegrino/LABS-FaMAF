#include<stdio.h>

void intercambiar(int tam, int a[], int i, int j);
int main(){
    int tam;
    printf("Cual es el tamano del arreglo? \n");
    scanf("%d", &tam);
    int a[tam];
    for (int i=0; i<tam; i++){
        printf("Ingrese el numero para la posicion %d del array \n", i);
        scanf("%d", &a[i]);
    }
    // Imprimimos el arreglo: 
    for (int i=0; i<tam; i++){
        printf("a[%d] = %d \n", i, a[i]);
    }
    printf("Vamos a cambiar el elemento que se encuentra en la posicion 0 por la posicion 1 \n");
    intercambiar(tam, a, 0, 1);
    // Volvemos a imprimir el arreglo: 
    for (int i=0; i<tam; i++){
        printf("a[%d] = %d \n", i, a[i]);
    }
    return 0; 
}

void intercambiar (int tam, int a[], int i, int j){
    if (i < tam && j < tam){
        int aux; 
        aux = a[i];
        a[i] = a[j];
        a[j] = aux;
    }
}