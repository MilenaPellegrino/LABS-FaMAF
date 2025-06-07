#include <stdlib.h>
#include <stdio.h>
#include "sorted.h"
#include <stdbool.h>
#define MAX_SIZE 1000

void reoder(unsigned int indexes[], char letters[], char sorted[], unsigned int length){
    unsigned int i = 0;
    while((i<length) && length <= MAX_SIZE){
        sorted[indexes[i]] = letters[i];
        i++;
    }
}
static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size){
    FILE *file; 
    file = fopen(path, "r");
    if (file == NULL){
        perror("Error al abrir el archivo \n");
        return 0;
    }
    unsigned int count = 0; 
    while(!feof(file) && count<max_size){
        if(fscanf(file, "%u -> *%c*", &indexes[count], &letters[count]) == 2){
            count++;
        } 
    }
    fclose(file);
    if(count >= max_size){
        fprintf(stderr, "Se excedio el tamano maximo \n");
    }
    return count;
}

char* parse_filepath(int arcg, char*argv[]){
    char *res = NULL;
    bool valid_args_count = (arcg == 2);
    if(!valid_args_count){
        exit(EXIT_FAILURE);
    }
    res = argv[1];
    return res;
}
int main(int arcg, char *argv[]) {
    char *filepath = NULL;
    filepath = parse_filepath(arcg, argv);

    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0; 

    length = data_from_file(filepath, indexes, letters, MAX_SIZE);
    reoder(indexes, letters, sorted, length);
    dump(sorted, length);

    return EXIT_SUCCESS;
}

