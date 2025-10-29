/****************************************************
 * Pontificia Universidad Javeriana
 * Fecha: 28/10/2025
 * Autor: Alejandro Lopez
 * Materia: Sistemas Operativos
 * Tema: Hilos con API POSIX
 *        Variables de Condición y Exclusión Mutua
 *
 * Descripción:
 * Suponer x*x es altamente costosa en términos de
 * cálculo computacional. Se desea calcular la suma
 * de los cuadrados de una cantidad de números.
 * Se desea aplicar la "paralelización" del cálculo
 * de la sumatoria de los cuadrados usando hilos.
 ****************************************************/

//librerias necearias
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

//mutex protege la variable 'acumulado'
pthread_mutex_t acumuladoMutex = PTHREAD_MUTEX_INITIALIZER;

//variable global donde se acumulan los cuadrados
int acumulado = 0;

//calcula el cuadrado del número recibido
void *cuadrado(void *x) {
    int xi = (intptr_t)x;
    
    //se bloquea el mutex antes de modificar la variable global
    pthread_mutex_lock(&acumuladoMutex);
    acumulado += xi * xi; 
    //se desbloquea el mutex
    pthread_mutex_unlock(&acumuladoMutex);
    
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t hilos[20];

    //bucle para creacion de hilos
	//cada uno calcula el cuadrado de un número (1-20)
    for (int i = 0; i < 20; i++) {
        int *valor = malloc(sizeof(int));
        *valor = i + 1;
        pthread_create(&hilos[i], NULL, cuadrado, (void *)valor);
    }

    //espera a que todos los hilos terminen
    for (int i = 0; i < 20; i++) {
        pthread_join(hilos[i], NULL);
    }

    //imprimir el resultado acumulado
    printf("Acumulado = %d\n", acumulado);
}
