import json
from pathlib import Path
from rich import print
from tools.utility.cmake import edit_cmake_project

from .ScriptClass import Script
from .utility.pk_rich import rich_error, rich_path, rich_file, bold, rich_command, rich_module
from .utility.const import PROJECTS_DIR_PATH

class NewProject(Script):
    name = "new_project"

    @staticmethod
    def _project_exists(project_dir: Path, name_project: str):
        if project_dir.exists():
            print(f"{rich_path(name_project)} already exists in {rich_path(project_dir)}")
            return True
        else:
            print(bold(f"Creating project {rich_module(name_project)}"))
            return False

    # CONFIG JSON _______________________________________________________________________
    @staticmethod
    def _make_config_json(project_dir: Path, name_project: str):
        data = {
        "name" : name_project,
        "description" : "...test...",
        "owner" : "Pickle_Corp",
        "dependencies": {
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
        }}}
        config_path = project_dir / "conf.json"
        with config_path.open("w", encoding="utf-8") as f:
            json.dump(data, f, indent=2)
        print(f"{rich_file('conf.json')} was created in {rich_path(project_dir)}")

    # MAIN.CPP _________________________________________________________________________
    @staticmethod
    def _make_main_cpp(project_dir: Path, name_project: str):
        src_dir = project_dir / "src"
        src_dir.mkdir(parents=True, exist_ok=True)
        main_cpp_path = src_dir / "main.cpp"
        main_cpp_content = \
          "#include <iostream>"\
          ""\
          "int main() {"\
         f"  std::cout << \"Hello, \" + {name_project} + \"!\" << std::endl;"\
          "  return 0;"\
          "}"
        with main_cpp_path.open("w", encoding="utf-8") as f:
            f.write(main_cpp_content)
        print(f"{rich_file('main.cpp')} was created in {rich_path(src_dir)}")

    # CREATE PROJECT ___________________________________________________________________
    @staticmethod
    def argvIsValid(argv: list[str]):
        if len(argv) <= 2:
            NewProject.doc()
            return False
        return True

    @staticmethod
    def call(argv: list[str]):
        if not NewProject.argvIsValid(argv):
            return print(rich_error(f"Stop of {rich_command(NewProject.name)}."))

        name_project = argv[2]
        if PROJECTS_DIR_PATH.exists():
            project_dir = PROJECTS_DIR_PATH / name_project
            if NewProject._project_exists(project_dir, name_project):
                return
            project_dir.mkdir(parents=True, exist_ok=True)
            # Création des sous-dossiers
            for folder in ["assets", "header", "src"]:
                (project_dir / folder).mkdir(exist_ok=True)
            # Création des fichiers
            NewProject._make_config_json(project_dir, name_project)
            edit_cmake_project(project_dir, name_project)
            NewProject._make_main_cpp(project_dir, name_project)

            print(f"Project {bold(name_project)} created in {rich_path(project_dir)}")
        else:
            print(rich_error(f"Projects folder {rich_path(PROJECTS_DIR_PATH)} not found"))

    @staticmethod
    def doc():
        print(f"""--<{NewProject.name}>-- doc --

"{NewProject.name}" allows you to create a new C++ project

> basic command:
    {NewProject.name} [name of new project]
""")
