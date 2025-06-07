#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "command.h"
#include "execute.h"
#include "parser.h"
#include "parsing.h"
#include "builtin.h"

#include "obfuscated.h"

// Colores piola, para hacer una terminal piola 
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define DEFAULT "\033[0m"

static void show_prompt(void) {
    char *usr = getenv("USER"); // Obtengo el usuario del pc
    char cwd[1024];  // Tamano suficiente para que se pueda ver el string del directorio
    char *bf = getcwd(cwd, sizeof(cwd));  // Obtengo el directorio actual
    if(bf == NULL){
        printf ("Wolobash> ");  // o un exit, un error
    } else {
        printf(DEFAULT "%s@%s", usr, usr);  // Nombre de usuario en verde
        printf(DEFAULT ":");
        printf(BLUE "~%s", cwd);  // Directorio actual en azul 
        printf("---Wolobash> ");  // Imprimir el prompt 
        printf(DEFAULT);
    }
    
    fflush (stdout);
}

int main(int argc, char *argv[]) {
    pipeline pipe;
    Parser input;
    bool quit = false;

    input = parser_new(stdin);
    while (!quit) {
        show_prompt();
        pipe = parse_pipeline(input);

        /* Hay que salir luego de ejecutar? */
        quit = parser_at_eof(input);
        
        if(pipe!= NULL){
            execute_pipeline(pipe);
            pipe = pipeline_destroy(pipe);
        }
        
    }
    printf(DEFAULT "\n");  // Salto de linea para hacerlo mas fachero 
    parser_destroy(input); input = NULL;
    return EXIT_SUCCESS;
}
