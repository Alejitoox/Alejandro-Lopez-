/**************************************************************************************
 * Fecha: 26 de Agosto 2025
 * Autor: Alejandro Lopez
 * Materia: Sistemas Operativos
 * Tema: Reto 01!!!!
*************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char *p; // puntero a char SIN inicializar
    char *q=NULL; // puntero a char inicializado a NULL
    printf("Address of p = %s\n",p); // intenta imprimir usando %s
    
    strcpy(p,"Hi, im the BEST in Operating Systems!!!"); // intenta copiar la cadena al lugar apuntado por p
    printf("%s\n", p); // intenta imprimir lo que hay en p
    printf("About to copy \"Goodbye\" to q\n"); // imprime el texto
    strcpy(q, "Goodbye"); // intenta copiar goodbye en la direccion apuntada por q
    printf("String copied\n"); //indica que la copia tuvo exito
    printf("%s\n", q); // intenta imprimir q, pero nunca fue asignado

    return 0;
}