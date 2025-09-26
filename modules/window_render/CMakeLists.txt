# modules/<module>/CMakeLists.txt
cmake_minimum_required(VERSION 3.19) # optional when included, safe

set(MODULE_NAME "window_render")
set(TARGET_NAME "pickle_module_${MODULE_NAME}")

project(${TARGET_NAME} LANGUAGES CXX)


add_library(${TARGET_NAME} STATIC)

target_sources(${TARGET_NAME}
  PRIVATE
    src/${MODULE_NAME}.cpp
)

target_include_directories(${TARGET_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/pickle/modules/${MODULE_NAME}>
)

# link core and any external libs
target_link_libraries(${TARGET_NAME}
  PUBLIC
    Pickle::Core
    SDL3::SDL3
)

target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)

# alias
add_library(Pickle::Module::${MODULE_NAME} ALIAS ${TARGET_NAME})

# install
install(TARGETS ${TARGET_NAME} EXPORT PickleEngineTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include/pickle/modules/${MODULE_NAME})