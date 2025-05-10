add_library(window_render
    src/window_render.cpp
)

# Cibler les inclusions publiques et privées pour window_render
target_include_directories(window_render
    PUBLIC include
    PRIVATE ${CMAKE_SOURCE_DIR}/core  # core doit être privé pour window_render
)

# Lier SDL3 à window_render
target_link_libraries(window_render PRIVATE SDL3)

# Assurer que PickleEngine utilise window_render si il est présent
if(TARGET PickleEngine)
    target_link_libraries(PickleEngine INTERFACE window_render)
endif()
