#ifndef _LIST_H
#define _LIST_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node_of_T *list;
typedef int list_elem;

/* === Constructors === */

list empty();
/* create an empty list */

list addl(list_elem e, list l);
/* Agrega el elemento e al principio de la lista l */

/* Destroy */
list destroy(list l);
/* LIbera memoria si es necesario*/

/* === Operations === */
bool is_empty(list l);
/* Devuelve true si l es una lista vacia */

list_elem head(list l);
/* Retorna el primer elemento de la lista */
/*
    PRE: not is_empty(l)
 */

list tail(list l);
/* Elimina el primer elemento de la lista l*/
/*
    PRE: not is_empty(l)
*/

list addr(list l, list_elem e);
/* Agrega el elemento e al final (por la derecha) de la lista l */

int length(list l);
/* Devuelve la cantidad de elementos de la lista l */

list concat(list l1, list l2);
/* Agrega todos los elementos de l1 al final de l2 */

list_elem index(list l, int n);
/* Devuelve el n-esimo elemento de la lista */
/*
    PRE: length(l) > n
*/

list take(list l, int n);
/* Se queda solo con los primeros n elementos de la lista y elimina los otros */

list drop(list l, int n);
/* Elimina todos los primeros n elementos de l*/

list copy_list(list l);
/* Copia todos los elementos de l a una nueva lista */

#endif