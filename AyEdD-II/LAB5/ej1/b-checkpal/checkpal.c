#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strfuncs.h"

#define MAX_LENGTH 20

#define SIZEOF_ARRAY(s) (sizeof(s) / sizeof(*s))

int main(void) {
    char user_input[MAX_LENGTH];
    char ignore_chars[] = {' ', '?', '!', ',', '-', '.'};
    char *filtered=NULL;
    char *aux = NULL;
    printf("Ingrese un texto (no más de %d símbolos) para verificar palíndromo: ", MAX_LENGTH);
    //scanf("%s", user_input);
    fgets(user_input, MAX_LENGTH, stdin); // Leer una línea de la entrada estándar (teclado)
    unsigned int lenght = string_length(user_input);
    user_input[lenght] = '\0';

    /* Valgrind error antes de modificacion de memory leaks */
    filtered = string_filter(user_input, ignore_chars[0]);
    aux = filtered;
    /*for (unsigned int i=0; i < SIZEOF_ARRAY(ignore_chars); i++) {
        filtered = string_filter(filtered, ignore_chars[i]);
    } */
    for (unsigned int i = 0; i < SIZEOF_ARRAY(ignore_chars); i++) {
        filtered = string_filter(filtered, ignore_chars[i]); 
        free(aux);
        aux = filtered;
    }

    printf("El texto:\n\n"
            "\"%s\" \n\n"
            "%s un palíndromo.\n\n", user_input, string_is_symmetric(filtered) ? "Es": "NO es");
    //free(filtered); // libero la memoria que reserve para filtered
    free(aux);
    return EXIT_SUCCESS;
}

/*
AL usar valgrind me dice esto (resumidamente dejando lo mas importante)

==31178== HEAP SUMMARY:
==31178==     in use at exit: 56 bytes in 7 blocks
==31178==   total heap usage: 9 allocs, 2 frees, 2,104 bytes allocated

==31178== 8 bytes in 1 blocks are definitely lost in loss record 1 of 2
==31178==    at 0x4843828: malloc 
==31178==    by 0x109276: string_filter 
==31178==    by 0x10942D: main

==31178== 48 bytes in 6 blocks are definitely lost in loss record 2 of 2
==31178==    at 0x4843828: malloc 
==31178==    by 0x109276: string_filter 
==31178==    by 0x109453: main 

==31178== LEAK SUMMARY:
==31178==    definitely lost: 56 bytes in 7 blocks

==31178== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)

vemos uqe tenemos algo llamado "definitely lost" que esto nos esta indicando perdida de memoria 
Esto significa que asignamos memoria dinamicamente usando malloc, pero nunca la liberamos usando free. 
LO cual es un GRAN PROBLEMA, porque puede llevar a muchos problemas. 

Ademas valgrind nos da mucha mas info sobre esto, vemos detalladamente lo que pasa:

    "8 bytes in 1 blocks are definitely lost:"
        Se perdio un bloque de memoria de 8 bytes

    "in loss record 1 of 2:""
        Esto solo nos dice que es el primer bloque de perdida y que en total hay dos

    "at 0x4843828: malloc:"
        Aca nos dice cual es la funcion que asigno memoria, en este caso es malloc, pero podriamos estar utilizando otra como calloc, realloc, etc. 

    "by 0x109276: string_filter:"
        Esto nos dice la funcion donde asignamos la memoria y no la liberamos.

    "by 0x10942D: main:"
        y por ultimo aca nos indica la funcion principal en la que usamos string_filter

    Y  en el otro bloque de perdida la unica diferencia es esta: 
    "48 bytes in 6 blocks are definitely lost in loss record 2 of 2"
    Que nos dice que se perdieron 6 bloque de memoria de 48 bytes.
    (si vemos el codigo vemos que tiene sentido, ya que llamamos a la funcion string_filter varias veces ya que esta dentro de un ciclo for)

    En resumen vemos que el problema esta que en la funcion string_filter, asignamos memoria dinamicamente pero nunca la liberamos, entonces solucionamos el problema (en solucion) simplemente liberando la memoria que utilizamos, para que ese espacio en memoria este disponible para usar posteriormente. 

*/
