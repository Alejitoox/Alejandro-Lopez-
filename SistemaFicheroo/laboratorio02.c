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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // Para manejo de directorios
#include <time.h>   // Para manejo de fechas (ctime)

int main() {
    DIR *dir;
    struct dirent *rdl;
    struct stat atr;
    char nombredir[30], nombrefich[50];

    printf("Introduce el nombre de un directorio: ");
    fgets(nombredir, sizeof(nombredir), stdin);
    nombredir[strlen(nombredir) - 1] = '\0'; // Elimina el salto de línea

    // Intenta abrir el directorio
    if ((dir = opendir(nombredir)) == NULL) {
        printf("Error: No se puede abrir el directorio\n");
        return -1;
    }

    // Recorre todos los elementos del directorio
    while ((rdl = readdir(dir)) != NULL) {
        strcpy(nombrefich, nombredir);
        strcat(nombrefich, "/");
        strcat(nombrefich, rdl->d_name);

        // Obtiene los atributos del archivo
        stat(nombrefich, &atr);

        // Verifica si es un archivo regular
        if (S_ISREG(atr.st_mode)) {
            printf("FICHERO:%s: fecha acceso %s, en sgdos %ld\n",
                   rdl->d_name,
                   ctime(&atr.st_mtime),
                   (long)atr.st_mtime);
        }
    }

    closedir(dir); // Cierra el directorio
    return 0;      // Finaliza correctamente
}
