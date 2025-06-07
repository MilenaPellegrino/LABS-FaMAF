#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"
#include <stdbool.h>

// Probando el tipo stack que implementamos en los casos extremos

int main(void){

    // ¿Funciona bien stack_pop() para pilas de tamaño 1? 
    stack stack_tam_1;
    stack_tam_1 = stack_empty();
    stack_push(stack_tam_1, 0); // agrego el elemento 0 a mi stack vacia

    // Si la pila queda vacía, ¿puedo volver a insertar elementos? 
    stack stack_queda_vacia; 
    stack_queda_vacia = stack_empty(); 

    // Agrego tres elementos: 
    stack_push(stack_queda_vacia, 0);
    stack_push(stack_queda_vacia, 1);
    stack_push(stack_queda_vacia, 2);

    // Los saco en un while y si saque todos los elementos intento agregar otro 
    // Como queria hacerlo rapido tato de insertar dos elementos 
    bool band = true;
    int cont = 0;
    while(band){
        if(stack_is_empty(stack_queda_vacia)){
            stack_push(stack_queda_vacia, 90);
            if(cont == 2) band = false;
        } else{
            stack_pop(stack_queda_vacia);
        }
        cont++;
    }

    // ¿La función stack_to_array() devuelve NULL para una pila vacía? 
    stack stack_vacio; 
    stack_vacio = stack_empty();
    stack_elem *se;
    se = stack_to_array(stack_vacio);
    if(se == NULL ){
        printf("La funcion stack to array devuelve null para una pila vacia\n");
    } else {
        printf("La funcacion stack to array no devuelve null para una pila vacia");
    }
    //¿Devuelve los elementos en el orden correcto?
    stack stack_array; 
    stack_array = stack_empty(); 

    // Agrego tres elementos: 
    stack_push(stack_queda_vacia, 0);
    stack_push(stack_queda_vacia, 1);
    stack_push(stack_queda_vacia, 2);

    unsigned int lenght = stack_size(stack_array);
    stack_elem *orden_array;
    orden_array = stack_to_array(stack_array);

    // Imprimimos el array para ver el orden 
    for(unsigned i = 0; i<lenght; i++){
        printf("Elemento %u = %d \n", i, orden_array[i]);
    }

    return 0;
}