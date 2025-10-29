/****************************************************
 * Pontificia Universidad Javeriana
 * Fecha: 28/10/2025
 * Autor: Alejandro Lopez
 * Materia: Sistemas Operativos
 * Tema: Hilos con API POSIX
 *        Variables de Condici�n y Exclusi�n Mutua
 *
 * Descripci�n:
 * Suponer x*x es altamente costosa en t�rminos de
 * c�lculo computacional. Se desea calcular la suma
 * de los cuadrados de una cantidad de n�meros.
 * Se desea aplicar la "paralelizaci�n" del c�lculo
 * de la sumatoria de los cuadrados usando hilos.
 *
 * HAY CONDICION DE CARRERA
 ****************************************************/
 
 //librer�as necesarias
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

int acumulado = 0;

//calcula el cuadrado del argumento y lo suma al total
void *cuadrado(void *x) {
    int xi = (intptr_t)x;
    acumulado += (xi) * (xi);
    return NULL;
}

int main(int argc, char *argv[]) {
    //arreglo para guardar los identificadores de los hilos
    pthread_t hilos[20];
    
    //bucle para crear 20 hilos, cada uno con un valor de 1 a 20
    for (int i = 0; i < 20; i++) {
        int *valor = malloc(sizeof(int)); //reserva memoria para el argumento del hilo
        *valor = i + 1; //asigna el valor (i+1) en la direcci�n de memoria
        pthread_create(&hilos[i], NULL, cuadrado, (void *)valor); //crea hilo
    }
    
    //espera a que todos los hilos terminen
    for (int i = 0; i < 20; i++) {
        void *resultado;
        pthread_join(hilos[i], &resultado);
    }
    
    //imprime el resultado final de la suma
    printf("Acumulado = %d\n", acumulado);
}
