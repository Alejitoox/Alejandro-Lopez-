/****************************************************
 * Fecha: 7/10/2025
 * Autor: Alejandro Lopez
 * Materia: Sistemas Operativos
 * Tema: Funcion fork(), creación de procesos
 ****************************************************/

#include<unistd.h>	//biblioteca para la función fork() y getpid(), getppid()
#include <stdio.h>  //biblioteca para entradas/salidas
#include <stdlib.h> //biblioteca general

int main(int argc, char *argv[]) {
    
    //se declara una variable entera para almacenar el valor de retorno de fork()
    int processID = fork();

    /*
    * fork() crea un nuevo proceso duplicando el proceso actual
    * -devuelve un valor positivo (>0) al proceso PADRE (es el PID del proceso hijo creado)
    * -devuelve 0 al proceso HIJO (recien creado)
    * -devuelve un valor negativo (<0) si la creación del proceso falla
    */

    if (processID > 0) {
        //se ejecuta unicamente en el proceso PADRE
        printf("fork() devuelve un valor +ve. Este es el 'proceso padre' con ID: %d \n", getpid());
        
        //getpid() obtiene el ID del proceso actual (PID = Process ID)en este caso corresponde al proceso padre
    }
    else if (processID == 0) {
        //se ejecuta unicamente en el proceso HIJO
        printf("fork() devuelve un valor 0. Este es un 'proceso hijo' recien creado con ID: %d \n", getpid());
        
        //getpid() obtiene el ID del proceso HIJO, que es diferente del padre
        printf("El proceso padre de este 'proceso hijo' tiene el ID: %d\n", getppid());
        
        //getppid() obtiene el PID del proceso padre, sirve para identificar quién creo al proceso actual
    }
    else {
        //se ejecuta solo si fork() falla 
        printf("fork() devuelve un valor -ve, por lo que la llamada al sistema fork() fallo\n");
    }

    //este bloque de codigo se ejecutara tanto en el proceso PADRE como en el proceso HIJO, porque ambos continuan ejecutando desde este punto del programa despues del fork()

    printf("\nEsta es una unica impresion. Si la llamada al sistema fork() ha tenido exito\n");
    printf("tanto el 'proceso padre' como el 'proceso hijo' se ejecutaran simultaneamente,\n");
    printf("y esta impresion aparecera dos veces.\n");

    return 0;
}

