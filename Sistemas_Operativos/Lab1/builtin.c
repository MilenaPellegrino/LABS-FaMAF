#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>  // Ver cual fue el error del chdir 
#include <assert.h>
#include <string.h>

#include "command.h"
#include "builtin.h"
#include "tests/syscall_mock.h"

// En caso de que haya mas comandos internos se podrian agregar sin problemas
char *comm_inter[] = {
    "cd",
    "help",
    "exit"
}; 

// Obtenemos el tamano por si se agregan mas pero en principio son 3
static unsigned int long_comm  = 3;

bool builtin_is_internal(scommand cmd){
    assert(cmd!=NULL);
    bool is_internal = false;
    unsigned int i = 0;
    while (!is_internal && i < long_comm)
    {
        if (strcmp(scommand_front(cmd), comm_inter[i]) == 0) {
            is_internal = true;
        }
        i++;
    }
    return is_internal;
}

bool builtin_alone(pipeline p){
    assert(p!=NULL);
    return pipeline_length(p) == 1 && builtin_is_internal(pipeline_front(p));;
}

/* Funciones auxiliares e implementacion del diccionario */

// Implementamos la estructura del diccionario 
typedef struct {
    char *command;
    void (*run_comm)(scommand);
}command_builtin;

// Definicion del diccionario de comandos 

command_builtin builtin_table[] = {
    {"cd", run_cd},
    {"help", run_help},
    {"exit", run_exit}
};

// Calculamos el tamano de la tabla por si se agregan mas pero en principio son 3
unsigned int command_length = sizeof(builtin_table) / sizeof(builtin_table[0]);

/* 
Funciones auxiliares para ejecutar cada comando externo 
Sin en un futuro se agregan nuevos comandos, simplemente 
creamos la nueva funcion que ejecute el comando interno 
y lo agregamos a nuestra diccionario de comandos 
*/

// Command = cd
void run_cd(scommand cmd){
    scommand_pop_front(cmd);                // Sacamos el comando cd, para ver el supuesto directorio
    char *path;
    if (scommand_is_empty(cmd)) {
        path = "/home";                   //Si es vacio, la ruta es /
    } else {
        path = scommand_front(cmd);   //Si no es vacio, obtenemos la ruta del directorio 
    }
    int cdir = chdir(path);  // Cambiamos el directorio 

    if(cdir == -1){ // Si retorna (-1) ocurrio un error
        // Diferentes casos de errores 
        switch(errno){  // Traduci como me parecia los mensajes del man (ver bien)
            case EACCES:
                printf("Se denegó el permiso de búsqueda para uno de los componentes de la ruta\n");
                break;
            case EFAULT:
                printf("La ruta apunta fuera del espacio de direcciones al que tienes acceso. \n");
                break;
            case EIO:
                printf("Ocurrió un error de entrada/salida.\n");
                break;
            case ELOOP:
                printf("Se encontraron demasiados enlaces simbólicos al resolver la ruta.\n");
                break;
            case ENAMETOOLONG: 
                printf("La ruta es demasiado larga. \n");
                break;
            case ENOENT: 
                printf("El directorio especificado en la ruta no existe.\n");
                break;
            case ENOTDIR:
                printf("Un componente de la ruta no es un directorio. \n");
                break;
            case ENOMEM:
                printf("No había suficiente memoria del núcleo disponible. \n");
                break;
            default:
                printf("Error al cambiar de directorio. \n");
                break;
        }
    }
}

void  run_help(scommand cmd){
    printf("Shell   -->   MyBash\n" 
            "Autores -->   Castillo Agustin, Gonzalez Juan Pablo, Madero Ismael, Pellegrino Milena \n \n"
            "Comandos: \n"
               "(1) 'cd <path>' -> Cambiar el directorio actual \n"
               "(2) 'help' -> Descripcion breve del uso de cada comando \n"
               "(3) 'exit'  -> Sale del MyBash actual \n"
    );
}

void run_exit(scommand cmd){
    printf("\n");
    exit(0);  // Termina el programa
}

/* Fin de funciones auxiliares e implementacion del diccionario*/

// Funcion que ejecuta el comando interno seleccionado
void builtin_run(scommand cmd){
    assert(builtin_is_internal(cmd));
    char *command = scommand_front(cmd);  // Buscamos el comando a ejecutar
    for(unsigned int i =0; i<command_length; i++){
        if(strcmp(builtin_table[i].command, command) == 0){  // Lo buscamos en el diccionario
            builtin_table[i].run_comm(cmd);  // Lo ejecutamos
            return;
        }
    }
}
