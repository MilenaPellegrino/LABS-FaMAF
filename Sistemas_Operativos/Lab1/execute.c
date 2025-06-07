#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <glib.h>
#include <string.h>
#include <unistd.h> //syscall
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>


#include "execute.h"
#include "command.h"
#include "builtin.h"
#include "tests/syscall_mock.h"

#define SIZE 128

/*
char *intern_comm[] = {
    "ls",
    "wc"
};

unsigned int comm_long  = sizeof(intern_comm) / sizeof(intern_comm[0]);
bool is_command (const scommand cmd){
    assert(cmd!=NULL);
    bool is_command = false;
    bool matches = true;
    for(unsigned int i=0; i<comm_long && matches; i++){
        char *comm_act = intern_comm[i];
        if (strcmp(comm_act, scommand_front(cmd)) == 0){
            is_command = true;
            matches = false;
        }
    }
    return is_command;
}
*/

char **command_to_array (scommand command) {
	assert (command != NULL);
	char **result = malloc((scommand_length(command)+2)*sizeof(char *));
	char *aux = NULL;
	guint length = scommand_length(command);
	for (guint i=0; i < length; i++) {
		aux = scommand_front(command);
		result[i] = malloc(strlen(aux)+1);
		strcpy(result[i], aux);
		scommand_pop_front(command);
	}
	result[length] = NULL;
	return result;
}

int command_run (scommand cmd, int fd, pipeline apipe) {
    char **cmd_arg;								//Arreglo para guardar argumentos, ideal para execvp.
    bool waiting = pipeline_get_wait(apipe);	//Booleano para ver ejecucion en seg plano.
    int error = 2;								//Entero a devolver, indica error en ejecucion. Ver definicion de command_run.
    int status;									//Entero, ideal para usar con wait.
	char *in = scommand_get_redir_in(cmd);		//String que guarda valor del input.
    char *out = scommand_get_redir_out(cmd);	//""     ""  ""     ""    ""  output.
	operator opp = scommand_get_operator(cmd);	//operator que define tipo de pipe: opp={PIPELINE, DOBLE_AMPERSAND, NOTHING}
	pid_t pid;									//Variable para almacenar procces id, ideal para fork.


    if (opp == PIPELINE) {	//--------------------------------------------PIPELINE-------------------------------------
		int outinpipe[2];				//Se crea el array de enteros, ideal para el pipeline.
		int status2;
		pid_t pid2;
		if (pipe(outinpipe) == -1) {	//Se usa pipe generando file
			perror("pipe");				//descriptors en outinpipe para 
        }								//transimitir info entre procesos.
        
		pid = fork();					//Inicia fork.

	    if (pid == -1) {				//ERROR en la creacion del fork.
            perror("fork");
			close(outinpipe[0]);								//Cerrar file descriptor no usado.    
            close(outinpipe[1]);								//write file descriptor de la pipe.
		} 
		else if (pid == 0) {                        //Hijo-------------------------------------------------------------
			close(outinpipe[0]);								//Cerrar file descriptor no usado.    

			if (fd > 1 && in==NULL) {							//Estos if's se encargan
        		dup2(fd, 0);									//de modificar el input
				close(fd);
				fd = 0;
    		} else if (fd == 0 && in!=NULL) {					//en caso de necesidad...
				fd = open(in, O_RDONLY, S_IRWXU);				//...
        		dup2(fd, 0);									//...
				close(fd);										//...
				fd = 0;											//...
			} else if (fd > 1 && in!=NULL) {					//...
				printf ("Error: usas dos inputs para un mismo comando\n");
				// Ver que hacer
			}
        
			if (out != NULL) {									//Error doble output. 
					printf("ERROR: Intenta agregar un output mientras usa pipe\n"
							"	   se prioriza el output del pipe.\n");
			}

            dup2(outinpipe[1], 1);								//Redirigimos la salida estandar al
            close(outinpipe[1]);								//write file descriptor de la pipe.
			
            cmd_arg = command_to_array(cmd);					//Tomamos el comando para ejecutar.
            if (execvp(cmd_arg[0], cmd_arg) == -1) {			//Ejecutamos el comando.
                error = -1;										//Entra el caso de error.
            }
		}
		else if (pid > 0) {							//Papi-------------------------------------------------------------
            close(outinpipe[1]);						//Cerrar file descriptor no usado.


            pipeline_pop_front(apipe);							//Eliminamos el comando ya ejecutado.
            cmd = pipeline_front(apipe);						//Agarramos el sig. para el pipe.

			pid2 = fork();

           	if (pid2 == -1) {
				perror("fork");
				close(outinpipe[0]);
			}
			else if (pid2 == 0) {
				dup2(outinpipe[0],0);
				close(outinpipe[0]);
				if (out != NULL) {									//Este if se encarga de 
        			int file_descriptor_out = open(out, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);	//modificar el output, S_IRWXU se usa para que tenga permiso de escritura, lectura y ejecucion para el propietario
					dup2(file_descriptor_out, 1);           		//en caso de necesidad.
					close(file_descriptor_out);
				}
				cmd_arg = command_to_array(cmd);
				execvp(cmd_arg[0], cmd_arg);
			}
			else if (pid2 > 0) {
				close(outinpipe[0]);
				if (waiting) {
                	wait(&status);							//En caso de wait el padre espera al hijo.
					wait(&status2);
				}
			}
        }
	} 
	else if (opp == DOBLE_AMPERSAND || opp == NOTHING) { //------------------DOBLE_AMPERSAN || NOTHING---------------------------------
		pid = fork();						//Inicia fork.
	    
		if (pid == -1) {					//ERROR en la creacion del fork.
            perror("fork");
	    } 
		else if (pid == 0) {                        //Hijo-------------------------------------------------------------
		//	close(errorpipe[0]);								//Cerrar file descriptor no usado.    
			if (fd > 1 && in==NULL) {							//Estos if's se encargan
        		dup2(fd, 0);									//de modificar el input
    		} else if (fd == 0 && in!=NULL) {					//en caso de necesidad...
				fd = open(in, O_RDONLY, S_IRWXU);				//...
        		dup2(fd, 0);									//...
				close(fd);										//...
				fd = 0;											//...
			} else if (fd > 1 && in!=NULL) {					//...
				printf ("Error: usas dos inputs para un mismo comando\n");
				// Ver que hacer
			}
			if (out != NULL) {									//Este if se encarga de 
        		int file_descriptor_out = open(out, O_CREAT|O_WRONLY|O_TRUNC, S_IWUSR);	//modificar el output, S_IRWXU se usa para que tenga permiso de escritura, lectura y ejecucion para el propietario
        		dup2(file_descriptor_out, 1);           		//en caso de necesidad.
        		close(file_descriptor_out);
			}

            cmd_arg = command_to_array(cmd);					//Tomamos el comando para ejecutar.
            if (execvp(cmd_arg[0], cmd_arg) == -1) {			//Ejecutamos el comando.
				if (opp == DOBLE_AMPERSAND) {					//Si ocurre error en operator
                error = 0;										//DOBLE_AMPERSAN setea error en 0.
				} 												
				else if (opp == NOTHING) {						//Si ocurre ERROR en operator
				error = 1;										//NOTHING setea error en 1.
				}
            }

			free(cmd_arg);										//Liberamos memoria almacenada
			cmd_arg = NULL;										//por command_to_array

		/*
			write(errorpipe[1], &error, sizeof(error)); 		//Escribimos el error de la ejecucion en el pipe.
			close(errorpipe[1]);								//Cerramos el pipe recien usado.
		*/
	    } 
		else if (pid > 0) {							//Papi-------------------------------------------------------------
        //    close(errorpipe[1]);								//Cerrar file descriptor no usado.

			if (waiting) {
                wait(&status);									//En caso de wait el padre espera al hijo.
            }


		/*
			read(errorpipe[0], &error, sizeof(error)); 			//Leemos el error de la ejecucion.
			close(errorpipe[0]); 								//Cerrar file descriptor.
		*/
        }
    }
	return error;
}

void execute_pipeline(pipeline apipe){
    assert(apipe != NULL);
    scommand cmd;
	int error=1;
	int fdinput = 0;
    bool builtin=true;
	int test=1;
	char *comand; 
    if (pipeline_is_empty(apipe)) { // caso base
        return;
    }
    while (pipeline_length(apipe)!=0 && error!=0) {
        cmd = pipeline_front(apipe);
		comand = scommand_to_string(cmd);
        builtin = builtin_is_internal(cmd);
        if (builtin){
            builtin_run(cmd);
            pipeline_pop_front(apipe);							//Limpiamos memoria 
        } else { //syscall
			error = command_run(cmd, fdinput, apipe);
            pipeline_pop_front(apipe);							//Limpiamos memoria 
        }
		test++;
		free(comand);
    }
	if (error==0) {
	}
}
