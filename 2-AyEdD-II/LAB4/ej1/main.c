/*
  @file main.c
  @brief Main program function implementation
*/
#include <stdio.h>
#include <stdlib.h>

/** @brief structure which represent a person */
typedef struct _person {
    int age;
    char name_initial;
} person_t;

/**
 * @brief Main program function
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(void) {

    int x = 1;
    person_t m = {90, 'M'};
    int a[] = {0, 1, 2, 3};

   // Cambiamos el valor de la variable "x"
    int *p = NULL;
    p = &x;
    *p = 9;
    
    // Cambiamos el valor de la edad de la persona 
    p = &m.age;
    *p = 100;

    // Cambiamos el valor de a[1]
    p = &a[1];
    *p = 42; 

    // Cambiamos el valor de la inicial del nombre de la persona
    char *c = NULL;
    c = &m.name_initial;
    *c = 'F';

    printf("x = %d\n", x);
    printf("m = (%d, %c)\n", m.age, m.name_initial);
    printf("a[1] = %d\n", a[1]);

    return EXIT_SUCCESS;
}

