from pathlib import Path
import subprocess
from rich import print
from tools.utility.const import BASE_DIR
from .pk_rich import rich_path, rich_command, bold, rich_error


def run_command(cmd: str, cwd: Path = BASE_DIR, strict: bool = True) -> int:
  """
  Runs a command and prints its output.

  strict=True  -> raise RuntimeError on fail  
  strict=False -> return exit code without raising
  """
  print(f"{rich_command(f'{bold('Running:')} {cmd}')} from {rich_path(cwd)}")
  process = subprocess.Popen(
    cmd,
    cwd=str(cwd),
    shell=True,
    stdout=subprocess.PIPE,
    stderr=subprocess.STDOUT,
    text=True,
    encoding="utf-8",
    bufsize=1
  )
  # Read output live
  for line in iter(process.stdout.readline, ""):
    print(f"[dim]{line.strip()}[/dim]")
  exit_code = process.wait()
  if exit_code != 0:
    msg = f"Command failed ({exit_code}): {cmd}"
    if strict:
      raise RuntimeError(msg)
    else:
      print(rich_error(msg))
  return exit_code


def run_commands(commands:list, cwd:Path=BASE_DIR, strict:bool = True ):
  """
  Runs a list of commands.

  WARNING: if you use a command to change directories,
    the next command will still be executed in the 'cwd' directory
    passed as a parameter to this function.

    To avoid this, use 'cd /[target_directory] && command' for commands 
    that need to run in a specific folder.
  """
  without_error = True
  for cmd in commands:
    try:
      if without_error: 
        result = run_command(cmd, cwd, strict=strict)
        if result != 0 and not strict:
          print(rich_error(f"Command returned {result}, continuing..."))
    except RuntimeError as e:
      print(e)
      print(rich_error("Stopping because of an error."))
      without_error = False
      break