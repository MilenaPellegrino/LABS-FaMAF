#include<stdio.h>
#define ABS(x) ((x) > 0 ? x : (-1)*x);
int main(){
    int x, abs; 
    printf("Ingrese un numero para x: \n");
    scanf("%d", &x);
    abs = ABS(x);
    printf("El valor absoluto de %d es: %d\n", x, abs);
    return 0;
}