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
    //n=numero de elementos, i=indice para el for, ptr=puntero a entero, sum=acumulador inicializado en 0
    int n, i, *ptr, sum=0;
    printf("Enter number of elements: "); //pide al usuario cuántos elementos desea ingresar
    scanf("%d", &n);//lee la cantidad ingresada por el usuario y la guarda en n
    ptr=(int*)calloc(n, sizeof(int)); //reserva memoria dinámica para n enteros
    if(ptr==NULL){ //verifica si la memoria no pudo ser asignada
        printf("Error! memory not allocated."); //imprime msj de error
        exit(0); //termina el programa
    }
    
    for(i=0; i<n; i++){ //recorre desde 0 hasta n-1
    printf("Enter element %d: ", i + 1); //pide al usuario el elemento número i+1
        scanf("%d", ptr+i); //almacena el número ingresado en la posición correspondiente
        sum += *(ptr+i); //suma el valor recién ingresado al acumulador
    }
    printf("Sum = %d", sum); //imprime la suma total de los elementos ingresados
    free(ptr);//libera la memoria asignada dinámicamente
    return 0;
}