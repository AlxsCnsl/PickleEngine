add_library(window_render STATIC
    src/window_render.cpp
)

target_include_directories(window_render PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(window_render PUBLIC
    SDL3
)

# Tu peux même ajouter une interface ou config CMake plus tard ici

