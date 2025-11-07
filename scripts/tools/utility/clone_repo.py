import subprocess
from pathlib import Path
from rich import print

from tools.utility.run_commands import run_command


def clone_repo(url:str, destination: Path, branch:str = "main"):
  cmd = f"git clone -b {branch} {url} {str(destination)}"
  print(f"Cloning [blue]{url}[/blue] to [blue]{destination}[/blue]...\n")
  run_command(cmd)
