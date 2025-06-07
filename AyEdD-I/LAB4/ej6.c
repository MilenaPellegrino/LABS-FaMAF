#include <stdio.h> 

void pedir_arreglo(int n_max, int a[]);

void print_array(int n_max, int a[]);

int main(){
    int n_max = 0;
    printf("Ingresa el tamano maximo del arreglo: \n"); 
    scanf("%d", &n_max);
    int a[n_max]; 
    pedir_arreglo(n_max, a[n_max]);
    print_array(n_max, a[n_max]);
    return 0; 
}

void pedir_arreglo(int n_max, int a[]){
    for (int i=0; i<n_max; i++){
        printf("Ingresa  el elemento %d del arreglo: \n", i);
        scanf("%d", &a[i]);
    }
}

void print_array(int n_max, int a[]){
    printf("Imprimiendo el array.... \n");
    for(int i=0; i<n_max; i++){
        printf("Elemento en la posicion %d ---> %d \n", i, a[i]);
    }
}