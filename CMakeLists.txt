cmake_minimum_required(VERSION 3.19)
project(PickleEngine VERSION 0.1.0 LANGUAGES CXX)


# Functions .cmake/functions.cmake
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(functions)

# Options
option(PICKLE_BUILD_TESTS "Build tests" OFF)
option(PICKLE_BUILD_EXAMPLES "Build examples" OFF)
option(PICKLE_INSTALL "Generate install rules" ON)

# Policies / build type sensible
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type" FORCE)
endif()

# Use modern defaults
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Make sure out-of-source builds are used
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(WARNING "In-source build detected. It's recommended to use an out-of-source build.")
endif()

# Where to find vendored libs CMake config (SDL3, SDL3_image)
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/libs/SDL3/lib/cmake")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/libs/SDL3_image/lib/cmake")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/libs/entt")

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)
# EnTT est header-only, tu peux juste inclure
add_library(EnTT INTERFACE)
target_include_directories(EnTT INTERFACE "${CMAKE_SOURCE_DIR}/libs/entt/include")


# Subprojects
#The order is important
add_subdirectory(core)
add_subdirectory(libs)
add_subdirectory(modules)     # will scan modules/ and add each module (seen modules/CMakeLists.txt)
add_subdirectory(engine_launcher)

# Export package config for installing/using PickleEngine via find_package
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/PickleEngineConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

# install package config only if requested
#if(PICKLE_INSTALL)
#  install(EXPORT PickleEngineTargets
#          FILE PickleEngineTargets.cmake
#          NAMESPACE Pickle::
#          DESTINATION lib/cmake/PickleEngine)
#endif()
