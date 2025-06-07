#include<stdio.h>
#include<limits.h>
struct datos_t {
float maximo;
float minimo;
float promedio;
};
struct datos_t stats(int tam, float a[]);
struct datos_t stats (int tam, float a[]){
    float min = INT_MAX, max = INT_MIN, sum =0;
    struct datos_t res;
    for(int i=0; i<tam; i++){
        // Verifico si es el minimo o maximo
        if (a[i] <= min){
            min = a[i];
            sum += a[i]; // Sumo el elemento a mi variable sum 
        } else if (a[i] >= i)
        {
            max = a[i];
            sum += a[i];
        } 
    }
    res.maximo = max; 
    res.minimo = min;
    res.promedio = sum / tam; 
    return res;
}

int main(){
    int tam = 4; 
    float a[tam];
    struct datos_t res;
    // Pedimos los datos al usuario
    for (int i=0; i<tam; i++){
        printf("Ingrese el elemento %d del array \n ", i);
        scanf("%f", &a[i]);
    }
    res = stats(tam, a);
    // Imprimos los tres resultados 
    printf("El elemento minimo del array es: %2.f \n", res.minimo);
    printf("El elemento maximo del array es: %2.f \n", res.maximo);
    printf("El promedio del array es: %.2f \n", res.promedio);
    return 0;
}