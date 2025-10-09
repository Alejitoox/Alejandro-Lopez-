/****************************************************
 * Fecha: 7/10/2025
 * Autor: Alejandro Lopez
 * Materia: Sistemas Operativos
 * Tema: Comunicacion entre procesos con PIPE y fork()
 ****************************************************/

#include <stdio.h>     //printf, perror
#include <stdlib.h>    //exit, EXIT_FAILURE
#include <unistd.h>    //pipe, fork, read, write, close
#include <sys/types.h> //pid_t
#include <sys/wait.h>  //wait
#include <string.h>    //strlen()

int main(void) {
    int pipefd[2];	// pipefd[0] = lectura, pipefd[1] = escritura
    pid_t procesoHIJO_PID;

    //crear el PIPE
    if (pipe(pipefd) == -1) {
        perror("PIPE");
        exit(EXIT_FAILURE);
    }

    //crear el proceso HIJO
    procesoHIJO_PID = fork();	//llamada al fork: creacion del proceso
    if (procesoHIJO_PID == -1) {
        perror("FORK");
        exit(EXIT_FAILURE);
    }

    if (procesoHIJO_PID == 0) {
        //PROCESO HIJO
        close(pipefd[1]);  //cierra salida del pipe (solo lee)

        char mensaje[100];	//vector de caracteres del mensaje
        ssize_t lectBytes = read(pipefd[0], mensaje, sizeof(mensaje));

        if (lectBytes == -1) {
            perror("LECTURA");
            exit(EXIT_FAILURE);
        }

        printf("\tProceso HIJO: recibe mensaje del PADRE: %.*s\n",
               (int)lectBytes, mensaje);

        close(pipefd[0]);  //cierra entrada del pipe
        exit(EXIT_SUCCESS);
    } else {
        //PROCESO PADRE
        close(pipefd[0]);	//cierra la entrada para leer

        const char *mensajeP = "HOLA, SOY TU PADRE :)";
        ssize_t escrBytes = write(pipefd[1], mensajeP, (size_t)strlen(mensajeP));

        if (escrBytes == -1) {
            perror("ESCRITURA");
            exit(EXIT_FAILURE);
        }

        close(pipefd[1]);  //cierra salida del pipe
        wait(NULL);        //espera a que termine el hijo
    }

    printf("FIN...\n");
    return 0;
}

