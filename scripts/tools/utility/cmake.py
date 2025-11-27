from pathlib import Path
from rich import print
from .pk_rich import rich_path, rich_success

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
   cmake_path = project_path / "CMakeLists.txt"
   with cmake_path.open("w", encoding="utf8" ) as f:
      f.write (
        "" \
        "add_auto_executable(" \
       f"    {project_name}" \
        "    \"${CMAKE_CURRENT_SOURCE_DIR}/src\"" \
        "    \"${CMAKE_CURRENT_SOURCE_DIR}/header\"" \
        ")" \
        "" \
        "include_directories(" \
        "    ${CMAKE_SOURCE_DIR}/header" \
        "    ${CMAKE_SOURCE_DIR}/../modules" \
        "    ${CMAKE_SOURCE_DIR}/../libs/SDL3/install/include" \
        ")" \
        "" \
       f"target_link_libraries({project_name}PRIVATE" \
        "  # link modules you want statically if needed:" \
       f"{"\n".join(f'{prefix}::{name}'
          for prefix, modules in dependencies['modules'].items()
          for name in modules)}"
        "" \
        "  #link libs" \
        f"{"\n".join(dependencies["libs"])}"
        ")" \
        "" \
        "# copy ressources dir" \
        "add_custom_command(" \
       f"    TARGET {project_name} POST_BUILD" \
        "    COMMAND ${CMAKE_COMMAND} -E copy_directory" \
        "            ${CMAKE_CURRENT_SOURCE_DIR}/assets" \
       f"            $<TARGET_FILE_DIR:{project_name}>/assets" \
        ")" \
        "" \
        f"set_target_properties({project_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY \"${"{CMAKE_BINARY_DIR}"}/bin\")" \
        ""
      )
      print(f"{rich_path(cmake_path)} {rich_success("was written successfully")}")