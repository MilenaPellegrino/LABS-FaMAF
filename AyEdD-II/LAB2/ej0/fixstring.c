#include <stdbool.h>
#include <assert.h>


#include "fixstring.h"

unsigned int fstring_length(fixstring s) {
    unsigned int longitud =0; 
    int i = 0;
    while(s[i] != '\0'){
        longitud++;
        i++;
    }
    return longitud;
}

bool fstring_eq(fixstring s1, fixstring s2) {
    int i =0;
    while(s1[i] != '\0' && s2[i] != '\0'){
        if(s1[i]!=s2[i]) return false;
        i++;
    }
    return true;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
   int i=0;
    while(s1[i] != '\0' && s2[i] != '\0'){
        if(s1[i]>s2[i]) return false;
        i++;
    }
    return true;
}

