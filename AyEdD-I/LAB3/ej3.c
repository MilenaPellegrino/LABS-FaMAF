#include<stdio.h>

void changeTo5 ();
void sum();
void sum2();

int main(){
    changeTo5();
    changeTo5();
    changeTo5();
    sum();
    sum();
    sum();
    sum2();
    sum2();
    sum2();
    return 0; 
}

void changeTo5 (){
    int x;
    printf("Flaco ingresa un numero para x porfa: \n");
    scanf("%d", &x); 
    
    x = 5; 
    printf("Ahora tu estado actual es: %d\n", x);
}

void sum(){
    int x, y;
    printf("\nIngresa el valor de x porfa: \n"); 
    scanf("%d", &x); 
    printf("\nLocoo y ahora el de Y: \n"); 
    scanf("%d", &y);
    x += y; 
    printf("\nEstado actual:  \n");
    printf(" X= %d", x);
    printf(" Y= %d\n", y);
    printf("\nAca modificamos el valor de y... \n");
    y += y; 
    printf("\nEstado actual:  \n");
    printf(" X -> %d", x);
    printf(" Y -> %d\n", y);
}

void sum2(){
    int x, y;
    printf("\nIngresa el valor de x porfa: \n"); 
    scanf("%d", &x); 
    printf("\nLocoo y ahora el de Y: \n"); 
    scanf("%d", &y);
    y +=y; 
    printf("\nEstado actual:  \n");
    printf(" X= %d", x);
    printf(" Y= %d\n", y);
    printf("\nAca modificamos el valor de x... \n");
    x+=y; 
    printf("\nEstado actual:  \n");
    printf(" X -> %d", x);
    printf(" Y -> %d\n", y);

}

/*
EJEMPLO DE EJECUCION 

1 a) 
Flaco ingresa un numero para x porfa: 
10
Ahora tu estado actual es: 5
Flaco ingresa un numero para x porfa: 
20
Ahora tu estado actual es: 5
Flaco ingresa un numero para x porfa: 
30
Ahora tu estado actual es: 5

1 b) 
Ingresa el valor de x porfa: 
10

Locoo y ahora el de Y: 
15

Estado actual:  
 X= 25 Y= 15

Aca modificamos el valor de y... 

Estado actual:  
 X -> 25 Y -> 30

Ingresa el valor de x porfa: 
23

Locoo y ahora el de Y: 
2

Estado actual:  
 X= 25 Y= 2

Aca modificamos el valor de y... 

Estado actual:  
 X -> 25 Y -> 4

Ingresa el valor de x porfa: 
10

Locoo y ahora el de Y: 
5

Estado actual:  
 X= 15 Y= 5

Aca modificamos el valor de y... 

Estado actual:  
 X -> 15 Y -> 10

1 c) 
Ingresa el valor de x porfa: 
6

Locoo y ahora el de Y: 
7

Estado actual:  
 X= 6 Y= 14

Aca modificamos el valor de x... 

Estado actual:  
 X -> 20 Y -> 14

Ingresa el valor de x porfa: 
10

Locoo y ahora el de Y: 
9

Estado actual:  
 X= 10 Y= 18

Aca modificamos el valor de x... 

Estado actual:  
 X -> 28 Y -> 18

Ingresa el valor de x porfa: 
6

Locoo y ahora el de Y: 
1

Estado actual:  
 X= 6 Y= 2

Aca modificamos el valor de x... 

Estado actual:  
 X -> 8 Y -> 2

*/