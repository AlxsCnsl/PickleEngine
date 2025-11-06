import json
import sys
import subprocess
import shutil
from pathlib import Path
from .ScriptClass import Script
from rich import print
import distro

BASE_DIR = Path(__file__).parents[2]
LIBS_DIR_NAME = "libs"

class LibsInstaller(Script):
  name="install_lib"


  #Open Json
  def _openJsonFile(path:Path):
    if not path.exists():
      print(f"file \"{path}\" not found")
      return None
    if not path.is_file():
      print(f" \"{path}\" is not file")
      return None
    try:
      with path.open('r', encoding="utf-8") as f:
        data = json.load(f)
    except json.JSONDecodeError as e:
      print(f"JSON decoding error in \"{path}\": {e}")
      return None
    except Exception as e:
      print(f"Error while reading the file \"{path}\": {e}")
      return None
    return data


  # Get value in conf.json root engine
  def _getConfValueOf(key):
    conf_file_name = "conf.json"
    conf_file_path = BASE_DIR / conf_file_name
    config = LibsInstaller._openJsonFile(conf_file_path)
    if config == None:
      return None
    try:
      value = config[key]
    except KeyError:
      print(f"The key '{key}' is missing from \"{conf_file_path}\".")
      return None
    return value
  

  # get Lib Instalable 
  def _supportedLibs(supported_libs_path: Path) -> list[str] :
    supported_libs_dict = LibsInstaller._openJsonFile(supported_libs_path)
    if supported_libs_dict == None:
      return None
    try:
      supported_libs=list(supported_libs_dict.keys())
    except AttributeError:
      print(f"The content of '{supported_libs_path}' is not a valid JSON dictionary.")
      return None
    return supported_libs


  # get lib disposed in conf.json
  def _currentLibs() -> list[str] :
    current_libs_dict = LibsInstaller._getConfValueOf("curent_librarys")
    if current_libs_dict == None:
      return None
    try :
      current_libs=list(current_libs_dict.keys())
    except AttributeError:
      print(f"The content of '{current_libs_dict}' is not a valid JSON dictionary.")
      return None
    return current_libs


  # get "current libs" U "suported libs"  
  def _filterSupportedCurrentLibs(supported:list, current:list):
    filtered_libs = []
    for lib in current:
      if not lib in supported:
        print(f"library \"{lib}\" is not supported")
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
      print(f"no libs called \"{argv[2]}\" were found in: \"{supported_libs_path}\"")
      LibsInstaller.doc()
      return False    
    return True


  def confirm_delete_exist_dir(lib_name: str, dest: Path) -> bool:
      if dest.exists():
          print(f"A library named [blue]{lib_name}[/blue] is already installed. Do you want to overwrite it?")
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
  

  def clone_repo(url, destination, branch):
    print(f"Cloning [blue]{url}[/blue] to [blue]{destination}[/blue]...\n")
    process = subprocess.Popen(
        ["git", "clone", "-b", branch, url, str(destination)],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        bufsize=1,
        encoding="utf-8"
    )
    for line in process.stdout:
        print(f"[dim]{line.strip()}[/dim]")
    process.wait()
    if process.returncode == 0:
        print("[bold green]Clone completed successfully![/bold green]")
    else:
        print(f"[bold red]Clone failed (exit code {process.returncode})[/bold red]")


  def run_commands(commands: list, cwd: Path = None):
    for cmd in commands:
      print(f"[bold blue]Running:[/bold blue] {cmd}")
      process = subprocess.Popen(
        cmd,
        cwd=str(cwd) if cwd else None,
        shell=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        bufsize=1,
        encoding="utf-8"
      )
      print(process)
      while True:
        output = process.stdout.readline()
        if output == "" and process.poll() is not None:
          break
        if output:
          print(f"[dim]{output.strip()}[/dim]", flush=True)
      if process.returncode != 0:
        raise RuntimeError(f"Command failed: {cmd} (exit code {process.returncode})")


  def compile_lib(destination, command_line = []):
    if not command_line:
      print("[yellow]No compile commands provided.[/yellow]")
      return
    LibsInstaller.run_commands(command_line, cwd=destination)
    print("[bold green] Compilation finished successfully![/bold green]")


  def install_dependencies(deps_dict:dict):
    if not deps_dict: return
    dist_name = distro.id()
    if not(dist_name in deps_dict):
      return print(f"[yellow]no dependency found for {dist_name}[/yellow]")
    deps_install_cmd = deps_dict[dist_name]
    LibsInstaller.run_commands([deps_install_cmd])
    print("[bold green] dependencies install successfully [/bold green] ")

  def _installLib(lib:str, lib_file_destination:Path, version_paternes:dict):
    url = version_paternes["ssh"] if LibsInstaller._getConfValueOf("github_install") == "ssh" else version_paternes["http"]
    branch = version_paternes["branch"]
    if(not LibsInstaller.confirm_delete_exist_dir(lib, lib_file_destination)):
      return
    print(f"installing [blue]{lib}[/blue] to [blue]{lib_file_destination}[/blue]")
    LibsInstaller.install_dependencies(version_paternes["deps"])
    LibsInstaller.clone_repo(url, lib_file_destination,branch)
    if version_paternes.get("type") == "compiled":
      if sys.platform.startswith("win"):
          commands = version_paternes.get("windows_install", [])
      else:
          commands = version_paternes.get("linux_install", [])
    LibsInstaller.compile_lib(lib_file_destination, commands)



  def get_curent_verison(lib:str) -> str:
    version = LibsInstaller._getConfValueOf("curent_librarys")[lib]
    return version
  

  @staticmethod
  def call(argv:list[str]): #======================================================================
    supported_libs_file_name = LibsInstaller._getConfValueOf("supported_libs_path")
    if supported_libs_file_name is None:
      print(f"Stop of [purple]{LibsInstaller.name}[/purple]")
      return
    #
    supported_libs_path = BASE_DIR / supported_libs_file_name
    if not LibsInstaller._argvIsValid(argv, supported_libs_path ):
      print(f"Stop of [purple]{LibsInstaller.name}[purple]")
      return
    #
    lib_to_install : str = argv[2]
    all_versions_conf:dict = LibsInstaller._openJsonFile(supported_libs_path)[lib_to_install]
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
      print(f"[bold red] Installation failed:[/bold red]\n{e}")
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