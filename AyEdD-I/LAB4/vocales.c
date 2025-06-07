#include<stdio.h>
#include<stdbool.h>

char pedir_char();
bool es_vocal(char letra);

int main(){
    char letra; 
    letra = pedir_char();
    es_vocal(letra);
    return 0;
}

bool es_vocal (char letra){
    bool es;
    switch (letra){
        case 'a':
        case 'A':
        case 'e':
        case 'E':
        case 'i':
        case 'I':
        case 'o':
        case 'O':
        case 'u':
        case 'U':  
            printf("La letra %c es vocal \n", letra);
            es = true;
            break;
        default:
            printf("La letra %c NO es una vocal \n", letra);
            es = false;
    }
    return es;
}

char pedir_char(){
    char letra;
    printf("Ingresa una letra: \n");
    scanf("%c", &letra);
    return letra;
}