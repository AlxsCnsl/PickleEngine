add_library(sprite_class STATIC
    src/sprite_class.cpp
)

target_include_directories(sprite_class PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(sprite_class PUBLIC
    SDL3
    SDL3_image
    window_render
)

# Tu peux même ajouter une interface ou config CMake plus tard ici

