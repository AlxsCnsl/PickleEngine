import sys
import shutil
from pathlib import Path
from tools.ScriptClass import Script
from rich import print

from tools.utility.run_commands import run_commands
from tools.utility.clone_repo import clone_repo
from tools.utility.const import  BASE_DIR, LIBS_DIR_NAME, SYSTEM, DISTRO, CONF_ENGINE, CONF_ENGINE_FILE_PATH
from tools.utility.dict import openJsonFile, getDictValue
from tools.utility.pk_rich import rich_error, rich_path, rich_module, rich_warn, rich_success, bold

class LibsInstaller(Script):
  name="install_lib"

  
  # get Lib Instalable 
  def _supportedLibs(supported_libs_path: Path) -> list[str] :
    supported_libs_dict = openJsonFile(supported_libs_path)
    if supported_libs_dict == None:
      return None
    try:
      supported_libs=list(supported_libs_dict.keys())
    except AttributeError:
      print(rich_error(f"The content of {rich_path(supported_libs_path)} is not a valid JSON dictionary."))
      return None
    return supported_libs


  # get lib disposed in conf.json
  def _currentLibs() -> list[str] :
    current_libs_dict = getDictValue(CONF_ENGINE, "curent_librarys", CONF_ENGINE_FILE_PATH)
    if current_libs_dict == None:
      return None
    try :
      current_libs=list(current_libs_dict.keys())
    except AttributeError:
      print(rich_error(f"The content of '{current_libs_dict}' is not a valid JSON dictionary."))
      return None
    return current_libs


  # get "current libs" U "suported libs"  
  def _filterSupportedCurrentLibs(supported:list, current:list):
    filtered_libs = []
    for lib in current:
      if not lib in supported:
        print(rich_error(f"library {rich_module(lib)} is not supported"))
      if lib in supported:
        filtered_libs.append(lib)
    return filtered_libs
    

  #args
  def _argvIsValid(argv:list[str],supported_libs_path: Path) -> bool :
    size = len(argv)
    supported_libs = LibsInstaller._supportedLibs(supported_libs_path)
    current_libs = LibsInstaller._currentLibs()
    if (supported_libs == None or current_libs == None):
      return False
    if size <= 2:
      LibsInstaller.doc()
      return False
    elif not((argv[2] in LibsInstaller._filterSupportedCurrentLibs(supported_libs, current_libs)) or (argv[2] == '@all')):
      print(rich_error(f"no libs called {rich_module(argv[2])} were found in: {rich_path(supported_libs_path)}"))
      LibsInstaller.doc()
      return False    
    return True


  def confirm_delete_exist_dir(lib_name: str, dest: Path) -> bool:
      if dest.exists():
          print(f"A library named {rich_module(lib_name)} is already installed. Do you want to overwrite it?")
          while True:
              user_in = input("[yes(y)/no(n)]: ").strip().lower()
              if user_in in ["y", "yes"]:
                  if dest.is_dir():
                      shutil.rmtree(dest)
                  else:
                      dest.unlink()
                  return True
              elif user_in in ["n", "no"]:
                  return False
              else:
                  print("Please type 'y' or 'n'.")
      return True
  

  def compile_lib(destination, command_line = []):
    if not command_line:
      print(rich_warn("No compile commands provided"))
      return
    run_commands(command_line, cwd=destination)
    print(rich_success("Compilation finished successfully!"))


  def install_dependencies(deps_dict:dict):
    if not deps_dict: return
    if not(DISTRO in deps_dict):
      return print(rich_warn(f"no dependency found for {bold(DISTRO)}"))
    deps_install_cmd = deps_dict[DISTRO]
    run_commands([deps_install_cmd])
    print(rich_success("dependencies install successfully"))


  def _installLib(lib:str, lib_file_destination:Path, version_paternes:dict):
    url = version_paternes["ssh"] if getDictValue(CONF_ENGINE, "github_install", CONF_ENGINE_FILE_PATH)== "ssh" else version_paternes["http"]
    branch = version_paternes["branch"]
    if(not LibsInstaller.confirm_delete_exist_dir(lib, lib_file_destination)):
      return
    print(f"installing {rich_module(lib)} to {rich_path(lib_file_destination)}")
    LibsInstaller.install_dependencies(version_paternes["deps"])
    clone_repo(url, lib_file_destination, branch)
    if version_paternes.get("type") == "compiled":
      commands = []
      if SYSTEM.startswith("win"):
          commands = version_paternes["windows_install"]
      else:
          commands = version_paternes["linux_install"]
      LibsInstaller.compile_lib(lib_file_destination, commands)
    

  def get_curent_verison(lib:str) -> str:
    version = getDictValue(CONF_ENGINE, ["curent_librarys", lib], CONF_ENGINE_FILE_PATH)
    return version
  

  @staticmethod
  def call(argv:list[str]): #======================================================================
    supported_libs_file_name = getDictValue(CONF_ENGINE, "supported_libs_path", CONF_ENGINE_FILE_PATH)
    if supported_libs_file_name is None:
      print(rich_error(f"Stop of {rich_module(LibsInstaller.name)}"))
      return
    #
    supported_libs_path = BASE_DIR / supported_libs_file_name
    if not LibsInstaller._argvIsValid(argv, supported_libs_path ):
      print(rich_error(f"Stop of {rich_module(LibsInstaller.name)}"))
      return
    lib_to_install : str = argv[2]
    all_versions_conf:dict = openJsonFile(supported_libs_path)[lib_to_install]
    lib_dir_name =all_versions_conf["lib_dir_name"]
    lib_version_conf = LibsInstaller.get_curent_verison(lib_to_install)
    curent_version = "0.0.0"
    all_versions = all_versions_conf["versions"]
    #
    if(lib_version_conf == "base"):
      curent_version = all_versions_conf["base_version"]
    else:
      curent_version = lib_version_conf
    #
    lib_file_destination = BASE_DIR / LIBS_DIR_NAME / lib_dir_name
    try:
      LibsInstaller._installLib(lib_to_install, lib_file_destination, all_versions[curent_version])
    except RuntimeError as e:
      print(rich_error(f"{bold('Installation failed:')}\n{e}"))
      sys.exit(1)
    


  @staticmethod
  def doc():
    print(
f"""[bold]-- [purple]{LibsInstaller.name}[/purple] DOC--[/bold]
          
[purple]{LibsInstaller.name}[/purple] allows you to install the static libraries available for the engine

> Info  
  
    You can change the version settings of your libraries in "conf.json" under the key "current_libraries"

> basic commande :

    [bright_black]#install the chosen library[/bright_black]
    {LibsInstaller.name} (name of lib)

    [bright_black]#install all librarys[/bright_black]
    {LibsInstaller.name} @all

[bold]-----END DOC-----[/bold]""")