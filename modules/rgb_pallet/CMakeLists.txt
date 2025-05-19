add_library(rgb_pallet
    src/rgb_pallet.cpp
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
target_include_directories(rgb_pallet
    PUBLIC include
    PRIVATE ${CMAKE_SOURCE_DIR}/core
)

# Link SDL3 to rgb_pallet
target_link_libraries(rgb_pallet PUBLIC ${libs_output} ${modules_output})

# Ensure that PickleEngine uses rgb_pallet if present
if(TARGET PickleEngine)
    target_link_libraries(PickleEngine INTERFACE rgb_pallet)
endif()

