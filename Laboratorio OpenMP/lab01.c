/*****************************************************
* Pontificia Universidad Javeriana
* Autor: Alejandro Lopez Beltran
* Fecha: 4/11/2025
* Materia: Sistemas Operativos
* Tema: OpenMP
* Descripción:
* - Introducción en laboratorio de OpenMP
* - Cláusulas y directivas para el programa
*****************************************************/

//librerias necesarias
#include <omp.h>//biblioteca principal de OpenMP (manejo de hilos y paralelismo)
#include <stdio.h>//para usar printf() y funciones de entrada/salida estándar
#include <stdlib.h>//biblioteca estándar de C (malloc, free, etc.)
#include <time.h>//para manejo de tiempo (no usada en este código pero útil en pruebas paralelas)

int main(int argc, char *argv[]){
    
    //se obtiene el número máximo de hilos que OpenMP puede usar según el sistema
    int maxHilos = omp_get_max_threads();

    //se muestra en pantalla la cantidad de hilos disponibles (núcleos o threads lógicos)
    printf("OpenMP ejecutando en Cores (HiperThreading = %d hilos)\n", maxHilos);

    //directiva de OpenMP: a partir de aquí, el bloque se ejecutará en paralelo
    #pragma omp parallel
    { 
        // Cada hilo que se crea ejecutará este bloque de código de manera simultánea

        // omp_get_thread_num() devuelve el identificador del hilo actual (desde 0 hasta n-1)
        printf("Hello World desde hilo %d\n", omp_get_thread_num());
    }
    //al finalizar el bloque parallel, todos los hilos se sincronizan y continúa el hilo principal
    
    return 0;
}

