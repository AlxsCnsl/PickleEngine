from .ScriptClass import Script
from rich import print
from .utility.run_commands import run_commands
from .utility.const import SYSTEM, PROJECTS_DIR_PATH, BASE_DIR
from .utility.pk_rich import rich_error
from .utility.dict import getDictValue, openJsonFile
import os

class ProjectCompliler(Script):
  name = "project_compiler"

  def _linux_compile(type:str, project:str):
    cmd : list[str] = []
    project_dir = BASE_DIR / "projects" /project
    build_dir = project_dir / "build" / f"build-{type}"
    cmd.append(f"mkdir -p {build_dir}")
    cmd.append(
      f'cmake -S . -B {build_dir} '
      f'-G Ninja -DCMAKE_BUILD_TYPE={type.capitalize()} '
      f'-DPROJECT_DIR_NAME="{project}" '
      f'-DPROJECT_EXECUTABLE_NAME="{project}" '
    )
    cmd.append(f"cmake --build {build_dir}")
    run_commands(cmd, project_dir)


  def _windows_compile(type:str, project:str):
    cmd : list[str] = []
    project_dir = BASE_DIR / "projects" /project
    build_dir = project_dir / "build" / f"build-{type}"
    cmd.append(f'if not exist "{build_dir}" mkdir "{build_dir}"')
    cmd.append(
        f'cmake -S . -B "{build_dir}"'
        f'-G Ninja -DCMAKE_BUILD_TYPE={type.capitalize()} '
        f'-DPROJECT_DIR_NAME="{project}"'
        f'-DPROJECT_EXECUTABLE_NAME="{project}"'
    )
    cmd.append(f'cmake --build "{build_dir}"')
    run_commands(cmd, BASE_DIR)


  def _isValidProject(project_name:str):
    project_path = PROJECTS_DIR_PATH / project_name
    if not os.path.exists(project_path):
      print ("Le projet n'existe pas");return False
    if not os.path.isdir(project_path):
      print ("le projet n'est pas un dossier");return False
    return True
    
    
  def argvIsValid(argv:list[str]):
    size = len(argv)
    args = ["debug","release"]
    if size <= 3:
      ProjectCompliler.doc()
      return False
    if argv[2] not in args:
      return False
    if not ProjectCompliler._isValidProject(argv[3]):
      return False
    return True
  

  def call(argv:list[str]):
    if not ProjectCompliler.argvIsValid(argv):
      print("erreur")
      return
    if SYSTEM.startswith("win"):
      return ProjectCompliler._windows_compile(argv[2], argv[3])
    return ProjectCompliler._linux_compile(argv[2], argv[3])

  #DOC ______________________________________________________________
  def doc():
    print(f"""--<{ProjectCompliler.name} >-- doc -- 

"{ProjectCompliler.name}" allows you to compile a project

>basic commande :

    #compile curent project for debug
    {ProjectCompliler.name} debug name_project

    ##compile curent project for release
    {ProjectCompliler.name} release name_project

""")