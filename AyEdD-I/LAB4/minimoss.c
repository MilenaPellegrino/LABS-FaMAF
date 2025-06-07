#include<stdio.h> 
#include<limits.h>
#define MIN(a, b) ((a)<(b) ? (a)  : (b))

int minimo_pares(int tam, int a[]);
int minimo_pares(int tam, int a[]){
    int min = INT_MAX;
    for(int i=0; i<tam; i++){
        if(a[i] < min && a[i] % 2 == 0){
            min = a[i];
        }
    }
    return min;
}
int minimo_impares(int tam, int a[]);
int minimo_impares(int tam, int a[]){
    int min = 100000000;
    for(int i=0; i<tam; i++){
        if(a[i] < min && a[i] % 2 != 0){
            min = a[i];
        }
    }
    return min;
}

int main(){
    int tam = 5; 
    int a[tam];
    for(int i =0; i<tam; i++){
        printf("Ingresa el elemento para la posicion %d del arreglo: \n", i);
        scanf("%d", &a[i]);
    }
    int min_par = minimo_pares(tam, a);
    int min_impar = minimo_impares(tam, a);
    int min_abs = MIN(min_par, min_impar);
    printf("El elemento par mas pequeno es: %d\n", min_par);
    printf("El elemento minimo impar es: %d\n", min_impar);
    printf("El elemento minimo absoluto es: %d\n", min_abs);
    return 0; 
}