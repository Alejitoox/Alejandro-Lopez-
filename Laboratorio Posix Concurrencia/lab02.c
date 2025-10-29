/***********************************************************************************************************
 * Fecha: 28/10/2025
 * Autor: Alejandro L�pez
 * Materia: Sistemas Operativos
 * Tema: Hilos - Creaci�n correcta
 * Descripci�n:
 * Se implementa un programa que crea m�ltiples hilos para incrementar un contador global.
 * Se utiliza un mutex para garantizar que solo un hilo acceda a la variable compartida a la vez,
 * evitando condiciones de carrera. Adem�s, se sincroniza la finalizaci�n de los hilos.
 ************************************************************************************************************/
 
//bibliotecas para el manejo de entrada-salida estandar, mutex e hilos
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//constante que define la cantidad de hilos a utilizar
#define NTHREADS 10

//inicializaci�n del mutex que proteger� la variable 'counter'
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

//variable global compartida (recurso cr�tico)
int counter = 0;

//funcion que cada hilo ejecutar�
void *thread_function(void *arg) {
	
    //obtiene �ndice del hilo pasado como argumento
    int i = *(int *)arg;

    //muestra numero de hilo e identificador
    printf("Thread number: %d | Thread ID %ld\n", i, pthread_self());

    //mutex se bloquea (lock)
    pthread_mutex_lock(&mutex1);

    //se incrementa el contador
    counter++;

    // Libera el bloqueo (unlock) para que otros hilos puedan acceder.
    pthread_mutex_unlock(&mutex1);

    return NULL;
}


void main() {
    //arreglo para almacenar los identificadores de los hilos creados
    pthread_t thread_id[NTHREADS];
    int i; 

    //bucle de creaci�n: se crean todos los hilos
    for (i = 0; i < NTHREADS; i++) {
        pthread_create(&thread_id[i], NULL, thread_function, &i);
    }

    //bucle de sincronizaci�n (join): El hilo principal espera a que todos los hilos terminen
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(thread_id[i], NULL);
    }
    
    //se imprime el resultado final del contador (deber�a ser igual a NTHREADS)
    printf("Final counter value: %d\n", counter);
    return;
}
