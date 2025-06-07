#include <stdio.h>
#define MIN(x, y) ((x) < (y) ? (x) : (y))
/*
ACLARACIONES
Para resolver el programar utilice una macro 
la cual la llame "MIN" lo que hace es dado dos numero 
me calcula el minimo elemetno entre los dos. 

*/
int main(){
    int x, y, min;
    printf("Ingrese un numero para x: \n");
    scanf("%d", &x);
    printf("Ingrese un numero para y: \n");
    scanf("%d", &y);

    min = MIN(x,y); 
    printf("El minimo entre %d y %d es: %d \n", x, y, min);

    return 0;
}

