# SDL3 statique
add_library(SDL3 STATIC IMPORTED GLOBAL)
set_target_properties(SDL3 PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/libs/SDL3/lib/libSDL3.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/libs/SDL3/include"
)

# SDL3_image statique
add_library(SDL3_image STATIC IMPORTED GLOBAL)
set_target_properties(SDL3_image PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/libs/SDL3_image/lib/libSDL3_image.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/libs/SDL3_image/include"
)
