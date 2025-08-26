/**************************************************************************************
 * Fecha: 26 de Agosto 2025
 * Autor: Alejandro Lopez
 * Materia: Sistemas Operativos
 * Tema: Reto 02!!!!
*************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int *ptr; //declaración de un puntero a entero
    ptr = malloc(15*sizeof(*ptr)); //reserva memoria dinámica para un bloque de 15 enteros (int)
    if(ptr!=NULL){ //comprueba si la asignación de memoria fue exitosa
        *(ptr+5)=480; // asigna el valor 480 al sexto entero del bloque (posición índice 5)
        printf("Value of the 6th integer is %d \n", *(ptr + 5)); //imprime el valor almacenado en el sexto entero
    }
    return 0;
}