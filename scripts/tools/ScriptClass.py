import json
from pathlib import Path

class Script:

  name="[script]"

  @staticmethod
  def call(argvs:list[str]):
    print(f"\"call\" undefine")
  
  @staticmethod
  def doc():
    print(f"\"doc\" undefine")
