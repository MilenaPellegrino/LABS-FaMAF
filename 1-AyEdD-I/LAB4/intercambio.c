#include<stdio.h>

int pedirEntero(char);
void printEntero(int, char);
int main(){
    int x, y,z; 
    x = pedirEntero('x');
    y = pedirEntero('y');
    z = pedirEntero('z');
    printf("Intercambio variables... \n");
    printEntero(y, 'x');
    printEntero(z, 'y');
    printEntero(x, 'z');
    return 0;
}

int pedirEntero(char n){
    int m;
    printf("Ingrese un valor para %c \n", n);
    scanf("%d", &m);
    return m;
}

void printEntero(int x, char n){
    printf("El valor de %c es: %d \n", n, x);
}