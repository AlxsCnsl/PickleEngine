add_library(ecs_sprite STATIC
    src/ecs_sprite.cpp
)

target_include_directories(ecs_sprite PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ecs_sprite PUBLIC
    SDL3
    SDL3_image
    entt
    window_render
)
