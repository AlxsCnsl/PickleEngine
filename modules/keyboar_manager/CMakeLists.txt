add_library(keyboar_manager STATIC
    src/keyboar_manager.cpp
)

target_include_directories(keyboar_manager PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(keyboar_manager PUBLIC
    SDL3
)
