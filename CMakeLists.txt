cmake_minimum_required(VERSION 3.19)
project(PickleEngine VERSION 0.1.0 LANGUAGES CXX)


# Functions .cmake/functions.cmake
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(functions)

# Options
option(PICKLE_BUILD_TESTS "Build tests" OFF)
option(PICKLE_BUILD_EXAMPLES "Build examples" OFF)
option(PICKLE_INSTALL "Generate install rules" ON)
# Variables
set(PROJECT_DIR_NAME "psyduck_field")
set(PROJECT_EXECUTABLE_NAME "psyduck_field")

# Policies / build type sensible
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type" FORCE)
endif()

# Use modern defaults
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Make sure out-of-source builds are used
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(WARNING "In-source build detected. It's recommended to use an out-of-source build.")
endif()

# SDL3 ------------------------------------------------------------------------
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/libs/SDL3/install")
find_package(SDL3 REQUIRED CONFIG)

# SDL3_image ------------------------------------------------------------------
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/libs/SDL3_Image/install")
find_package(SDL3_image REQUIRED CONFIG)

# SDL3_ttf --------------------------------------------------------------------
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/libs/SDL3_ttf/install")
find_package(SDL3_ttf REQUIRED CONFIG)

# EnTT (header-only) ----------------------------------------------------------
add_library(entt INTERFACE)
target_include_directories(entt INTERFACE
    ${CMAKE_SOURCE_DIR}/libs/EnTT/src
)

# Subprojects
#The order is important
add_subdirectory(modules)     # will scan modules/ and add each module (seen modules/CMakeLists.txt)
add_subdirectory(projects/${PROJECT_DIR_NAME})


# Export package config for installing/using PickleEngine via find_package
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/PickleEngineConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)
