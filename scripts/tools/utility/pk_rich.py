import sys
from pathlib import Path

SYSTEM = sys.platform

COLOR = {
  "path":"#B348B8",
  "file" : "#C977BC",
  "url": "#7358E8",
  "module": "#CD9600",
  "error": "#C93535",
  "warn" : "#B3BD48",
  "success": "#2E9856",
  "command": "#4348D5"
}

def rich_file(child:str):
  return f"[{COLOR["file"]}]{child}[/{COLOR["file"]}]"

def rich_path(path: Path, end = ""):
  slash = "/" if "win" not in SYSTEM else "\\"
  return f"[{COLOR["path"]}]{path.parent}{slash}[/{COLOR["path"]}]" \
    f"[bold {COLOR["file"]}]{path.name}[/bold {COLOR["file"]}]{end}"

def rich_url(child:str):
  return f"[{COLOR["url"]}]{child}[/{COLOR["url"]}]"

def rich_module(child:str):
  return f"[{COLOR["module"]}]{child}[/{COLOR["module"]}]"

def rich_error(child:str):
  return f"[{COLOR["error"]}]{child}[/{COLOR["error"]}]"

def rich_warn(child:str):
  return f"[{COLOR["warn"]}]{child}[/{COLOR["warn"]}]"

def rich_success(child:str):
  return f"[{COLOR["success"]}]{child}[/{COLOR["success"]}]"

def rich_command(child:str):
  return f"[{COLOR["command"]}]{child}[/{COLOR["command"]}]"

def bold(child:str):
  return f"[bold]{child}[/bold]"