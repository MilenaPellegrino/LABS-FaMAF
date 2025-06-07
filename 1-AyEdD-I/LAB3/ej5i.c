#include<stdio.h>

int main(){
    int i;
    printf("Escribe un numero para i: \n");
    scanf("%d", &i);
    printf("Estado actual: \n"); 
    printf("\n i = %d\n", i);
    while (i != 0)
    {
        i =0 ;
        printf("Estado actual: \n"); 
        printf(" i = %d\n", i);
    }
    printf("Estado Final: \n"); 
    printf(" i = %d\n", i);   

    return 0;
}

/*
EJEMPO DE USO 
Escribe un numero para i: 
400
Estado actual: 

 i = 400
Estado actual: 
 i = 0
Estado Final: 
 i = 0


*/