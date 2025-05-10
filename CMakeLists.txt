cmake_minimum_required(VERSION 3.16)
project(GameEngine)

# C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# SDL3 static linking
set(SDL3_DIR "${CMAKE_SOURCE_DIR}/libs/SDL3")

# Ajouter les répertoires d'inclusions nécessaires
include_directories(
    ${SDL3_DIR}/include
    ${CMAKE_SOURCE_DIR}/core  # Ajout explicite de core ici
)

message(STATUS "Core directory: ${CMAKE_SOURCE_DIR}/core")

link_directories(${SDL3_DIR}/lib)

# Créer la cible "PickleEngine" en tant que bibliothèque INTERFACE
add_library(PickleEngine INTERFACE)

# Définir les répertoires d'inclusion pour "PickleEngine"
target_include_directories(PickleEngine INTERFACE
    ${CMAKE_SOURCE_DIR}/core  # Ajout explicite de core
    ${CMAKE_SOURCE_DIR}/modules
    ${SDL3_DIR}/include
)

# Ajouter les sous-répertoires des modules
add_subdirectory(modules)

# Déclaration de la cible principale (engine_launcher)
add_executable(engine_launcher
    engine_launcher/main.cpp
)

# Lier SDL3 et les librairies de base avec engine_launcher
target_link_libraries(engine_launcher
    PRIVATE
        SDL3
        pthread
        dl
        m


)

# Lier automatiquement PickleEngine avec engine_launcher
target_link_libraries(engine_launcher PRIVATE PickleEngine)