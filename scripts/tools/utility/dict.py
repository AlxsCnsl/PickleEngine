import json
from pathlib import Path
from rich import print


def openJsonFile(path:Path):
  """
  Opens a JSON file and converts it into a dict type.
  Handles errors if:
    - the file is missing,
    - the path is not a file,
    - the JSON could not be decoded,
    - or other errors.
  """
  if not path.exists():
    print(f"[bold red]file \"{path}\" not found [/bold red]")
    return None
  if not path.is_file():
    print(f"[bold red] \"{path}\" is not file [/bold red]")
    return None
  try:
    with path.open('r', encoding="utf-8") as f:
      data = json.load(f)
  except json.JSONDecodeError as e:
    print(f"[bold red]JSON decoding error in \"{path}\": {e}[/bold red]")
    return None
  except Exception as e:
    print(f"[bold red]Error while reading the file \"{path}\": {e}[/bold red]")
    return None
  return data


def getDictValue(data_dict:dict, keys:str|list[str], json_path:Path=None):
  """
  Returns the value of the requested key from the dictionary.
  If the key does not exist, an error is printed and None is returned.
  The optional 'json_path' parameter is used only to facilitate debugging
  if the key is not found.
  """
  if type(keys) == str:
    keys = [keys]
  if data_dict == None:
    print(f"[bold red] python dict '{data_dict}' is missing. [bold red]")
    return None
  current_data = data_dict
  for key in keys:
    if not isinstance(current_data, dict):
      print(f"[bold red]Expected a dict at '{key}', but got {type(current_data).__name__}.[/bold red]")
      return None
    try:
      current_data = current_data[key]
    except KeyError:
      if json_path:
        print(f"[bold red]The key '{key}' is missing from \"{json_path}\".[bold red]")
        return None
      print (f"[bold red]The key '{key}' is missing on {data_dict}. [bold red]")
      return None
  return current_data