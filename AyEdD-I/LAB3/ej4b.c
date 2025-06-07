#include<stdio.h>

int main(){
    int x, y, z, m;
    printf("Ingresa el valor de x: \n");
    scanf("%d", &x);
    printf("Ingresa el valor de y: \n");
    scanf("%d", &y);
    printf("Ingresa el valor de z: \n");
    scanf("%d", &z);
    printf("Ingresa el valor de m: \n");
    scanf("%d", &m);
    printf("Estado actual: ");
    printf("\n x = %d\n", x);
    printf("\n y = %d\n", y);

    if (x < y){
        m = x; 
        printf("Estado actual: ");
        printf("\n x = %d\n", x);
        printf("\n y = %d\n", y);
    } else {
        m = y; 
        printf("Estado actual: ");
        printf("\n x = %d\n", x);
        printf("\n y = %d\n", y);
    }

    if(m < z){
        printf("Estado actual: ");
        printf("\n x = %d\n", x);
        printf("\n y = %d\n", y);
        printf("\n z = %d\n", z);
        printf("\n m = %d\n", m);

    } else{
        m = z; 
        printf("Estado actual: ");
        printf("\n x = %d\n", x);
        printf("\n y = %d\n", y);
        printf("\n z = %d\n", z);
        printf("\n m = %d\n", m);
    }
    printf("Estado final: ");
    printf("\n x = %d\n", x);
    printf("\n y = %d\n", y);
    printf("\n z = %d\n", z);
    printf("\n m = %d\n", m);
    return 0;
}

/*
EJEMPLOS DE USO: 

Ingresa el valor de x: 
5
Ingresa el valor de y: 
4
Ingresa el valor de z: 
8
Ingresa el valor de m: 
0
Estado actual: 
 x = 5

 y = 4
Estado actual: 
 x = 5

 y = 4
Estado actual: 
 x = 5

 y = 4

 z = 8

 m = 4
Estado final: 
 x = 5

 y = 4

 z = 8

 m = 4

*/