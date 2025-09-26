# core/CMakeLists.txt
add_library(pickle_core STATIC)

target_sources(pickle_core
  PRIVATE
    src/read_conf.cpp
    src/write_conf.cpp
)

target_include_directories(pickle_core
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(pickle_core PUBLIC cxx_std_17)
target_compile_options(pickle_core PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>)

# Create alias for external use
add_library(Pickle::Core ALIAS pickle_core)

# installation (optional)
install(TARGETS pickle_core EXPORT PickleEngineTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(DIRECTORY include/ DESTINATION include)
