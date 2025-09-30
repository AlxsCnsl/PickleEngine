import json
from pathlib import Path

BASE_DIR = Path(__file__).parents[2]
MODULES_DIR = BASE_DIR / "modules"


def module_exists(module_dir: Path, name_module: str):
    if module_dir.exists():
        print(f"{name_module} already exists in {module_dir}")
        return True
    else:
        print(f"----creation of {name_module}----")
        return False
        
# CONFIG JSON ___________________________________________________________________________
    
def make_config_json(module_dir: Path, name_module: str): 
        data = {
            "name": name_module,
            "description": f"This is a module: {name_module}.",
            "dependencies": {
                "libs": [],
                "modules": ["SDL3"]
            },
            "functions": []
        }
        config_path = module_dir / "meta.json"
        with config_path.open("w", encoding="utf-8") as f:
            json.dump(data, f, indent=2)
        print("meta.json was created")


# CMAKE _________________________________________________________________________________

def make_cmakelists(module_dir: Path, name_module: str):
    cmake_path = module_dir / "CMakeLists.txt"
    with cmake_path.open("w", encoding="utf8" ) as f:
        f.write("cmake_minimum_required(VERSION 3.19)\n"+
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
install(DIRECTORY include/ DESTINATION include/pickle/modules/${MODULE_NAME})""")
    print("CMakeLists.txt was created")



# INCLUDE _______________________________________________________________________________

def make_include(module_dir: Path, name_module: str):
    dir_path = module_dir / "include"
    header_file = f"{name_module}.hpp"
    dir_path.mkdir(parents=True, exist_ok=True)
    header_path = dir_path /header_file
    with header_path.open("w", encoding="utf8" ) as f:
        f.write(f"""#include <SDL3/SDL3.h.hpp>
// other module""")
    print(f"{header_file} was created")



# SOURCE ________________________________________________________________________________
def make_src(module_dir: Path, name_module: str):
    dir_path = module_dir / "src"
    source_file = f"{name_module}.cpp"
    dir_path.mkdir(parents=True, exist_ok=True)
    header_path = dir_path /source_file
    with header_path.open("w", encoding="utf8" ) as f:
        f.write(f"#include <{name_module}/{name_module}.hpp>")
    print(f"{source_file} was created")



# MODULE ________________________________________________________________________________

def new_module(name_module: str):
    if MODULES_DIR.exists():
        module_dir = MODULES_DIR / name_module
        if(module_exists(module_dir, name_module)):return
        module_dir.mkdir(parents=True, exist_ok=True)#/module
        make_config_json(module_dir, name_module)#/module/config.json
        make_cmakelists(module_dir, name_module)#/module/CmakeLists.json
        make_include(module_dir, name_module)#/module/include/module.hpp
        make_src(module_dir, name_module)#/module/src/module.hpp

        print(f"Module {name_module} created in {module_dir}")
    else:
        print(f"Modules folder {MODULES_DIR} not found")
