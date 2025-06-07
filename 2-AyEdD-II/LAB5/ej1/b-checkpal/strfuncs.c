#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include<string.h>

#include "strfuncs.h"

size_t string_length(const char *str){
   int s;
   if(str == NULL){
	    printf("NULL\n");
         s=0;
	    return s;
    }
    size_t length = 0;
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}

/* Valgrind error antes de modificacion de la funcion */
char *string_filter(const char *str, char c){
    if (str == NULL) {
        printf("NULL\n");
        return NULL; 
    }

    size_t len = string_length(str);

    char *res = malloc(sizeof(char) * len); 
    if (res!= NULL) {
        size_t i = 0;
        size_t j = 0;
        while (str[i] != '\0') {
            if (str[i] != c) {
                res[j] = str[i];
                j++;
            }
            i++;
        }
        res[j] = '\0';
        
    } 
    return res;
}


bool string_is_symmetric(const char *str){
    bool res = true; 
    if (str == NULL){
        printf("NULL\n"); 
        return false;
    }

    size_t length = string_length(str); // guardo la longitud del string 
    size_t i =0;
    size_t j = length-1;
    while(i!=j){
        if(str[i] != str[j]){
            return false;
        }
        i++; 
        j--;
    }
    return res;
}
