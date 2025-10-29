/***********************************************************************************************************
 * Fecha: 28/10/2025
 * Autor: Alejandro Lopez
 * Materia: Sistemas Operativos
 * Tema: Uso de mutex para sincronizar el acceso a una variable compartida entre hilos
 * Descripci�n:
 * Se implementa un programa que crea tres hilos concurrentes, donde cada uno representa un trabajo.
 * Se utiliza un mutex para proteger la secci�n cr�tica al momento de modificar una variable global compartida.
 ************************************************************************************************************/
 
//bibliotecas para el manejo de entrada-salida estandar, mutex e hilos
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h> 

// arreglo para almacenar los IDs (identificadores) de los hilos
pthread_t tid[3];

//variable global 
int counter;

//declaraci�n del mutex que proteger� la variable 'counter'.
pthread_mutex_t lock;


void* compute(void *arg) {
    unsigned long i = 0;
    int my_job_number; //guardar el n�mero de este trabajo

    // se bloquea el mutex para entrar a la secci�n cr�tica
    pthread_mutex_lock(&lock);
    counter += 1; // Modificaci�n segura del contador global
    my_job_number = counter;

    //se libera el mutex y se anuncia el inicio del trabajo
    pthread_mutex_unlock(&lock);
    printf("\n Job %d has started\n", my_job_number);

    //simulaci�n de una tarea que consume tiempo
    sleep(1);
    
    //se imprime la finalizaci�n del trabajo de este hilo
    printf("\n Job %d has finished\n", my_job_number);

    return NULL;
}

int main(void) {
    int i = 0;
    int error;

    //inicializaci�n del mutex. Si falla, el programa termina
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n Mutex init failed\n");
        return 1;
    }

    //bucle para la creaci�n de los tres hilos
    while (i < 3) {
        error = pthread_create(&(tid[i]), NULL, &compute, NULL);
        if (error != 0)
            printf("\nThread can't be created : [%s]", strerror(error));
        i++;
    }

    //espera a que los tres hilos terminen su ejecuci�n
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    //se destruye el mutex para liberar los recursos antes de salir
    pthread_mutex_destroy(&lock);
    return 0;
}
