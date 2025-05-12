add_library(sprite_sdl3_img
    src/sprite_sdl3_img.cpp
)

execute_process(
    COMMAND bash ${CMAKE_SOURCE_DIR}/scripts/get_libs.sh ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE result_libs
    OUTPUT_VARIABLE libs_output
    ERROR_VARIABLE libs_error
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Run get_modules.sh and store the output in a variable
execute_process(
    COMMAND bash ${CMAKE_SOURCE_DIR}/scripts/get_modules.sh ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE result_modules
    OUTPUT_VARIABLE modules_output
    ERROR_VARIABLE modules_error
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Target public and private includes
target_include_directories(sprite_sdl3_img
    PUBLIC include
    PRIVATE ${CMAKE_SOURCE_DIR}/core
)

# Link SDL3 to sprite_sdl3_img
target_link_libraries(sprite_sdl3_img PUBLIC SDL3 SDL3_image ${modules_output})

# Ensure that PickleEngine uses sprite_sdl3_img if present
if(TARGET PickleEngine)
    target_link_libraries(PickleEngine INTERFACE sprite_sdl3_img)
endif()

