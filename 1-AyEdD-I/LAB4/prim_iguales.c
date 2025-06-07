#include<stdio.h>

int prim_iguales(int tam, int a[]);
int prim_iguales(int tam, int a[]){
    int cont =0; 
    for(int i=0; i<tam; i++){
        if(a[i] == a[i+1]){
            cont ++;
        } else {
            break;
        }
    }  
    return cont;
}

int main(){
    int tam = 5;
    int a[tam];
    int cont; 
    for(int i=0; i<tam; i++){
        printf("Ingresa el elemento %d del array: \n", i);
        scanf("%d", &a[i]);
    }
    cont = prim_iguales(tam, a) + 1;
    printf("Hay %d elementos primeros iguales \n", cont);
    return 0;
}