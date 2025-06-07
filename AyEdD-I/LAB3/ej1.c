#include<stdio.h> 
#include<stdbool.h>

int main(){
    int x, y, z; 
    printf("Ingresa un numero para x: \n");
    scanf("%d", &x);
    printf("\n Ingresa un numero para y: \n");
    scanf("%d", &y); 
    printf("\n Ingresa un numero para z: \n");
    scanf("%d", &z);
    printf("El valor de x + y + 1: %d\n", (x+ y +1));
    printf("El valor de z * z + y * 45 - 15 * x: %d\n", (z *z + y * 45 - 15)); 
    printf("El resultad de y - 2 == (x * 3 +1) mod 5: %d\n", (y - 2 == (x * 3 +1) % 5));
    printf ("El resultado de y / 2 * x: %d\n",(y / 2 * x)); 
    printf ("El resultado de y < x * z: %d\n", (y < x * z));

    return 0;
}
/*
Resolviendo el ejemplo de los ejercicio con mi codigo: 
Ingresa un numero para x: 
7

 Ingresa un numero para y: 
3

 Ingresa un numero para z: 
5
El valor de x + y + 1: 11
El valor de z * z + y * 45 - 15 * x: 145
El resultad de y - 2 == (x * 3 +1) mod 5: 0
El resultado de y / 2 * x: 7
El resultado de y < x * z: 1

Ingresa un numero para x: 
1

 Ingresa un numero para y: 
10

 Ingresa un numero para z: 
8
El valor de x + y + 1: 12
El valor de z * z + y * 45 - 15 * x: 499
El resultad de y - 2 == (x * 3 +1) mod 5: 0
El resultado de y / 2 * x: 5
El resultado de y < x * z: 0

En la ultima expresion (y < x * z) como en c no existen los booleanos, 
el tipo va a ser un int (0 o 1) dependiendo si se cumple o no la condicion.

*/
