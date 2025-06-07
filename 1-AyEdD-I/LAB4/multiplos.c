#include<stdio.h>
#include<stdbool.h>

bool todos_pares(int tam, int a[]);
bool existe_multiplo(int m, int tam, int a[]);

int main(){
    int tam;
    int opc = 0;
    bool result;
    printf("Ingrese el tamano maximo del arreglo: \n");
    scanf("%d", &tam);
    int a[tam];
    for(int i =0; i<tam; i++){
        printf("Ingrese el elemento de la posicion %d del arreglo: \n", i);
        scanf("%d", &a[i]);
    }
    printf("Elige que quieres realizar con el arreglo: \n");
    printf("1- Te digo si los elementos de tu array son todos pares. \n"); 
    printf("2- Te digo si existe algun multiplo 'm' en el arreglo \n");
    scanf("%d", &opc);
    if(opc == 1){
        printf("Elegiste la opcion 1: <Ejecutaremos la funcion todos_pares> \n"); 
        result = todos_pares(tam, a);
        printf("%d", result);
    } else if (opc == 2){
        int m;
        printf("Elegiste la opcion 2: <Ejecutaremos la funcion existe_multiplo> \n"); 
        printf("Para eso ingrese un valor para m: \n");
        scanf("%d", &m);
        result = existe_multiplo(m, tam, a);
        printf("%d", result);
    } else {
        printf("Opcion  no valida. \n");
    }
    return 0; 
}

bool todos_pares(int tam, int a[]){
    bool res =  true; 
    for(int i =0; i<tam; i++){
        if(a[i] % 2 != 0){
            res = false;
        }
    }
    return res;
}
bool existe_multiplo(int m, int tam, int a[]){
    bool res = false;
    for (int i=0; i<tam; i++){
        if(a[i] % m == 0){
            res = true;
            break;
        }
    }
    return res; 
}