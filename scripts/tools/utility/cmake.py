from pathlib import Path

def edit_cmake_module(module_dir: Path, name_module:str, 
    dependencies:dict = {
      "libs": ["SDL3::SDL3"],
      "modules":{
        "Pickle::Module":["window_render"]
      }
}):
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
    Pickle::Core
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
  print("CMakeLists.txt was ready")



def edit_cmake_libs_project():
  pass
