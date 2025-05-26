add_library(ecs_base_tools STATIC
    src/ecs_base_tools.cpp
)

target_include_directories(ecs_base_tools PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ecs_base_tools PUBLIC
    SDL3
    SDL3_image
    entt
)