#include<stdio.h>
//#include "./entradas2.c"

#include<stdio.h>
int pedirEntero(char n); 
void imprimirEntero(char n, int);
void condicionales();
void entradas1();
int main(){
    condicionales();
    entradas1();
    return 0;
}

int pedirEntero(char n){
    int x;
    printf("Ingresa un numero para %c\n", n); 
    scanf("%d", &x);
    return x;
}

void imprimirEntero(char n, int x){
    printf("El valor de %c = %d\n", n, x);
}

void condicionales(){
        int x, y, z, m;
    x = pedirEntero('x');
    y = pedirEntero('y');
    z = pedirEntero('z');
    m = pedirEntero('m');

    if (x < y){
        m = x; 
        printf("Estado actual: ");
        imprimirEntero('x', x);
        imprimirEntero('y', y);
        imprimirEntero('z', z);
        imprimirEntero('m', m);
    } else {
        m = y; 
        printf("Estado actual: ");
        imprimirEntero('x', x);
        imprimirEntero('y', y);
        imprimirEntero('z', z);
        imprimirEntero('m', m);
    }

    if(m < z){
        printf("Estado actual: ");
        imprimirEntero('x', x);
        imprimirEntero('y', y);
        imprimirEntero('z', z);
        imprimirEntero('m', m);

    } else{
        m = z; 
        printf("Estado actual: ");
        imprimirEntero('x', x);
        imprimirEntero('y', y);
        imprimirEntero('z', z);
        imprimirEntero('m', m);
    }
    printf("Estado final: ");
        imprimirEntero('x', x);
        imprimirEntero('y', y);
        imprimirEntero('z', z);
        imprimirEntero('m', m);
}

void entradas1(){
    int x, y, z; 
    x = pedirEntero('x');
    y = pedirEntero('y');
    z = pedirEntero('z');
    printf("El valor de x + y + 1: %d\n", (x+ y +1));
    printf("El valor de z * z + y * 45 - 15 * x: %d\n", (z *z + y * 45 - 15)); 
    printf("El resultad de y - 2 == (x * 3 +1) mod 5: %d\n", (y - 2 == (x * 3 +1) % 5));
    printf ("El resultado de y / 2 * x: %d\n",(y / 2 * x)); 
    printf ("El resultado de y < x * z: %d\n", (y < x * z));
}


/*
En este ejercicio, podria seguir escriiendo funciones para no repetir codigo, por ejemplo que me imprima el estado de x, y, z, m. 
Las ventajas de esto, es que queda el codigo mas legible, y no repetimos codigo. 

Podria seguir con muchas mas ejercicios, del proyecto, ya que muchos se basaban en pedir un entero al usuario y asi varias veces, y despues imprimirlo, y simplemente reemplazar ese bloque de codigo donde pido el entero al usuario por el pedirentero() y donde lo imprimo por imprimirentero()

*/