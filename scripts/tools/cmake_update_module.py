import json
from pathlib import Path
import json

from .ModuleScriptClass import ModuleScript

BASE_DIR = Path(__file__).parents[2]
MODULES_DIR = BASE_DIR / "modules"


class CmakeUpdateModule(ModuleScript):
    name="cmk_module"


    @staticmethod
    def _moduleExists(module_dir: Path, name_module: str):
        if module_dir.exists():
            print(f"----start of the reissue of \"{name_module}\" module----")
            return True
        else:
            print(f"----\"{name_module}\" module does not exist----")
            return False



    # read JSON _______________________________________________________________________
    @staticmethod
    def _getDependenciesJson(module_dir: Path): 
        path = module_dir / "meta.json"
        if not path.exists():
            print(f"Error: the file {path} does not exist.")
            return None
        if not path.is_file():
            print(f"Error: {path} is not a file.")
            return None
        with path.open("r", encoding="utf-8") as f:
            dependencies = json.load(f)["dependencies"] #add verify for key
            return dependencies
        

    # CMake MODULE ______________________________________________________________________
    def _ArgvIsValid(argv:list[str]):
        size = len(argv)
        if size <= 2:
            CmakeUpdateModule.doc()
            return False
        return True


    @staticmethod
    def call(argv:list[str]):
        if not CmakeUpdateModule._ArgvIsValid(argv):
            return print(f"Stop of \"{CmakeUpdateModule.name}\".")
        
        name_module = argv[2]
        if MODULES_DIR.exists():
            module_dir = MODULES_DIR / name_module
            dependencies = CmakeUpdateModule._getDependenciesJson(module_dir)
            if(not CmakeUpdateModule._moduleExists(module_dir, name_module)):return
            CmakeUpdateModule._editCmakeLists(module_dir, name_module, dependencies)

            print(f"CMakeLsist module {name_module} as update in {module_dir}")
        else:
            print(f"Modules folder {MODULES_DIR} not found")


    @staticmethod
    def doc():
        print(f"""--<{CmakeUpdateModule.name} >-- doc -- 

"{CmakeUpdateModule.name}" allows you to update the CMakeLists of a module

>basic commande : 
    {CmakeUpdateModule.name} [name of module]
""")