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
    char *q=NULL; //puntero a char inicializado a NULL
    printf("Requesting space for \"Goodbye\" \n"); //solicita memoria para guardar 
    q = (char*)malloc(strlen("Goodbye")+1); 
    
    if(!q) //verifica si la asignacion fue exitosa
        perror("Failed to allocate space because");
        exit(1);
    }
    
    printf("About to copy \"Goodbye\" to q at address %s \n", q); //muestra la direccion asignada
    strcpy(q, "Goodbye"); //copia al bloque reservado
    printf("String copied\n"); 
    printf("%s \n", q); //imprime la memoria reservada
    
    return 0;
}