cmake_minimum_required(VERSION 3.20)


# EnTT (header-only)-----------------------------------------------------------
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/entt")
add_library(entt INTERFACE)
target_include_directories(entt INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/entt/include
)

# SDL3 ------------------------------------------------------------------------
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/SDL3/install")
#set(SDL3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SDL3/build")
find_package(SDL3 CONFIG REQUIRED)


# SDL3_image-------------------------------------------------------------------
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}SDL3_image/lib/cmake")
set(SDL3_image_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SDL3_image/lib/cmake/SDL3_image)
find_package(SDL3_image REQUIRED CONFIG)


#******************************************************************************
add_library(project_libs INTERFACE)
target_link_libraries(project_libs INTERFACE
    entt
    SDL3::SDL3
    SDL3_image::SDL3_image
)