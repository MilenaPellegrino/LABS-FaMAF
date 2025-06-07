#include<stdio.h>

struct comp_t {
    int menores;
    int iguales;
    int mayores;
};
struct comp_t cuantos(int tam, int a[], int elem);

struct comp_t cuantos(int tam, int a[], int elem){
    int igu = 0, men = 0, may = 0;
    struct comp_t res; // Declaro una variable res de tipo struct comp_t que es lo que voy a retornar
    for(int i=0; i<tam; i++){
        if(a[i] == elem){
            igu ++;
        }else if(a[i] < elem){
            men ++;
        } else {
            may ++;
        }
    }
    res.iguales = igu;
    res.mayores = may;
    res.menores = men;
    return res;
}
int main(){
    int tam, elem; 
    struct comp_t res;
    printf("Ingres el tamano del arreglo: \n");
    scanf("%d", &tam);
    printf("Ingrese el elemento con el que lo va a comparar: \n");
    scanf("%d", &elem);
    int a[tam];
    for(int i=0; i<tam; i++){
        printf("Ingrese el elemento %d del array: \n", i);
        scanf("%d", &a[i]);
    }
    res = cuantos(tam, a, elem);
    printf("Hay %d elementos iguales a %d \n", res.iguales, elem);
    printf("Hay %d elementos menores a %d\n", res.menores, elem);
    printf("Hay %d elementos mayores a %d \n", res.mayores, elem);
    return 0;
}