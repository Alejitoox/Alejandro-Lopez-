/*****************************************************
* Pontificia Universidad Javeriana
* Autor: Alejandro Lopez Beltran
* Fecha: 4/11/2025
* Materia: Sistemas Operativos
* Tema: OpenMP
* Descripción:
* - Introducción en laboratorio de OPENMP
* - Cláusulas y Directivas para el Programa
*****************************************************/

//librerias necesarias
#include <omp.h>//biblioteca de OpenMP: manejo de paralelismo e hilos
#include <stdio.h>//entrada y salida estándar (printf)
#include <stdlib.h>//funciones estándar como atoi(), exit(), etc.
#include <time.h>//manejo de tiempo (no usado directamente aquí, pero útil en experimentos)

int main(int argc, char *argv[]){  

    //verifica que el usuario haya pasado un argumento (el número de hilos)
    if (argc != 2) {
        //si no se pasa exactamente un argumento, se muestra un mensaje de error y termina el programa
        printf("Error\n\t%s <numHilos>\n\n", argv[0]);
        exit(0);
    }

    //convierte el argumento recibido por línea de comandos (string) a entero
    int numHilos = (int) atoi(argv[1]);
    printf("======> %d <======\n", numHilos); //muestra el número de hilos que el usuario desea usar

    //obtiene el número máximo de hilos que puede usar OpenMP según el sistema
    int maxHilos = omp_get_max_threads();
    printf("OpenMP ejecutando en Cores (HiperThreading = %d hilos)\n", maxHilos);

    //fija el número de hilos que se usarán en la región paralela
    omp_set_num_threads(numHilos);

    //región paralela: el código dentro de este bloque se ejecutará simultáneamente por todos los hilos creados
    #pragma omp parallel
    {
        //cada hilo imprime su identificador (número de hilo)
        printf("Hello World desde hilo %d\n", omp_get_thread_num());
    }

    //cuando todos los hilos terminan, se sincronizan y continúa el hilo principal
    return 0;
}

