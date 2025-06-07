
# Nombre del compilador
CC = gcc

# Flags del compilador que usamos en todos los proyectos en c
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99

# Archivos fuente y objetos
SRCS = main.c queue.c queue_helpers.c
OBJS = $(SRCS:.c=.o)

# Nombre del ejecutable
EXEC = queue2

# Flags de Valgrind
VALGRIND = valgrind --leak-check=yes

# Regla por defecto
all: $(EXEC)

# Regla para compilar el ejecutable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regla para compilar los archivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para ejecutar Valgrind
valgrind: $(EXEC)
	$(VALGRIND) ./$(EXEC)

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJS) $(EXEC)

# Regla para limpiar todos los archivos generados, incluyendo archivos temporales y de respaldo
cleanall: clean
	rm -f *~ *.bak

# Declaraciones de phony para evitar conflictos con archivos que puedan tener estos nombres
.PHONY: all clean cleanall valgrind

