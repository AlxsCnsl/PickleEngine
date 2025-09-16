add_library(ecs_collisions STATIC
    src/ecs_collisions.cpp
)

target_include_directories(ecs_collisions PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ecs_collisions PUBLIC
    SDL3
    entt
    ecs_sprite
)
