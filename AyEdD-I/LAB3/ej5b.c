#include <stdio.h>

int main(){
    int x, y, i; 
    printf("Ingresa el valor de x: \n");
    scanf("%d", &x);
    printf("Ingresa el valor de y: \n");
    scanf("%d", &y);
    printf("Ingresa el valor de i: \n");
    scanf("%d", &i);
    i = 0;
    while(x >= y){
        x -= y; 
        i ++;
        printf("Estado actual: "); 
        printf("x = %d\ny=%d\ni=%d\n ", x, y, i);
    }
    return 0;
}