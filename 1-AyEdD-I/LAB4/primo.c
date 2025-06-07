#include<stdio.h> 
#include<math.h>
#include<stdbool.h>

bool es_primo(int n);
bool es_primo(int n){
    if (n <= 1){
        return false;
    }
    for(int i=2; i<=(sqrt(n)); i++){ 
        if(n % i == 0){
            return false; 
        }
    }
    return true;
}
int nesimo_primo(int N);
int nesimo_primo(int N){
    bool band = true;
    int cont = 0;
    int i = 0;
    while (band){
        if(es_primo(i)){
            cont ++;
        }
        if(cont == N){
            band = false;
        }
        i ++;
    } 
    return i -1; 
} 

int  main(){
    int n = 0;
    int pos; 
    printf("Ingresa un numero: \n");
    scanf("%d", &n);
     while(n < 0){
        printf("Ingrese un numero: \n");
        scanf("%d", &n);
    } 
    pos = nesimo_primo(n);
    printf("%d-esimo primo es: %d\n", n, pos);
    

    return 0; 
}