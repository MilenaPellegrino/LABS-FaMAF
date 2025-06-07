#include<stdio.h>
#include <stdbool.h>

typedef char clave_t;
typedef int valor_t;

struct asoc {
    clave_t clave;
    valor_t valor;
};

bool asoc_existe(int tam, struct asoc a[], clave_t c);
bool asoc_existe(int tam, struct asoc a[], clave_t c){
    for(int i =0; i<tam; i++){
        if(a[i].clave == c){
            return true;
        } 
    }
    return false;
}

int main(){
    int tam = 3; 
    struct asoc a[tam]; 
    char clave; 

    // Pedimos los datos al usuario 
    for (int i=0; i<tam; i++){
        printf("Ingresa la clave %d -> ", i);
        scanf(" %c", &a[i].clave);
        printf("\n Ingresa el valor %d -> ", i);   
        scanf("%d", &a[i].valor);  
    }
    // Pedimos la clave 
    printf("Ingresa la clave que quieres verificar: \n");
    scanf(" %c", &clave);
    
    // Vemos si la clave existe 
    if(asoc_existe(tam, a, clave) == true){
        printf("La clave se encuentra en el arreglo. \n");
    } else{
        printf("La clave no se encuentra en el arreglo \n");
    }
    return 0; 
}
