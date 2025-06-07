#include<stdio.h> 

int main(){
    int x, i, res; 
    printf("Ingresa el valor de x: \n");
    scanf("%d", &x);
    printf("Ingresa el valor de i: \n");
    scanf("%d", &i);
    printf("Ingresa el valor de res: \n");
    scanf("%d", &res);
    i = 2; 
    res = 1; 
    printf("Estado actual: "); 
    printf("x = %d\ni=%d\nres=%d\n ", x, i, res);
    while( (i < x) && res){
        res = res && ((x % i) != 0);
        i ++;
        printf("Estado actual: "); 
        printf("x = %d\ni=%d\nres=%d\n ", x, i, res);
    }
    printf("Estado final: "); 
    printf("x = %d\ni=%d\nres=%d\n ", x, i, res);
    return 0;
}