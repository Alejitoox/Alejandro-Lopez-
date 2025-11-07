/*****************************************************
* Pontificia Universidad Javeriana
* Autor: Alejandro Lopez Beltran
* Fecha: 4/11/2025
* Materia: Sistemas Operativos
* Tema: OpenMP - Cláusulas de Datos (private)
* Descripción:
* - Ejemplo del uso de la cláusula "private" en un bucle paralelo
* - Demostración de variables privadas en OpenMP
*****************************************************/

//librerias necesarias
#include <omp.h> //header necesario para invocar API OpenMP
#include <stdio.h> //funciones estándar de entrada y salida (printf)
#include <stdlib.h> //funciones generales (malloc, free, atoi, etc.)

int main(){
    int i;//variable de iteración
    const int N = 1000; //constante que define el número de iteraciones del bucle
    int a = 50; //variable base usada dentro del cálculo
    int b = 0; //variable acumuladora (resultado final esperado)

	//"private(i)" y "private(a)" indican que cada hilo tendrá su propia copia de las variables i y a, evitando conflictos
    #pragma omp parallel for private(i) private(a)
    for (i = 0; i < N; i++) {
        b = a + i; //cada hilo calcula su propio valor local de b
    }
    //al finalizar el bloque paralelo, los valores privados de b no se acumulan
    //el valor mostrado de b será el del hilo que terminó de último

    printf("a = %d  b = %d  (Se espera a = 50  b = 1049)\n", a, b);

    return 0;
}

