import sys
from tools.new_modules import NewModule
from tools.cmake_update_module import CmakeUpdateModule

scripts = [
    {
        "name":"new_module", 
        "call": lambda:NewModule.call(sys.argv)
    },
    {
        "name":"cmku_module", #CMake Update Module
        "call": lambda:CmakeUpdateModule.call(sys.argv)
    }
]


def get_all_doc():
    docs = ""
    for script in scripts:
        docs += (f"""\n > {script["name"]}""")
    return docs


def fast_doc ():
    return f"""---Here are the available scripts---:
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