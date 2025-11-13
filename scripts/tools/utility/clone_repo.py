from pathlib import Path
from rich import print
from .pk_rich import rich_path, rich_url

from tools.utility.run_commands import run_command


def clone_repo(url:str, destination: Path, branch:str = "main"):
  cmd = f"git clone -b {branch} {url} {str(destination)}"
  print(f"Cloning {rich_url(url)} to {rich_path(destination)}...\n")
  run_command(cmd)
