#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void absolute(int x, int *y) {
    if (x>=0) *y=x;
    else *y = (-x);
}

int main(void) {
    int a=0, res=0;  // No modificar esta declaración
    // --- No se deben declarar variables nuevas ---
    a = -10;
    absolute(a, &res);
    printf("%d\n", res);
    assert(res >= 0 && (res == a || res == -a));
    return EXIT_SUCCESS;
}

/*
    Si se muestra el valor correcto con respecto al algoritmos del teorico-practico. 
    El parametros int *y de absolute es de tipo in, ya que no se modifica dentro de la funcion absolute, solo se esta modificando el valor al que apunta. 
    C solo tiene disponible parametros de tipo in, pero se puede hacer "truquitos" como este, al utilizar punteros para modificar variables y hacerlas ver como si fuera de tipo "out", pero en realidad solamente son de tipo in. 
*/
