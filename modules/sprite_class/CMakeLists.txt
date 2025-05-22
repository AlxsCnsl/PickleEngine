add_library(sprite_class
    src/sprite_class.cpp
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
target_include_directories(sprite_class
    PUBLIC include
    PRIVATE ${CMAKE_SOURCE_DIR}/core
)

# Link SDL3 to sprite_class
target_link_libraries(sprite_class PUBLIC SDL3 SDL3_image ${modules_output})

# Ensure that PickleEngine uses sprite_class if present
if(TARGET PickleEngine)
    target_link_libraries(PickleEngine INTERFACE sprite_class)
endif()

