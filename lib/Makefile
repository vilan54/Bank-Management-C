# Compilador a utilizar
CC = gcc

# Opciones de compilación
CFLAGS = -lncurses -Wall -lm -lpcre -g

# Archivos fuente
SOURCES = main.c interfaz.c system.c bank.c hash.c

# Nombre del ejecutable
TARGET = main

# Regla predeterminada: construir el programa
all: $(TARGET)

# Regla para construir el ejecutable a partir de los archivos fuente
$(TARGET): $(SOURCES)
	$(CC) -o $(TARGET) $(SOURCES) $(CFLAGS)

# Regla para limpiar los archivos generados
clean:
	rm -f $(TARGET)

