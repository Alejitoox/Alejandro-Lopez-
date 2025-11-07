/*****************************************************
* Pontificia Universidad Javeriana
* Autor: Alejandro Lopez Beltran
* Fecha: 4/11/2025
* Materia: Sistemas Operativos
* Tema: OpenMP - Cláusulas de Datos (private)
* Descripción:
* - Ejemplo del uso de la cláusula "private" en un bucle paralelo
* - Demostración de variables privadas y efectos de condición de carrera
*****************************************************/
//librerias necesarias
#include <omp.h> //biblioteca necesaria para invocar la API de OpenMP
#include <stdio.h> //entrada y salida estándar (printf)
#include <stdlib.h> //funciones generales (malloc, atoi, etc.)

int main(){
    int i;//variable de iteración para el bucle
    const int N = 1000;//límite del bucle: cantidad de iteraciones
    int a = 50;//valor base usado para las sumas
    int b = 0; //variable acumuladora o resultado final

    #pragma omp parallel for private(i) private(b) //a diferencia del lab03 aqui usamos private(b)
    for (i = 0; i < N; i++) {
        b = a + i; //cada hilo calcula un valor diferente para b
    }
    
    //el valor de 'b' mostrado dependerá del hilo que termine de último
    //por eso puede variar en cada ejecución
    printf("a = %d  b = %d  (Se espera a = 50  b = 1049)\n", a, b);

    return 0; // Fin del programa
}

