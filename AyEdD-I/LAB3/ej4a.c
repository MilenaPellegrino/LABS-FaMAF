#include<stdio.h>

int main(){
    int x, y;
    printf("Ingresa el valor de x: \n");
    scanf("%d", &x);
    printf("Ingresa el valor de y: \n");
    scanf("%d", &y);
    printf("Estado actual: ");
    printf("\n x = %d\n", x);
    printf("\n y = %d\n", y);

    if (x >= y){
        printf("Estado actual: ");
        printf("\n x = %d\n", x);
        printf("\n y = %d\n", y);
        x =0;
    } else{
        printf("Estado actual: ");
        printf("\n x = %d\n", x);
        printf("\n y = %d\n", y);
        x = 2;
    }
    printf("Estado final: ");
    printf("\n x = %d\n", x);
    printf("\n y = %d\n", y);
    return 0;
}

/*
EJEMPLO DE USO: 
Ingresa el valor de x: 
3
Ingresa el valor de y: 
1
Estado actual: 
 x = 3

 y = 1
Estado actual: 
 x = 3

 y = 1
Estado final: 
 x = 0

 y = 1

Ingresa el valor de x: 
100
Ingresa el valor de y: 
1
Estado actual: 
 x = 100

 y = 1
Estado actual: 
 x = 100

 y = 1
Estado final: 
 x = 0

 y = 1
 
*/
