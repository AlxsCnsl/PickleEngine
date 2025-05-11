add_library(app_loop_sdl3
    src/app_loop_sdl3.cpp
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
target_include_directories(app_loop_sdl3
    PUBLIC include
    PRIVATE ${CMAKE_SOURCE_DIR}/core
)

# Link SDL3 to app_loop_sdl3
target_link_libraries(app_loop_sdl3 PUBLIC ${libs_output} ${modules_output})

# Ensure that PickleEngine uses app_loop_sdl3 if present
if(TARGET PickleEngine)
    target_link_libraries(PickleEngine INTERFACE app_loop_sdl3)
endif()

