/***********************************************************************************************************
 * Fecha: 28/10/2025
 * Autor: Alejandro López
 * Materia: Sistemas Operativos
 * Tema: Hilos - Creación correcta
 * Descripción:
 * Se implementa un programa que crea dos hilos independientes utilizando la biblioteca pthread.
 * Se verifica si los hilos se crean correctamente mediante el valor de retorno de la funcion pthread_create.
 ************************************************************************************************************/
 
//bibliotecas requeridas para salida estandar y manejo de hilos
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//recibe un puntero genérico (void *), lo convierte a (char *) para que imprima el mensaje
void *print_message_function(void *ptr) {
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);
}

void main() {
    //declaracion de los identificadorespara los dos hilos
    pthread_t thread1, thread2;

    //cadenas de texto que se pasarán como argumento a cada hilo
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";

    //variables para capturar el resultado de la función pthread_create
    int iret1, iret2;

    //cracion de los hilos, ambos ejecutan la misma funcion con distintos mensajes
    iret1 = pthread_create(&thread1, NULL, print_message_function, (void*) message1);
    iret2 = pthread_create(&thread2, NULL, print_message_function, (void*) message2);

    //se muestra el valor que se retorna por la creación de los hilos.
    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 2 returns: %d\n", iret2);
	
	exit(0);
}
