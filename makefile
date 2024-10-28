# Variables
CC = gcc
CFLAGS = -I/usr/include/SDL2 -Wall -g
LDFLAGS = -lSDL2 -lSDL2_image
SRCS = main.c \
	srcs/core/window.c \
	srcs/core/game.c \
	srcs/core/renderer.c \
	srcs/core/deltatime.c \
	srcs/core/sprite.c \
	srcs/core/input/sys_input.c

OBJ = $(SRCS:.c=.o)
TARGET = picklejumper

# Règle par défaut
all: $(TARGET)

# Compilation du binaire final
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation des fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJ) $(TARGET)

# Pour afficher tout les .C
cat:
	cat $(SRCS)
