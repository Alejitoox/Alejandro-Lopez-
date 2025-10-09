/****************************************************
 * Fecha: 7/10/2025
 * Autor: Alejandro Lopez
 * Materia: Sistemas Operativos
 * Tema: Funcion fork(), creacion de procesos
 ****************************************************/

#include <unistd.h>	//para fork(), getpid(), getppid()
#include <stdio.h>	//para printf()
#include <stdlib.h>	//para funciones estandar del sistema

int main(int argc, char *argv[]) {

    //se crea un nuevo proceso con fork()
    int processID = fork();

    if (processID > 0) {
        //se ejecuta en el proceso padre
        printf("\n proceso padre.... \n");
    }
    else if (processID == 0) {
        //se ejecuta en el proceso hijo recien creado
        printf("\n proceso hijo recien creado \n");
    }
    else {
        //si el valor es negativo, la llamada a fork() fallo
        printf("\n llamada al sistema fork() fallo\n");
    }

    //se ejecutara tanto en el proceso padre como en el hijo
    printf("\n\n Imprimiendo ... \n");
    for (int i = 0; i < 5; i++)
        printf("%d ", i);

    printf("\n Fin \n");

    return 0;
}
//Observacion:luego de varias ejecuciones tiende a aparecer el caos en la compilacion del codigo

