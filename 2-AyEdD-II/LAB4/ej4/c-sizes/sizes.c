#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "data.h"

void
print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

int main(void) {

    data_t messi1 = {"Leo Messi", 36, 169};
    print_data(messi1);

    printf("name-size  : %lu bytes\n"
           "age-size   : %lu bytes\n"
           "height-size: %lu bytes\n"
           "data_t-size: %lu bytes\n", sizeof(messi1.name), sizeof(messi1.age), sizeof(messi1.height), sizeof(messi1));

    // Agrego otro printf para ver si el tamano del campo "name" depende de la longitud del nombre 
    // Ya que estoy modifico los otros campos, suponiendo que messi tiene 0 anos y es mucho mas alto 
    data_t messi2 = {"Leonel Andres Messi", 0, 180};
    print_data(messi2);

    printf("name-size  : %lu bytes\n"
           "age-size   : %lu bytes\n"
           "height-size: %lu bytes\n"
           "data_t-size: %lu bytes\n", sizeof(messi2.name), sizeof(messi2.age), sizeof(messi2.height), sizeof(messi2));

    // Comprobamos que los campos no depende de la longitud de nada, simplemente es la memoria total que esta reservada, que puede etar o no utilizada totalmente. 
    
    printf("\n\nDirecciones de memoria:\n");

    printf("name-size  : %lu bytes  | direccion de memoria: %p \n"
           "age-size   : %lu bytes  | direccion de meoria:  %p \n"
           "height-size: %lu bytes  | direccion de memoria: %p \n"
           "data_t-size: %lu bytes  | direccion de memoria: %p \n\n",
            sizeof(messi2.name), (void *)&messi2.name, sizeof(messi2.age), (void *)&messi2.age, sizeof(messi2.height), (void *)&messi2.height, sizeof(messi2), (void *)&messi2);
    return EXIT_SUCCESS;
}

/*
Lo que imprime por pantalla es lo siguiente: 
name-size  : 30 bytes
age-size   : 4 bytes
height-size: 4 bytes
data_t-size: 40 bytes

Direcciones de memoria:
name-size  : 30 bytes  | direccion de memoria: 0x7ffe5810cde0 
age-size   : 4 bytes  | direccion de meoria:  0x7ffe5810ce00 
height-size: 4 bytes  | direccion de memoria: 0x7ffe5810ce04 
data_t-size: 40 bytes  | direccion de memoria: 0x7ffe5810cde0 

La suma de los miembros no coincide con el total ya que 40 != 30 + 4 + 4 = 38 

Es decir, el tamaño total de la estructura data_t no es simplemente la suma de los tamaños de sus miembros debido al concepto de alineación de datos en la memoria.

LO raro que encuentro en las direcciones de memoria es que los campos estan ordenadas asi: 

name | age | height 
cuando nosotros en el codigo tenemos el height antes que el age 

*/