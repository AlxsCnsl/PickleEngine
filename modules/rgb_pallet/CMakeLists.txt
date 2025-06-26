add_library(rgb_pallet STATIC
    src/rgb_pallet.cpp
)

target_include_directories(rgb_pallet PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(rgb_pallet PUBLIC
    SDL3
    window_render
)