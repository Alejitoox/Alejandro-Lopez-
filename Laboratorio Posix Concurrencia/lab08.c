/************************************************************
 * Pontificia Universidad Javeriana
 * Fecha: 28/10/2025
 * Autor: Alejandro Lopez
 * Materia: Sistemas Operativos
 * Tema: Hilos con API POSIX
 *        Variables de Condici�n y Exclusi�n Mutua
 *
 * Descripci�n:
 * Ejemplo de uso de hilos POSIX con variables de condici�n
 * y mutex para sincronizar la comunicaci�n entre hilos.
 *************************************************************/

//librerias necesarias
#include <stdio.h>      
#include <stdlib.h>     
#include <pthread.h>    
#include <stdbool.h>

//variables de sincronizacion
pthread_cond_t var_cond = PTHREAD_COND_INITIALIZER; 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
//variable compartida
int valor = 100;                
//se�al para notificar al hilo                    
bool notificar = false;                             

void *reportar(void *nousado){
   
    pthread_mutex_lock(&mutex);//se libera el mutex y espera la se�al
    while(!notificar){
        //apenas se recibe la se�al el mutex se readquiere autom�ticamente
        pthread_cond_wait(&var_cond, &mutex);
    }
    printf("El valor es: %d\n", valor);
    pthread_mutex_unlock(&mutex);
    return NULL;                      
}

void *asignar(void *nousado){
    valor = 20; 
    
    //se�ala al hilo 'reportar' que puede continuar
    pthread_mutex_lock(&mutex);
    notificar = true;
    pthread_cond_signal(&var_cond);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int argc, char *argv[]){
    pthread_t reporte, asigne;

    //crea los hilos
    pthread_create(&reporte, NULL, reportar, NULL);
    pthread_create(&asigne, NULL, asignar, NULL);

    void *nousado;

    //espera a que los hilos terminen
    pthread_join(reporte, &nousado);
    pthread_join(asigne, &nousado);

    return 0;
}
