/*************************************************************************
 * Pontificia Universidad Javeriana
 * Autor: Alejandro Lopez Beltran
 * Fecha: 11/10/2025
 * Materia: Sistemas Operativos
 * Tema: Sistemas de FIcheros
 * Descripción: Programa en C que lea de teclado el nombre
 * de un directorio y muestre en pantalla el nombre y el tamaño de
 * los ficheros que contiene.
 *************************************************************************/

//Bibibliotecas necesarias para el funcionamiento

#include <sys/types.h> //tipos de datos para el sistema de archivos
#include <sys/stat.h> //información sobre archivos (estructura stat)
#include <fcntl.h> //constantes para control de archivos
#include <stdio.h> //funciones de entrada/salida estándar (printf, fgets)
#include <unistd.h> //funciones POSIX (close, etc.)
#include <stdlib.h> //funciones generales (malloc, exit, etc.)
#include <string.h> //manejo de cadenas (strlen, strcpy, strcat)
#include <dirent.h> //manejo de directorios (opendir, readdir, closedir)

int main() {
    DIR *d; //puntero al directorio
    char nomdir[90], nomfich[90]; //nombre del directorio y ruta de cada archivo
    struct stat datos; //estructura para guardar información del archivo
    struct dirent *direc; //rstructura que almacena entradas del directorio

    //se solicita al usuario el nombre de un directorio
    printf("Introduzca el Nombre de un Directorio: ");
    fgets(nomdir, sizeof(nomdir), stdin);
    nomdir[strlen(nomdir) - 1] = '\0'; //elimina el salto de línea final del input

    //intenta abrir el directorio especificado
    if ((d = opendir(nomdir)) == NULL) {
        printf("El directorio no existe\n");
        return -1;
    }

    //lee cada elemento dentro del directorio
    while ((direc = readdir(d)) != NULL) {
        //construye la ruta completa del archivo o subdirectorio
        strcpy(nomfich, nomdir);
        strcat(nomfich, "/");
        strcat(nomfich, direc->d_name);

        //obtiene información del archivo con 'stat'
        stat(nomfich, &datos);
        
        //verifica si el elemento es un archivo regular
        if (S_ISREG(datos.st_mode)) {
            //muestra el nombre del archivo y su tamaño en bytes
            printf("Nombre: %s\t|\tTamaño: %ld\n", direc->d_name, datos.st_size);
        }
    } //finaliza el recorrido del directorio
    
    closedir(d); //cierra el directorio abierto
    return 0;
}
