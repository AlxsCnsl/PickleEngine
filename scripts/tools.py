import sys
from tools.new_modules import NewModule
from tools.cmake_update_module import CmakeUpdateModule
from tools.install_lib import LibsInstaller
from tools.utility.const import  BASE_DIR, LIBS_DIR_NAME, SYSTEM

scripts = [
    {
        "name":"cmku_module", #CMake Update Module
        "call": lambda:CmakeUpdateModule.call(sys.argv)
    },
    {
        "name":"install_lib", #install lib
        "call": lambda:LibsInstaller.call(sys.argv)
    },
    {
        "name":"new_module", #Create new module
        "call": lambda:NewModule.call(sys.argv)
    },
]


def get_all_doc():
    docs = ""
    for script in scripts:
        docs += (f"""\n > {script["name"]}""")
    return docs


def fast_doc ():
    return f"""---Here are the available scripts---:
{SYSTEM}
{get_all_doc()}\n
------"""


def launch_def():
    for script in scripts : 
        if script["name"] == sys.argv[1]:
            return script["call"]()
    print(f"{sys.argv[1]} does not exist")
    return print(fast_doc())
    

def main():
    if len(sys.argv) == 1:
        return print(fast_doc())
    launch_def()
    

if __name__ == "__main__":
    main()