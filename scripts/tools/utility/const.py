from pathlib import Path
import sys
import distro

from tools.utility.dict import openJsonFile

#ENGINE____________________________________________________
BASE_DIR = Path(__file__).parents[3]
LIBS_DIR_NAME = "libs"

#modules
CONF_MOD_NAME = "meta.json"

#launcher
LAUNCHER_DIR_NAME = "engine_launcher"
LAUNCHER_DIR_PATH = BASE_DIR / LAUNCHER_DIR_NAME

#conf
CONF_ENGINE_FILE_NAME = "conf.json"
CONF_ENGINE_FILE_PATH = BASE_DIR / CONF_ENGINE_FILE_NAME
CONF_ENGINE = openJsonFile(CONF_ENGINE_FILE_PATH)


#SYSTEM____________________________________________________
SYSTEM = sys.platform
DISTRO = distro.id() #if linux