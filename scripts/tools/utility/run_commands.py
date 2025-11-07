from pathlib import Path
import subprocess
from rich import print
from tools.utility.const import BASE_DIR


def run_command(cmd: str, cwd: Path = None):
  """
  Runs a command and prints its output if there is any.
  """
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
  while True:
    output = process.stdout.readline()
    if output == "" and process.poll() is not None:
      break
    if output:
      print(f"[dim]{output.strip()}[/dim]", flush=True)
  if process.returncode != 0:
    raise RuntimeError(f"Command failed: {cmd} (exit code {process.returncode})")


def run_commands(commands: list, cwd: Path = BASE_DIR ):
  """
  Runs a list of commands.

  WARNING: if you use a command to change directories,
    the next command will still be executed in the 'cwd' directory
    passed as a parameter to this function.

    To avoid this, use 'cd /[target_directory] && command' for commands 
    that need to run in a specific folder.
  """
  for cmd in commands:
    run_command(cmd, cwd)