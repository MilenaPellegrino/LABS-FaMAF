#include <stdio.h>

struct div_t {
    int cociente;
    int resto;
};

// Cuando le pedi los datos al usuario me asegure que el divisor no sea 0.
struct div_t division(int x, int y) {
    struct div_t resultado; // Declaro una variable "resultado" de tipo struct div_t
        resultado.cociente = x / y;
        resultado.resto = x % y;
    return resultado;
}

int main() {
    int dividendo, divisor;
    struct div_t resultado;
    printf("Ingrese el dividendo (el que va arriba por si no aprobaste la primaria): ");
    scanf("%d", &dividendo);
    printf("Ingrese el divisor (si antes era el de arriba ahora es el de abajo): ");
    scanf("%d", &divisor);

    while (divisor == 0 ){
        printf("Che esto no es ni teoria de numeros ni algebra abastracta \n EL DIVISOR NUNCA PUEDE SER CERO \n Ingresa otro numero por favor: \n");
        scanf("%d", &divisor);
    }
    resultado = division(dividendo, divisor);

    printf("Cociente: %d\n", resultado.cociente);
    printf("Resto: %d\n", resultado.resto);

    return 0;
}
