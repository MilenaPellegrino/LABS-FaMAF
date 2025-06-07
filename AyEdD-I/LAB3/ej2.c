#include<stdio.h>

int main(){
    int x, y, z, b, w; 
    printf("Valor de x: \n"); 
    scanf("%d", &x); 
    printf("Valor de y: \n"); 
    scanf("%d", &y); 
    printf("Valor de z: \n"); 
    scanf("%d", &z); 
    printf("Valor de b: \n"); 
    scanf("%d", &b); 
    printf("Valor de w: \n"); 
    scanf("%d", &w); 
    printf("1: %d\n", x % 4 == 0); 
    printf("1: %d\n", (x + y == 0 && y - x == (-1) * z)); 
    printf ("0: %d\n", (!b && w));

    /*
    Valor de x: 
    8
    Valor de y: 
    -8
    Valor de z: 
    16
    Valor de b: 
    10
    Valor de w: 
    15
    1: 1
    1: 1
    0: 0

    Por lo tanto el valor de las variables son:
    x = 8
    y = -8
    z = 16 
    b = 10
    w = 15 
    */
   
    return 0; 
}