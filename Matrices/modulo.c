/**************************************************************************************
 * Fecha: 22 de Septiembre 2025
 * Autor: Alejandro Lopez
 * Materia: Sistemas Operativos
 * Tema: Concurrencia
 * Objetivo: Hacer una metodología para la implementación de la multiplicación de matrices.
 * La idea principal, es construir paso a paso la implementación para hacer uso de la
 * biblioteca PTHREAD. Se implementa el Algoritmo Clásico de multiplicación de matrices, para
 * matrices cuadradas, es decir, la dimensión de filas es igual a la de columnas.
 * Inicialmente se genera el programa o codigo de forma general.
 * Posteriromente, 
 * A continuación se describen los paso
 *  - Reserva de memoria
 *      - Creación de punteros para matrices del tipo doble
 *      - Asignación de memoria
 *      - Ingreso de argumentos de entrada (Dimensión matriz, número de hilos)
 *      - Validación argumentos de entrada
 *      - Inicializar las matrices
 *      - Imprimir las matrices
 *      - Función para inicializar las matrices
 *      - Función para imprimir las matrices
 *      - Algoritmo clásico de multiplicación matrices
 *  - Se verifica el resultado
 *      - Función para multiplicación las matrices
 *      - Declaración vector de hilos
 *      - Creación de hilos según tamaño de vector de hilos
 *      - Crear estructura de datos que encapsule los argumentos de entrada de la función MM
 * Implementación de paralelismo: resolución de la multiplicación de matrices
 *  - Se crea el vector de hilos
 *  - Se tiene pendiente la exclusión de los hilos
 *  - Se pasa a globales las matrices
 *  - Encapsular los datos para enviarlos a la función MxM
 *  - Se desencapsulan los datos dentro de la función MxM (descomprimen)
*************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "modulo.h"

//firmas de funciones del codigo
void iniMatrix(int dim, double *matrix);
void impMatriz(int N, double *m);
void multMM(int N, const double *A, const double *B, double *C);

//funcion para la inicializacion de las matrices 
void iniMatrix(int dim, double *matrix) {
    for (int i = 0; i < dim * dim; i++) {
        matrix[i] = (double)(rand() % 10);//cada posicion se llena con un numero entero aleatorio convertido a double
    }
}

//funcion para la impresion de matrices, mientras que la dim sea menor a 
void impMatriz(int N, double *m) {
    if (N <= 10) {
        printf("\n");
        for (int i = 0; i < N * N; i++) {
            if (i % N == 0) printf("\n");
            printf("%8.2f ", m[i]);
        }
        printf("\n");
    } else {
        printf(" (N=%d, omitida para no saturar la salida)\n", N);
    }
}

//funcion para multiplicar matriz A con matriz B dando como resultado la matriz C
void multMM(int N, const double *A, const double *B, double *C) {
    for (int i = 0; i < N; i++) { //recorre fila por fila de matriz A
        for (int j = 0; j < N; j++) { ///recorre columna por columna de matriz B
            double suma = 0.0;
            const double *pA = A + i * N;
            const double *pB = B + j;  
            for (int k = 0; k < N; k++, pA++, pB += N) { //se recorren los elementos de la fila i de A y la columna j de B
                suma += (*pA) * (*pB);
            }
            C[i * N + j] = suma;//se guarda el valor calculado en la posici�n (i,j) de C
        }
    }
}
