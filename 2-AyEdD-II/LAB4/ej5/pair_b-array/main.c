#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "pair.h"    /* TAD Par         */

static
void show_pair(pair_t p) {
    printf("(%d, %d)\n", p.values[0], p.values[1]);
}


int main(void) {
    pair_t p, q;
    // Nuevo par p
    p = pair_new(3, 4);

    // Se muestra el par por pantalla
    printf("p = ");
    show_pair(p);

    // Nuevo par q con elementos de p intercambiados
    q = pair_swapped(p);

    // Se muestra q
    printf("q = ");
    show_pair(q);

    // Se destruyen p y q
    p = pair_destroy(p);
    q = pair_destroy(q);
    
    return EXIT_SUCCESS;
}


/*

Al compilarlo con el mismo archivo main que en el pair a-tuple, no compila ya que esta especificado para el tipo pair_t que tenia dos campos: fst, snd. Pero ahora solo tiene un campo llamado values, el cual es un arreglo que almacena dos valores 

El TAD Logra encapsulamiento esto se debe a que estamos trabajando con una abstraccion, no tenemos idea como esta implementado.

*/