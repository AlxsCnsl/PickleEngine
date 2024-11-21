# Variables
CXX = g++
CFLAGS = -I/usr/include/SDL2 -Wall -g
LDFLAGS = lib/libSDL2.a lib/libSDL2_image.a -lm

# Fichiers sources et objets
SRCS = main.cpp \
			srcs/window.cpp \
			srcs/system/configuration.cpp \


OBJ = $(SRCS:.cpp=.o)
TARGET = picklejumper

# Règle par défaut
all: $(TARGET)

# Compilation du binaire final
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation des fichiers .c en .o
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJ) $(TARGET)

# Pour afficher tout les .C
cat:
	cat $(SRCS)
