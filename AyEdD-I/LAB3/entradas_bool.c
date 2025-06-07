#include <stdio.h>
#include <stdbool.h>

bool pedir_booleano(char n);
void imprimir_booleano(bool x, char n);

int main() {
    bool val = true;
    bool n = pedir_booleano('n');

    if (n == false) {
        printf("El valor introducido es False\n");
    } else {
        printf("El valor introducido es True\n");
    }
    imprimir_booleano(val, 'n');

    return 0;
}

bool pedir_booleano(char n) {
    int res;
    printf("Introduce un valor booleano (0/1) para %c: ", n);
    scanf(" %d", &res);

    if (res == 1) {
        return false;
    } else {
        return true;
    }
}

void imprimir_booleano(bool x, char n){
    if (x == true) {
        printf("El valor de %c es %d\n", n, x);
    } else {
        printf("El valor de %c es %d", n, x);
    }
}


