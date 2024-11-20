# Variables
CXX = g++
CXXFLAGS = -I/usr/include/SDL2 -Wall -g
LDFLAGS = lib/libSDL2.a lib/libSDL2_image.a -lm

# Fichiers sources et objets
SRCS_CPP = main.cpp \
			srcs/system/configuration.cpp \


OBJS = $(SRCS_CPP:.cpp=.o)

# Nom de l'exécutable
TARGET = picklejumper

# Règle par défaut
all: $(TARGET)

# Compilation du binaire final
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compilation des fichiers .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJS) $(TARGET)

# Gestion des dépendances
depend: $(SRCS_CPP)
	$(CXX) $(CXXFLAGS) -MM $^ > .depend

-include .depend

# Option pour afficher tous les fichiers source
cat:
	@echo $(SRCS_CPP)
