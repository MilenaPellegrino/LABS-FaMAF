#include<stdio.h>
#include<limits.h>

typedef struct _persona {
char *nombre;
int edad;
float altura;
float peso;
} persona_t;

float peso_promedio(unsigned int longitud, persona_t arr[]);
float peso_promedio(unsigned int longitud, persona_t arr[]){
    float peso_prom = 0; 
    for(unsigned int i=0; i<longitud; i++){
         peso_prom += arr[i].peso;
    }
    return (peso_prom / longitud); 
}
persona_t persona_de_mayor_edad(unsigned int longitud, persona_t arr[]);
persona_t persona_de_mayor_edad(unsigned int longitud, persona_t arr[]){
    int edad_mayor = 0;
    int pos_persona = 0; 
    for (unsigned int  i=0; i<longitud; i++){
        if(arr[i].edad > edad_mayor){
            edad_mayor = arr[i].edad;
            pos_persona = i;
        }
    }
    return arr[pos_persona];
}
persona_t persona_de_menor_altura(unsigned int longitud, persona_t arr[]);
persona_t persona_de_menor_altura(unsigned int longitud, persona_t arr[]){
    float altura_menor = INT_MAX;
    int pos_persona = 0; 
    for (unsigned int i=0; i<longitud; i++){
        if(arr[i].altura < altura_menor){
            altura_menor = arr[i].altura;
            pos_persona = i;
        }
    }
    return arr[pos_persona];
}


int main(void){
persona_t p1 = {.nombre="Paola", .edad=21, .altura=1.85, .peso=75};
persona_t p2 = {.nombre="Luis", .edad=54, .altura=1.75, .peso=69};
persona_t p3 = {.nombre="Julio", .edad=40, .altura=1.70, .peso=80};
unsigned int longitud = 3;
persona_t arr[] = {p1, p2, p3};
printf("El peso promedio es %.2f\n", peso_promedio(longitud, arr));
persona_t p = persona_de_mayor_edad(longitud, arr);
printf("El nombre de la persona con mayor edad es %s\n", p.nombre);
p = persona_de_menor_altura(longitud, arr);
printf("El nombre de la persona con menor altura es %s\n", p.nombre);

    return 0;
}