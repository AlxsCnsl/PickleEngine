cmake_minimum_required(VERSION 3.16)
project(GameEngine LANGUAGES CXX)

# 🧱 Options générales
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# 📁 Répertoires de libs locales
set(SDL3_DIR "${CMAKE_SOURCE_DIR}/libs/SDL3")
set(SDL3_IMGDIR "${CMAKE_SOURCE_DIR}/libs/SDL3_image")

# 📚 Bibliothèque statique SDL3
add_library(SDL3 STATIC IMPORTED)
set_target_properties(SDL3 PROPERTIES
    IMPORTED_LOCATION "${SDL3_DIR}/lib/libSDL3.a"
    INTERFACE_INCLUDE_DIRECTORIES "${SDL3_DIR}/include"
)

# 📚 Bibliothèque statique SDL3_image
add_library(SDL3_image STATIC IMPORTED)
set_target_properties(SDL3_image PROPERTIES
    IMPORTED_LOCATION "${SDL3_IMGDIR}/lib/libSDL3_image.a"
    INTERFACE_INCLUDE_DIRECTORIES "${SDL3_IMGDIR}/include"
)


# 🧩 Bibliothèque principale du moteur
add_library(PickleEngine INTERFACE)
target_include_directories(PickleEngine INTERFACE
    ${CMAKE_SOURCE_DIR}/core
    ${CMAKE_SOURCE_DIR}/modules
    ${SDL3_DIR}/include
    ${SDL3_IMGDIR}/include
)
target_link_libraries(PickleEngine INTERFACE SDL3 SDL3_image)


# 🔁 Inclure automatiquement les dossiers /modules/*/include
file(GLOB_RECURSE MODULE_INCLUDE_DIRS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/modules/*/include)
foreach(INC_DIR ${MODULE_INCLUDE_DIRS})
    if(IS_DIRECTORY "${INC_DIR}")
        target_include_directories(PickleEngine INTERFACE "${INC_DIR}")
    endif()
endforeach()

# 📁 Ajouter les sous-dossiers des modules
add_subdirectory(modules)

# 🚀 Exécutable principal
add_executable(engine_launcher engine_launcher/main.cpp)

# 🔗 Lier les dépendances


if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(engine_launcher PRIVATE PickleEngine)
    message("WHIOGUUUIUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYy")
else()
    target_link_libraries(engine_launcher
        PRIVATE
            pthread
            dl
            m
            PickleEngine
    )
    message("WHIOGUUUIUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYy")
endif()



