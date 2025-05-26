cmake_minimum_required(VERSION 3.21)
project(PickleEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 🎯 Dépendances externes
add_subdirectory(libs/SDL3)
add_subdirectory(libs/SDL3_image)

# 📚 entt (header-only)
add_library(entt INTERFACE)
target_include_directories(entt INTERFACE ${CMAKE_SOURCE_DIR}/libs/entt/include)

# 🧠 Bibliothèque principale de ton moteur
add_library(PickleEngine INTERFACE)
target_include_directories(PickleEngine INTERFACE
    ${CMAKE_SOURCE_DIR}/core
    ${CMAKE_SOURCE_DIR}/libs/SDL3/include
    ${CMAKE_SOURCE_DIR}/libs/SDL3_image/include
    ${CMAKE_SOURCE_DIR}/libs/entt/include
)

# 📁 Code de base (core)
add_subdirectory(core)

# 🧩 Modules (automatisé)
file(GLOB MODULE_CMAKELISTS RELATIVE ${CMAKE_SOURCE_DIR}/modules/ ${CMAKE_SOURCE_DIR}/modules/*/CMakeLists.txt)

set(MODULE_NAMES "")
foreach(module_cmakelists ${MODULE_CMAKELISTS})
    get_filename_component(module_dir ${module_cmakelists} DIRECTORY)
    message(STATUS "🔗 Ajout automatique du module : ${module_dir}")
    add_subdirectory(modules/${module_dir})
    list(APPEND MODULE_NAMES ${module_dir})
endforeach()

# 🔗 Link tous les modules à PickleEngine automatiquement
foreach(module_name IN LISTS MODULE_NAMES)
    if(TARGET ${module_name})
        target_link_libraries(PickleEngine INTERFACE ${module_name})
    else()
        message(WARNING "⚠️ Le module ${module_name} n’a pas défini de target correspondante.")
    endif()
endforeach()


# 🚀 Application de lancement
add_subdirectory(engine_launcher)
