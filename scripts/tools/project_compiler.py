from .ScriptClass import Script
from rich import print
from .utility.run_commands import run_commands
from .utility.const import SYSTEM, LAUNCHER_DIR_PATH, BASE_DIR
from .utility.pk_rich import rich_error
from .utility.dict import getDictValue, openJsonFile

class ProjectCompliler(Script):
  name = "project_compiler"


  def _linux_compile():
    cmd = [
      "mkdir -p build",
      "cmake -S . -B build -G Ninja",
      "cmake --build build",
    ]
    run_commands(cmd, BASE_DIR)


  def _windows_compile():
      cmd = [
          "if not exist build mkdir build",
          "cmake -S . -B build -G Ninja",
          "cmake --build build",
      ]
      run_commands(cmd, BASE_DIR)


  def argvIsValid(argv:list[str]):
    size = len(argv)
    args = ["--dev"]
    if size <= 2:
      ProjectCompliler.doc()
      return False
    if argv[2] not in args:
      return False
    return True
  

  def call(argvs:list[str]):
    if not ProjectCompliler.argvIsValid(argvs): return
    if SYSTEM.startswith("win"):
      return ProjectCompliler._windows_compile()
    return ProjectCompliler._linux_compile()

  #DOC ______________________________________________________________
  def doc():
    print(f"""--<{ProjectCompliler.name} >-- doc -- 

"{ProjectCompliler.name}" allows you to compile a project

>basic commande :

    #compile curent project
    {ProjectCompliler.name} --dev

""")