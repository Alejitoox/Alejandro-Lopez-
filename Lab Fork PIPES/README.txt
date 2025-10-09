🧪 Laboratorio: Fork & Pipes — Sistemas Operativos - Alejandro López

📘 Descripción General
Este laboratorio tiene como propósito comprender y aplicar los conceptos de creación de procesos y comunicación entre procesos en sistemas operativos tipo UNIX, haciendo uso de las llamadas al sistema `fork()` y `pipe()` en lenguaje C.  

Los ejercicios permiten observar cómo se comportan los procesos PADRE e HIJO en la memoria, cómo se comunican entre sí y cómo comparten o no los recursos del sistema operativo.


🎯 Objetivos del Taller

1. Comprender el funcionamiento de `fork()` como mecanismo para crear procesos en UNIX.
2. Identificar la diferencia entre procesos padre e hijo** mediante el uso de `getpid()` y `getppid()`.
3. Implementar comunicación entre procesos utilizando tuberías (Pipes).
4. Experimentar con la ejecución simultánea y el caos de impresión generado por múltiples procesos.