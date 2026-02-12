from pathlib import Path
from rich import print
from .pk_rich import rich_path, rich_success
from .snake_case import to_snake_case
from .const import BASE_DIR

def edit_cmake_module(module_dir: Path, name_module:str, 
    dependencies:dict = {
      "libs": ["SDL3::SDL3"],
      "modules":{
        "Pickle::Module":["window_render"]
    }}
):
  cmake_path = module_dir / "CMakeLists.txt"
  with cmake_path.open("w", encoding="utf8" ) as f:
      f.write ("cmake_minimum_required(VERSION 3.19)\n"+
f'set(MODULE_NAME "{name_module}")'+
"""
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
PUBLIC"""+f"""
    #libs
    {"""
    """.join(dependencies["libs"])}
    #modules
    {"""
    """.join(f'{prefix}::{name}'
    for prefix, modules in dependencies['modules'].items()
    for name in modules)
    }
"""+"""
)

target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)

# alias
add_library(Pickle::Module::${MODULE_NAME} ALIAS ${TARGET_NAME})

# install
install(TARGETS ${TARGET_NAME} EXPORT PickleEngineTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include/pickle/modules/${MODULE_NAME})"""
          )
  
  print(f"{rich_path(cmake_path)} {rich_success("was written successfully")}")


def edit_cmake_project(
  project_path:Path,
  project_name:str,
  dependencies:dict = {
    "libs": [
      "SDL3::SDL3",
      "SDL3_image::SDL3_image",
      "entt"
    ],
    "modules": {
      "Pickle::Module": [
        "window_render",
        "app_loop",
        "assets_loader",
        "easy_drawing",
        "keyboard_manager",
        "ecs_sprite",
        "rgb_pallet"
      ]
    }
  }
):
   project_name = to_snake_case(project_name)
   cmake_path = project_path / "CMakeLists.txt"
   with cmake_path.open("w", encoding="utf8" ) as f:
      f.write (f"""

cmake_minimum_required(VERSION 3.19)
project({project_name} VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Options
option(PROJET_BUILD_TESTS "Build tests" OFF)
option(PROJET_BUILD_EXAMPLES "Build examples" OFF)
option(PROJET_INSTALL "Generate install rules" ON)

# Variables
get_filename_component(PICKLE_ROOT_DIR "{BASE_DIR}" ABSOLUTE)
get_filename_component(PROJECT_ROOT_DIR "${"{CMAKE_SOURCE_DIR}"}" ABSOLUTE)

message(STATUS "Pickle root dir = ${"{PROJECT_ROOT_DIR}"}")

set(PROJECT_EXECUTABLE_NAME "{project_name}")

# Functions PICKLEENGINE/cmake/functions.cmake
list(APPEND CMAKE_MODULE_PATH "${"{PICKLE_ROOT_DIR}"}/cmake")
include(functions)

# Policies / build type sensible
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type" FORCE)
endif()

# Make sure out-of-source builds are used
if("${"{PROJECT_ROOT_DIR}"}" STREQUAL "${"{CMAKE_BINARY_DIR}"}")
  message(WARNING "In-source build detected. It's recommended to use an out-of-source build.")
endif()

# LIBS vvv --------------------------------------------------------------------


# SDL3 
list(APPEND CMAKE_PREFIX_PATH "${"{PICKLE_ROOT_DIR}"}/libs/SDL3/install")
find_package(SDL3 REQUIRED CONFIG)

# SDL3_image
list(APPEND CMAKE_PREFIX_PATH "${"{PICKLE_ROOT_DIR}"}/libs/SDL3_Image/install")
find_package(SDL3_image REQUIRED CONFIG)

# SDL3_ttf
list(APPEND CMAKE_PREFIX_PATH "${"{PICKLE_ROOT_DIR}"}/libs/SDL3_ttf/install")
find_package(SDL3_ttf REQUIRED CONFIG)

# EnTT (header-only)
add_library(entt INTERFACE)
target_include_directories(entt INTERFACE
    ${"{PICKLE_ROOT_DIR}"}/libs/EnTT/src
)

# LIBS ^^^ --------------------------------------------------------------------


add_subdirectory(
  ${"{PICKLE_ROOT_DIR}"}/modules
  ${"{CMAKE_BINARY_DIR}"}/modules 
)
  

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${"{CMAKE_CURRENT_BINARY_DIR}"}/PickleEngineConfigVersion.cmake"
  VERSION ${"{PROJECT_VERSION}"}
  COMPATIBILITY AnyNewerVersion
)

add_auto_executable(
    ${"{PROJECT_EXECUTABLE_NAME}"}
    "${"{PROJECT_ROOT_DIR}"}/src"
    "${"{PROJECT_ROOT_DIR}"}/header"
)

target_include_directories(${"{PROJECT_EXECUTABLE_NAME}"} PRIVATE
    ${"{PROJECT_ROOT_DIR}"}/header
    ${"{PICKLE_ROOT_DIR}"}/modules
)

target_link_libraries(${"{PROJECT_EXECUTABLE_NAME}"} PRIVATE
  # link modules you want statically if needed:
  {"""
  """.join(f'{prefix}::{name}'
          for prefix, modules in dependencies['modules'].items()
          for name in modules)}

  #link libs
  {"""
   """.join(dependencies["libs"])
     
  }
)

#copy ressoures dir
add_custom_command(
    TARGET ${"{PROJECT_EXECUTABLE_NAME}"} POST_BUILD
    COMMAND ${"{CMAKE_COMMAND}"} -E copy_directory
            ${"{PROJECT_ROOT_DIR}"}/assets
            $<TARGET_FILE_DIR:${"{PROJECT_EXECUTABLE_NAME}"}>/assets
)

set_target_properties(${"{PROJECT_EXECUTABLE_NAME}"} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${"{CMAKE_BINARY_DIR}"}/bin")
"""
      )
      print(f"{rich_path(cmake_path)} {rich_success("was written successfully")}")

