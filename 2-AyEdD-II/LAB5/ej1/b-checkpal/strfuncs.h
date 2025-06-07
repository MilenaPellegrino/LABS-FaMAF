#ifndef _STRFUNCS_H
#define _STRFUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

// Calcula la longitud de la cadena apuntada por str
size_t string_length(const char *str);

// Devuelve una nueva cadena en memoria dinámica que se obtiene tomando los caracteres de str que son distintos del caracter c
char *string_filter(const char *str, char c);

//ndica si la cadena apuntada por str es simétrica en cuanto que el primer caracter coincide con el último, el segundo con el penúltimo, etc
bool string_is_symmetric(const char *str);

#endif /* _STRFUNCS_H */

