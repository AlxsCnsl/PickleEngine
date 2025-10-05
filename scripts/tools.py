import sys
from tools.new_modules import new_module

scripts = [
    {
        "name":"new_module", 
        "args":["[module name]"],
    },
    {
        "name":"remake_module",
        "args": ["[moudule name]"],
    }
]

def limit_argc(min, max, name_fun):
    if len(sys.argv)-1 > max:
        print(f"too many arguments for {name_fun}")
        return 0
    elif len(sys.argv)-1 < min:
        print(f"missing one or more arguments for {name_fun}")
        return 0
    return 1

def print_argv_wanted(wanted):
    print(wanted)

def get_all_doc():
    docs = ""
    for script in scripts:
        docs += (f"""\n > {script["name"]}
    args : {script["args"]}""")
    return docs


def doc ():
    return f"""---Here are the available scripts---:
{get_all_doc()}\n
------"""


def main():
    if len(sys.argv) == 1:
        return print(doc())
    match sys.argv[1]:
        case "new_module":
            if (limit_argc(2, 2, "new_module")):
                return new_module(sys.argv[2])
            return print_argv_wanted("new_module")
        case _:
            return print(doc())

if __name__ == "__main__":
    main()