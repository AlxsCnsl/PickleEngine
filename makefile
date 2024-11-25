# Compilateur et options
CXX = g++
CXXFLAGS = -Iinclude/SDL2 -Wall -std=c++17 -Iinclude -g

# Répertoires
SRCDIR = srcs
LIBDIR = lib
BINDIR = bin
BUILDDIR = build

# Fichiers
SOURCES = main.cpp \
          $(SRCDIR)/system/window.cpp \
          $(SRCDIR)/system/configuration.cpp

OBJECTS = $(addprefix $(BUILDDIR)/, $(SOURCES:.cpp=.o))
EXECUTABLE = $(BINDIR)/Picle_engine

# Bibliothèques
LDFLAGS = -L$(LIBDIR) -lSDL2 -lSDL2_image -lSDL2main

# Règles
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(EXECUTABLE)