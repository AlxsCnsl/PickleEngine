# Bibliothèque statique du moteur
add_library(pickle_core STATIC
    src/read_conf.cpp
    src/write_conf.cpp
)

target_include_directories(pickle_core PUBLIC
    ${PROJECT_SOURCE_DIR}/core/include
)

target_link_libraries(pickle_core PUBLIC
    SDL3
    SDL3_image
)
