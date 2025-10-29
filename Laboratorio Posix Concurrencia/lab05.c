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
 *
 * HAY CONDICION DE CARRERA
 ****************************************************/
 
 //librerías necesarias
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
        *valor = i + 1; //asigna el valor (i+1) en la dirección de memoria
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
