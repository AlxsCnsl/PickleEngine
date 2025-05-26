add_library(app_loop STATIC
    src/app_loop.cpp
)

target_include_directories(app_loop PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(app_loop PUBLIC
    SDL3
    SDL3_image
    window_render
)

