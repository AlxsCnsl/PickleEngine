import json
import sys
from pathlib import Path

from .ModuleScriptClass import ModuleScript

BASE_DIR = Path(__file__).parents[2]
MODULES_DIR = BASE_DIR / "modules"


class NewModule(ModuleScript):
    name="new_module"


    @staticmethod
    def _module_exists(module_dir: Path, name_module: str):
        if module_dir.exists():
            print(f"{name_module} already exists in {module_dir}")
            return True
        else:
            print(f"----creation of {name_module}----")
            return False
            

    # CONFIG JSON _______________________________________________________________________
    @staticmethod
    def _make_config_json(module_dir: Path, name_module: str): 
            data = {
                "name": name_module,
                "description": f"This is a module: {name_module}.",
                "alias" : {
                    "namespace":"Pickle",
                    "subnamespace":"Module"
                },
                "dependencies": {
                    "libs": ["SDL3::SDL3"],
                    "modules": {
                    "Pickle::Module":["window_render"]
                    }
                },
                "functions": []
            }
            config_path = module_dir / "meta.json"
            with config_path.open("w", encoding="utf-8") as f:
                json.dump(data, f, indent=2)
            print("meta.json was created")


    # INCLUDE ___________________________________________________________________________
    @staticmethod
    def _make_include(module_dir: Path, name_module: str):
        dir_path = module_dir / "include"
        header_file = f"{name_module}.hpp"
        dir_path.mkdir(parents=True, exist_ok=True)
        header_path = dir_path /header_file
        with header_path.open("w", encoding="utf8" ) as f:
            f.write(f"""#pragma once
#include <SDL3/SDL.h>
// other module""")
        print(f"{header_file} was created")



    # SOURCE ____________________________________________________________________________
    @staticmethod
    def _make_src(module_dir: Path, name_module: str):
        dir_path = module_dir / "src"
        source_file = f"{name_module}.cpp"
        dir_path.mkdir(parents=True, exist_ok=True)
        header_path = dir_path /source_file
        with header_path.open("w", encoding="utf8" ) as f:
            f.write(f"#include <{name_module}/{name_module}.hpp>")
        print(f"{source_file} was created")



    # New MODULE ________________________________________________________________________

    def ArgvIsValid(argv:list[str]):
        size = len(argv)
        if size <= 2:
            NewModule.doc()
            return False
        return True


    @staticmethod
    def call(argv:list[str]):
        if not NewModule.ArgvIsValid(argv):
            return print(f"Stop of \"{NewModule.name}\".")
        
        name_module = argv[2]
        if MODULES_DIR.exists():
            module_dir = MODULES_DIR / name_module
            if(NewModule._module_exists(module_dir, name_module)):return
            module_dir.mkdir(parents=True, exist_ok=True)#/module
            NewModule._make_config_json(module_dir, name_module)#/module/config.json
            NewModule._editCmakeLists(module_dir, name_module)#/module/CmakeLists.json
            NewModule._make_include(module_dir, name_module)#/module/include/module.hpp
            NewModule._make_src(module_dir, name_module)#/module/src/module.hpp

            print(f"Module {name_module} created in {module_dir}")
        else:
            print(f"Modules folder {MODULES_DIR} not found")


    @staticmethod
    def doc():
        print(f"""--<{NewModule.name} >-- doc -- 

"{NewModule.name}" allows you to create a new module

>basic commande : 
    {NewModule.name} [name of new module]
""")