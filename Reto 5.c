/**************************************************************************************
 * Fecha: 26 de Agosto 2025
 * Autor: Alejandro Lopez
 * Materia: Sistemas Operativos
 * Tema: Reto 04!!!!
*************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    //ptr=puntero a entero para manejar memoria dinámica
    //i=variable de control para los bucles for
    //n1=tamaño inicial del bloque de memoria
    //n2=tamaño nuevo al que se reajustará el bloque
    int *ptr, i, n1, n2;

    printf("Enter size: "); //se ingresa el tamanio inicial del arreglo dinamico
    scanf("%d", &n1); //lee el tamanio y lo guarda en n1

    ptr = (int*) malloc(n1 * sizeof(int)); //reserva memoria para n1 y malloc devuelve un puntero al bloque reservado
    printf("Addresses of previously allocated memory:\n"); //imprime texto antes de mostrar las direcciones
    for (i=0; i<n1; i++) //imprime la dirección de cada entero reservado
        printf("\n\np = %p\n", ptr+i); 
    printf("\nEnter the new size: "); //se ingresa el nuevo tamanio
    scanf("%d", &n2); //lo guarda en n2
    ptr = realloc(ptr, n2 * sizeof(int)); //ajusta el bloque de memoria al nuevo tamanio
    printf("Addresses of newly allocated memory:\n");//imprime texto antes de mostrar las direcciones
    for (i=0; i<n2; i++) // imprime la dirección de cada entero en el nuevo tamanio
        printf("\n\np = %p\n", ptr+i);
    free(ptr); //libera la memoria
}