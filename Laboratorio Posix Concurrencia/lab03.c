/***********************************************************************************************************
 * Fecha: 28/10/2025
 * Autor: Alejandro Lopez
 * Materia: Sistemas Operativos
 * Tema: Sincronización de hilos con mutex y variables de condición
 * Descripción:
 * Se implementa un programa que utiliza dos hilos para incrementar un contador global de forma concurrente.
 * Se emplean mutex y variables de condición para controlar cuándo un hilo debe detenerse y cuándo puede continuar,
 * evitando conflictos de acceso y demostrando el uso de sincronización en entornos multihilo.
 ************************************************************************************************************/
 
//bibliotecas para el manejo de entrada-salida estandar, mutex e hilos
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//inicializacion los mutex (para el contador y la condición) y la variable de condición
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;

int count = 0;

//constantes para los límites del conteo (meta final y pausas).
#define COUNT_DONE 15
#define COUNT_HALT1 4
#define COUNT_HALT2 11

//función que ejecutará el Hilo 1
void *count01() {
    for (;;) {
        // Adquiere el bloqueo del mutex de condición para chequear 'count'.
        pthread_mutex_lock(&condition_mutex);

        // Si 'count' está en el rango [4, 11], el hilo se pone a esperar (wait).
        while (count >= COUNT_HALT1 && count <= COUNT_HALT2) {
            pthread_cond_wait(&condition_cond, &condition_mutex);
        }

        // Libera el bloqueo del mutex de condición.
        pthread_mutex_unlock(&condition_mutex);

        // Adquiere el bloqueo del 'count_mutex' para modificar el contador.
        pthread_mutex_lock(&count_mutex);
        count++;
        // Imprime el valor actual del contador (identificándose como 01).
        printf("Counter value functionCount ==> 01 <==: %d\n", count);
        pthread_mutex_unlock(&count_mutex);

        // Si se alcanza el límite final (COUNT_DONE), el hilo termina.
        if (count >= COUNT_DONE) return NULL;
    }
}

//función que ejecutará el Hilo 2
void *count02() {
    for (;;) {
        //bloquo del mutex de condición revisar si debe enviar señal
        pthread_mutex_lock(&condition_mutex);
        
        //si 'count' está fuera del rango [4, 11], llama al Hilo 1 (si está esperando).
        if (count < COUNT_HALT1 || count > COUNT_HALT2) {
            pthread_cond_signal(&condition_cond);
        }

        //libera el bloqueo del mutex de condición
        pthread_mutex_unlock(&condition_mutex);

        //se bloquea el mutex para modificar el contador
        pthread_mutex_lock(&count_mutex);
        count++;
        //imprime el valor actual del contador (identificándose como 02)
        printf("Counter value functionCount ==> 02 <==: %d\n", count);
        pthread_mutex_unlock(&count_mutex);

        //si se alcanza el límite final (COUNT_DONE), el hilo termina
        if (count >= COUNT_DONE) return NULL;
    }
}


int main() {
    //identificadores para los dos hilos
    pthread_t thread1, thread2;

    //creacion de los dos hilos concurrentes
    pthread_create(&thread1, NULL, &count01, NULL);
    pthread_create(&thread2, NULL, &count02, NULL);

    //el hilo 'main' espera a que ambos hilos concluyan (join).
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    exit(0);
}
