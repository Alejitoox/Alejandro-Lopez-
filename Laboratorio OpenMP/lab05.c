/*****************************************************
* Pontificia Universidad Javeriana
* Autor: Alejandro Lopez Beltran
* Fecha: 4/11/2025
* Materia: Sistemas Operativos
* Tema: OpenMP – Cálculo de la sumatoria de la función SENO
* Descripción:
* - Implementación de una sumatoria del seno mediante paralelismo con OpenMP
* - Uso de funciones matemáticas del GCC (sin)
* - Control del número de hilos y demostración de cláusula reduction
*****************************************************/

//librerias necesarias
#include <omp.h>//biblioteca principal de OpenMP
#include <stdio.h>//entrada y salida estándar
#include <stdlib.h>//funciones estándar (malloc, atoi, exit)
#include <time.h>//medición de tiempos (no usada directamente aquí)
#include <math.h>//funciones matemáticas (sin)
#include <sys/time.h>//para medir tiempo con gettimeofday()


#define MIN(x, y) (((x) < (y)) ? (x) : (y))

//variables globales para medición de tiempo
struct timeval inicio, fin;

void InicioMuestra() {
    gettimeofday(&inicio, (void *)0);
}


void FinMuestra() {
    gettimeofday(&fin, (void *)0);
    fin.tv_usec -= inicio.tv_usec;
    fin.tv_sec -= inicio.tv_sec;
    double tiempo = (double)(fin.tv_sec * 1000000 + fin.tv_usec);
    printf("%9.0f \n", tiempo);
}

double funcion(int i) {
    int j, inicio = i * 4 / 2, final = inicio + i;
    double valor = 0;

    for (int j = inicio; j < final; j++) {
        valor += sin(j);//suma el seno de cada número del rango
    }

    return valor;//devuelve la sumatoria parcial
}

int main(int argc, char *argv[]) {
    double sumatoria = 0;//variable acumuladora global
    int i, N = 30000; //define el número de iteraciones

    //fijar número de hilos a partir del argumento del usuario
    if (argc != 2) {
        printf("Error\n\t%s ejecutable numHilos\n\n", argv[0]);
        exit(0);
    }

    int numHilos = (int)atoi(argv[1]);
    printf("====> %d ====\n", numHilos);

    int maxHilos = omp_get_max_threads(); //detecta máximo de hilos del sistema
    printf("OpenMP ejecutando en Cores (HiperThreading = %d hilos)\n", maxHilos);

    //configurar número de hilos que se desea usar
    omp_set_num_threads(numHilos);

    //inicio de región paralela controlada por OpenMP
    #pragma omp parallel
    {
        //solo el hilo principal (master) imprime esta información
        #pragma omp master
        printf("MAX hilos: %d || Hilos fijados: %d\n",
               omp_get_max_threads(), omp_get_num_threads());

        //todos los hilos ejecutan el siguiente bucle en paralelo
        #pragma omp for reduction(+:sumatoria)
        for (i = 0; i < N; i++) {
            sumatoria += funcion(i);
        }
    }

    //resultado final de la sumatoria
    printf("Valor sumatoria de función SENO = %f\n", sumatoria);

    return 0;
}

