add_library(window_render
    src/window_render.cpp
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
target_include_directories(window_render
    PUBLIC include
    PRIVATE ${CMAKE_SOURCE_DIR}/core
)

# Link SDL3 to window_render
target_link_libraries(window_render PRIVATE ${libs_output} ${modules_output})

# Ensure that PickleEngine uses window_render if present
if(TARGET PickleEngine)
    target_link_libraries(PickleEngine INTERFACE window_render)
endif()
