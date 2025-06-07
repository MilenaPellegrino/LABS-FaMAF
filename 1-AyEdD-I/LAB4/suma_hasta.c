#include <stdio.h>

// Utilizando la formula de Gauss
int suma_hasta(int n);

// Utilizando ciclo
int suma_hasta2 (int n);

int main(){
    int x; 
    printf("Ingresa un numero: \n");
    scanf("%d", &x);
    suma_hasta(x);
    suma_hasta2(x);
    return 0;
}

// Utilizando la formula de gauss
int suma_hasta(int n){
    int res; 
    res = ((n * (n +1)) / 2);
    printf("La suma de los primeros %d es: %d \n", n, res);
    return res;
}

//Utilizando ciclos 
int suma_hasta2(int n){
    int res = 0; 
    for(int i=0; i<=n; i++){
        res += i;
    }
    printf("La suma de los primeros %d es: %d \n", n, res);
    return res;
}