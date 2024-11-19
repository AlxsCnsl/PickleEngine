# Variables
CC = gcc
CFLAGS = -I/usr/include/SDL2 -Wall -g
LDFLAGS = lib/libSDL2.a lib/libSDL2_image.a -lm
SRCS = main.c \
	srcs/window.c \
	srcs/renderer.c \
	srcs/deltatime.c \
	srcs/graphic/sprite.c \
	srcs/system/sys_input.c \
	srcs/system/configuration.c \
	srcs/object/collide_box.c \
	srcs/object/object.c

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