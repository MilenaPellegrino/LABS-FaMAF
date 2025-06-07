#include <stdio.h>
int sumatoria(int tam, int a[]);

int main (){
    int tam; 
    printf("Ingresa el numero del tamano del arreglo: \n"); 
    scanf("%d", &tam);
    int a[tam], sum;
    // Como el ejercicio dice que pidamos los datos del arreglo en la funcion main lo hacemos aca: 
    for (int i=0; i<tam; i++){
        printf("Ingresa el elemento del array en la posicion %d \n", i);
        scanf("%d", &a[i]);
    }
    sum = sumatoria(tam, a);
    printf("La sumatoria del array es: %d \n", sum);
    return 0; 
}


int sumatoria(int tam, int a[]){
    int res = 0;
    for (int i=0; i< tam; i++){
        res += a[i];
    }
    return res;
}