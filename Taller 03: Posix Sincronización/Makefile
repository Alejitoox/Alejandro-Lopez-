# Opciones del compilador
CC = gcc
# Flags para C, -g para debug, -Wall para warnings
CFLAGS = -g -Wall
# Flags para enlazar (linking)
# -lrt es para la librería Real Time (necesaria para shm_open y sem_open)
# -pthread es para la librería Pthreads
LDFLAGS_POSIX = -lrt
LDFLAGS_PTHREAD = -pthread

# Define los nombres de los ejecutables
TARGETS = producer consumer posixSincro

# Regla por defecto: compila todo
all: $(TARGETS)

# Regla para compilar producer
producer: producer.c
	$(CC) $(CFLAGS) -o producer producer.c $(LDFLAGS_POSIX)

# Regla para compilar consumer
consumer: consumer.c
	$(CC) $(CFLAGS) -o consumer consumer.c $(LDFLAGS_POSIX)

# Regla para compilar posixSincro
posixSincro: posixSincro.c
	$(CC) $(CFLAGS) -o posixSincro posixSincro.c $(LDFLAGS_PTHREAD)

# Regla para limpiar los ejecutables generados
clean:
	rm -f $(TARGETS)
