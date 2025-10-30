/*
 * Taller 01 - Sistemas Operativos
 * Pontificia Universidad Javeriana
 *
 * Estudiantes:
 * - (Tu nombre)
 * - (Nombre compañero 1)
 * - (Nombre compañero 2)
 *
 * Implementación de procesos con fork() e IPC con pipe()
 * para el cálculo de sumas de arreglos leídos desde archivos.
 */

#include <stdio.h>      // Para printf, fopen, fscanf, fclose
#include <stdlib.h>     // Para malloc, free, atoi, exit
#include <unistd.h>     // Para fork, pipe, read, write, close
#include <sys/wait.h>   // Para wait

/**
 * @brief Lee N enteros desde un archivo de texto y los carga en un vector dinámico.
 * @param nombre_archivo El path del archivo a leer.
 * @param N La cantidad de enteros a leer.
 * @return Un puntero al vector de enteros (int*).
 * * Basado en los requisitos del Punto 3 del taller [cite: 939] 
 * y el uso de memoria dinámica (malloc).
 */
int* leer_fichero(const char* nombre_archivo, int N) {
    FILE *archivo;
    // 1. Asignar memoria dinámica para el vector 
    int *vector = (int *)malloc(N * sizeof(int));
    
    if (vector == NULL) {
        perror("Error al asignar memoria con malloc");
        exit(EXIT_FAILURE);
    }

    // 2. Abrir y leer el archivo
    archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    // 3. Llenar el vector
    for (int i = 0; i < N; i++) {
        if (fscanf(archivo, "%d", &vector[i]) != 1) {
            fprintf(stderr, "Error al leer el elemento %d del archivo %s\n", i, nombre_archivo);
            exit(EXIT_FAILURE);
        }
    }

    fclose(archivo);
    return vector;
}

/**
 * @brief Calcula la suma de los elementos de un vector.
 * @param vector El arreglo de enteros.
 * @param N El tamaño del arreglo.
 * @return La suma total (int).
 */
int sumar_vector(int* vector, int N) {
    int suma = 0;
    for (int i = 0; i < N; i++) {
        suma += vector[i];
    }
    return suma;
}

int main(int argc, char *argv[]) {

    // --- 1. Validación y Paso de Argumentos (Punto 2) --- 
    if (argc != 5) {
        fprintf(stderr, "Uso: %s N1 archivo00 N2 archivo01\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int N1 = atoi(argv[1]);        // [cite: 935]
    char *archivo00 = argv[2];    // [cite: 935]
    int N2 = atoi(argv[3]);        // [cite: 936]
    char *archivo01 = argv[4];    // [cite: 937]

    // --- 2. Lectura de Ficheros (Punto 3) --- [cite: 939]
    int *vector1 = leer_fichero(archivo00, N1);
    int *vector2 = leer_fichero(archivo01, N2);

    // --- 3. Creación de Pipes (Punto 4) ---
    // El Padre debe recibir 3 cálculos, por lo tanto, necesita 3 pipes.
    // fd_gh -> Pipe para el Grand Hijo
    // fd_h2 -> Pipe para el Segundo Hijo
    // fd_h1 -> Pipe para el Primer Hijo
    int fd_gh[2], fd_h2[2], fd_h1[2];

    // Se usa la llamada al sistema pipe() 
    if (pipe(fd_gh) == -1 || pipe(fd_h2) == -1 || pipe(fd_h1) == -1) {
        perror("Error al crear pipes");
        exit(EXIT_FAILURE);
    }

    // --- 4. Creación de Procesos (Punto 4) --- [cite: 943]
    pid_t pid1, pid2;

    // --- Creación del Primer Hijo ---
    pid1 = fork(); // 
    if (pid1 < 0) {
        perror("Error en fork (Primer Hijo)");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // --- CÓDIGO DEL PRIMER HIJO --- 
        pid_t pid_nieto;

        // Cerrar extremos de lectura (buena práctica)
        close(fd_gh[0]);
        close(fd_h2[0]);
        close(fd_h1[0]);

        // Cerrar pipes que no usa (el de H2)
        close(fd_h2[1]);

        // --- Creación del Grand Hijo ---
        pid_nieto = fork();
        if (pid_nieto < 0) {
            perror("Error en fork (Grand Hijo)");
            exit(EXIT_FAILURE);
        }

        if (pid_nieto == 0) {
            // --- CÓDIGO DEL GRAND HIJO --- 
            // Cerrar pipe que no usa (el de H1)
            close(fd_h1[1]);
            
            // Tarea: Calcular suma del archivo 00
            int suma_gh = sumar_vector(vector1, N1);
            
            // Escribir en el pipe del Grand Hijo
            write(fd_gh[1], &suma_gh, sizeof(suma_gh));
            
            // Cerrar su pipe y terminar
            close(fd_gh[1]);
            exit(EXIT_SUCCESS);
        }

        // --- CÓDIGO DEL PRIMER HIJO (continuación) ---
        // Cerrar pipe que no usa (el de GH)
        close(fd_gh[1]);
        
        // Esperar a que el Grand Hijo termine 
        wait(NULL); 
        
        // Tarea: Calcular suma total de ambos arreglos
        int suma_total = sumar_vector(vector1, N1) + sumar_vector(vector2, N2);
        
        // Escribir en el pipe del Primer Hijo
        write(fd_h1[1], &suma_total, sizeof(suma_total));
        
        // Cerrar su pipe y terminar
        close(fd_h1[1]);
        exit(EXIT_SUCCESS);
    }

    // --- Creación del Segundo Hijo (solo el Padre ejecuta esto) ---
    pid2 = fork();
    if (pid2 < 0) {
        perror("Error en fork (Segundo Hijo)");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // --- CÓDIGO DEL SEGUNDO HIJO --- 
        // Cerrar extremos de lectura (buena práctica)
        close(fd_gh[0]);
        close(fd_h2[0]);
        close(fd_h1[0]);
        
        // Cerrar pipes que no usa (el de GH y H1)
        close(fd_gh[1]);
        close(fd_h1[1]);
        
        // Tarea: Calcular suma del archivo 01
        int suma_h2 = sumar_vector(vector2, N2);
        
        // Escribir en el pipe del Segundo Hijo
        write(fd_h2[1], &suma_h2, sizeof(suma_h2));
        
        // Cerrar su pipe y terminar
        close(fd_h2[1]);
        exit(EXIT_SUCCESS);
    }

    // --- CÓDIGO DEL PADRE --- 
    
    // Cerrar todos los extremos de escritura (buena práctica)
    close(fd_gh[1]);
    close(fd_h2[1]);
    close(fd_h1[1]);

    // Esperar a que los DOS hijos directos terminen
    wait(NULL);
    wait(NULL);

    // Tarea: Recibir los cálculos desde los 3 procesos
    int suma1_recibida, sumaB_recibida, sumatotal_recibida;

    read(fd_gh[0], &suma1_recibida, sizeof(int));
    read(fd_h2[0], &sumaB_recibida, sizeof(int));
    read(fd_h1[0], &sumatotal_recibida, sizeof(int));

    // Imprimir los resultados
    printf("--- Resultados de los cálculos ---\n");
    printf("Suma Arreglo 01 (calculada por Grand Hijo): %d\n", suma1_recibida);
    printf("Suma Arreglo 02 (calculada por Segundo Hijo): %d\n", sumaB_recibida);
    printf("Suma Total (calculada por Primer Hijo):    %d\n", sumatotal_recibida);

    // Cerrar extremos de lectura
    close(fd_gh[0]);
    close(fd_h2[0]);
    close(fd_h1[0]);

    // --- 5. Liberar Memoria (Punto 3) --- 
    free(vector1); // [cite: 3761]
    free(vector2); // [cite: 3761]

    return 0;
}
