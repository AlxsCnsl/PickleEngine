#!/bin/bash

set -euo pipefail

# System detection
OS="$(uname -s)"

if [[ "$OS" == "Linux" ]]; then
    echo "Linux system detected, launching the script for Linux..."
    chmod +x scripts/update_sdl3/update_sdl3_linux.sh
    ./scripts/update_sdl3/update_sdl3_linux.sh
elif [[ "$OS" == "CYGWIN"* || "$OS" == "MINGW"* || "$OS" == "MSYS"* ]]; then
    echo "Windows system detected, launching the script for Windows..."
    chmod +x scripts/update_sdl3/update_sdl3_win.sh
    ./scripts/update_sdl3/update_sdl3_win.sh
else
    echo "Unknown system: $OS. No action taken."
    exit 1
fi
