#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    if(x>=0) y = x;
    else y = -(x);
}

int main(void) {
    int a=0, res=0;
    a = -10;
    absolute(a, res);
    printf("%d\n", res);
    return EXIT_SUCCESS;
}

/*
    En el algoritmos del lenguaje del teorico-practico, el valor que se imprimiria seria 10. 
    En C, el valor que se muestra por consola es 0 (el valor original de res).
    Esto se debe a que los valores que le paso a absolute son de tipo "int", y nuestra funcion no devuelve nada. 
    Por lo tanto todo lo que hace la funcion muere en el scope de la misma 
    O sea si modificamos nuestra funcion absolute e imprimir por pantalla los valores que tiene, ahi se se van a modificar, pero en el main no se modifica nada. 
    Ya que todo lo que hace absolute muere en el scope limitado que tiene, y no va a pasar nada ya que todos los parametros son del tipo int. 
*/