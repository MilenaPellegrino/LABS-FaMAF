#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../kernel/param.h"
#include "user.h"

int main(int argc, char *argv[]){
    int waiting;
	int sem_padre;
	int sem_hijo;

	sem_padre = sem_open(first_sem_free(),1);
	if (sem_padre == 1024) {
		return 0;
	}

	sem_hijo = sem_open(first_sem_free(),1);
	if (sem_hijo == 1024) {
		return 0;
	}

    if (argc != 2){   
        printf("ERROR: cantidad de argumentos invalidos\n");
        return 0;
    }
    int n = atoi(argv[1]);  // Convertimos el numero a entero 

    if(n<=0){
        printf("ERROR: El numero de rounds tiene que ser mayor a 1\n");
        return 0;
    }

    int pd = fork();  // Creamos el proceso hijo
    if(pd < 0){
        printf("ERROR: No se pudo forkear. \n");
        return 0;
    } else if (pd == 0){
        // hijo
    	sem_down(sem_hijo);
		while (n>0) {
    		printf("	pong\n");
			if (n!=1) {
    			sem_up(sem_padre);    // Despertamos para poder imprimir pong
				sem_down(sem_hijo);  // Esperamos para imprimir ping
			} else {
    			sem_close(sem_hijo);
			}
			n--;
		}
    } else {
        // padre
		while (n>0) {
    		printf(" ping \n");
    		sem_up(sem_hijo);    // Despertamos para poder imprimir ping
			if (n!=1) {
				sem_down(sem_padre);  // Esperamos para imprimir pong
			} else {
				sem_close(sem_padre);
			}
			n--;
		}
        wait(&waiting);   // Hacemos el wait para esperar que se termine de hacer pong
    }
    return 0;
}
