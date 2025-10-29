
/************************************************************
 * Pontificia Universidad Javeriana
 * Fecha: 28/10/2025
 * Autor: Alejandro Lopez
 * Materia: Sistemas Operativos
 * Tema: Hilos con API POSIX
 *        Variables de Condición y Exclusión Mutua
 *
 * Descripción:
 * Ejemplo de uso de hilos POSIX con variables de condición
 * y mutex para sincronizar la comunicación entre hilos.
 ************************************************************/

//librrias necesarias
#include <stdio.h>      
#include <stdlib.h>    
#include <pthread.h>   
#include <stdbool.h>    

//variables de sincronización
pthread_cond_t var_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int valor = 100;                
//señal para notificar al hilo                    
bool notificar = false;                             

//hilo que reporta el valor de la variable compartida
void *reportar(void *nousado){
	
    /*********************************************************************
    //parte comentada para demostrar la CONDICION DE CARRERA de los hilos
    pthread_mutex_lock(&mutex);
    while(!notificar){
        pthread_cond_wait(&var_cond, &mutex);
    }
    **********************************************************************/
    
    printf("El valor es: %d\n", valor); //valor actual
    pthread_mutex_unlock(&mutex);       //desbloquea mutex
    return NULL;                      
}

//hilo que asigna un nuevo valor a la variable compartida
void *asignar(void *nousado){
    valor = 20;
    
    /**********************************************************
    //parte comentada para demostrar la CONDICION DE CARRERA
    pthread_mutex_lock(&mutex);
    notificar = true;
    pthread_cond_signal(&var_cond);
    pthread_mutex_unlock(&mutex);
    ****************************************************************/
    return NULL;
}

int main(int argc, char *argv[]){
    pthread_t reporte, asigne;

    //se cran los hilos
    pthread_create(&reporte, NULL, reportar, NULL);
    pthread_create(&asigne, NULL, asignar, NULL);

    void *nousado;

    //espera a que ambos hilos terminen
    pthread_join(reporte, &nousado);
    pthread_join(asigne, &nousado);

    return 0;
}
