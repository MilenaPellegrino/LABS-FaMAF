#include "array_helpers.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {
    // Open file
    FILE *fp = fopen(filepath, "r"); // "r" = reading
    if(fp == NULL){
		printf("Hay un error al abrir el archivo\n");
		return 1; 
	}
	unsigned int length; 
	if(fscanf(fp, "%u", &length) != 1 || length >max_size || length <= 0){
		printf("La longitud del array es invalida\n");
		return 1; 
	}
	for(unsigned int i =0; i<length; i++){
		if((fscanf(fp, "%d", &array[i])) != 1){
			printf("Error con la longitud del array y el numero del elemento de este\n");
			return 1; 
		}
	}
	fclose(fp);
    return length;
}
void array_dump(int a[], unsigned int length) {
    printf("%d\n", length);
    printf("[");
    for(unsigned int i = 0; i<length; i++){
		printf("%d, ", a[i]);
	}
	printf("%d]\n", a[length-1]);
}