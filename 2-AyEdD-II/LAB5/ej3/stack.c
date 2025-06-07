#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;
    unsigned int size;
    unsigned int capacity;
};

// Declaro una capacidad incial para no hacer realloc sin necesdidad al agregar los primeros elementos
#define CAP_INICIAL 4

stack stack_empty() {
    stack s = malloc(sizeof(struct _s_stack)); // Reservamos memoria para el stack
    if (s != NULL) { // Se reservo memoria correctamente
        s->elems = malloc(CAP_INICIAL * sizeof(stack_elem)); // Reservamos memoria para el arreglo de elementos
        if (s->elems == NULL) {
            free(s);
            return NULL;
        }
        s->size = 0;
        s->capacity = CAP_INICIAL;
    }
    return s;
}


stack stack_push(stack s, stack_elem e) {
    if (s->size == s->capacity) { // Si el tamano de nuestro stack esta lleno redimensionamos el arreglo de elementos
        s->capacity *= 2;  // Como aconseja el ejercicio redimensionamos con el doble de capacidad que tenia
        stack_elem *new_elems = realloc(s->elems, s->capacity * sizeof(stack_elem));
        if (new_elems == NULL) {
            return s; // Si no pudimos reallocar memoria, devolvemos la pila sin cambios
        }
        s->elems = new_elems;
    }
    s->elems[s->size] = e;
    s->size++;
    return s;
}

stack stack_pop(stack s) {
    assert(s->size > 0); // Nos aseguramos que el stack no esté vacío
    s->size--;          // Decrementar el tamaño del stack
    s->elems[s->size] = -1;  // Pongo un valor -1 al ultimo elemento, como si no existiera
    return s;
}

unsigned int stack_size(stack s) {
    return s->size;
}

stack_elem stack_top(stack s) {
    assert(s->size > 0); // Nos aseguramos que el stack no este vacio
    return s->elems[s->size - 1];  // Resto uno porque  en c los indices empiezan en 0
}

bool stack_is_empty(stack s) {
    return s->size == 0;  
}

stack_elem *stack_to_array(stack s) {
    stack_elem *arr = malloc(s->size * sizeof(stack_elem));
    if (arr != NULL) {
        for (unsigned int i = 0; i < s->size; i++) {
            arr[i] = s->elems[i];
        }
    }
    return arr;
}

stack stack_destroy(stack s) {
    free(s->elems);
    free(s);
    return NULL;
}
