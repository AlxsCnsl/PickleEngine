add_library(easy_drawing STATIC
    src/easy_drawing.cpp
)

target_include_directories(easy_drawing PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(easy_drawing PUBLIC
    SDL3
    SDL3_image
    window_render
)


