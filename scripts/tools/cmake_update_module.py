import json
from pathlib import Path
import json


from rich import print
from .utility.cmake import edit_cmake_module
from .utility.dict import openJsonFile, getDictValue
from .utility.const import CONF_MOD_NAME
from .utility.pk_rich import rich_path, rich_error, rich_success, rich_module, bold

BASE_DIR = Path(__file__).parents[2]
MODULES_DIR = BASE_DIR / "modules"


class CmakeUpdateModule():
  name="cmk_module"


  @staticmethod
  def _moduleExists(module_dir: Path, name_module: str):
    if module_dir.exists():
      print(f"start of the reissue of {rich_module(bold(name_module))} module")
      return True
    else:
      print(rich_error(f"{rich_module(bold(name_module))} module does not exist"))
      return False


  # read JSON _________________________________________________________________________
  @staticmethod
  def _getDependencies(module_dir: Path):
    deps_path = module_dir / CONF_MOD_NAME
    conf = openJsonFile(deps_path)
    if not conf:
      return
    deps = getDictValue(conf,"dependencies", module_dir)
    return deps 
      

  # CMake MODULE ______________________________________________________________________
  @staticmethod
  def _ArgvIsValid(argv:list[str]):
    size = len(argv)
    if size <= 2:
      CmakeUpdateModule.doc()
      return False
    return True


  # Call_______________________________________________________________________________
  @staticmethod
  def call(argv:list[str]):
    if not CmakeUpdateModule._ArgvIsValid(argv):
      return print(rich_error([f"ERROR of {CmakeUpdateModule.name}"]))
    module_name = argv[2]
    if MODULES_DIR.exists():
      module_dir = MODULES_DIR / module_name
      dependencies = CmakeUpdateModule._getDependencies(module_dir)
      if(not CmakeUpdateModule._moduleExists(module_dir, module_name)):
        return
      edit_cmake_module(module_dir, module_name, dependencies)
      print(rich_success(f"CMakeLsist module {rich_module(module_name)} as update in {rich_path(module_dir)}"))
    else:
      print(rich_error(f"Modules folder {rich_path(MODULES_DIR)} not found"))


  @staticmethod
  def doc():
    print(f"""--<{CmakeUpdateModule.name} >-- doc -- 

"{CmakeUpdateModule.name}" allows you to update the CMakeLists of a module

>basic commande : 
  {CmakeUpdateModule.name} [name of module]
""")