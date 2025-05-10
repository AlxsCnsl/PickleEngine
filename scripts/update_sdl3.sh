#!/bin/bash

set -euo pipefail

# Configuration
SDL_REPO="https://github.com/libsdl-org/SDL.git"
TEMP_DIR="$(mktemp -d)"
INSTALL_DIR="$(pwd)/libs/SDL3"
INCLUDE_DIR="$INSTALL_DIR/include/SDL3"
LIB_DIR="$INSTALL_DIR/lib"

echo "[SDL3] 📥 Clonage de SDL "
git clone "$SDL_REPO" "$TEMP_DIR/SDL"

echo "[SDL3] 🛠️ Configuration de la build..."
cmake -S "$TEMP_DIR/SDL" -B "$TEMP_DIR/SDL/build" \
    -DSDL_STATIC=ON \
    -DSDL_SHARED=OFF \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    -DCMAKE_INSTALL_PREFIX="$TEMP_DIR/SDL/install" \
    -DCMAKE_BUILD_TYPE=Release

echo "[SDL3] 🔨 Compilation..."
cmake --build "$TEMP_DIR/SDL/build" --target install -j"$(nproc)"

echo "[SDL3] 📦 Installation des fichiers..."
mkdir -p "$INCLUDE_DIR"
mkdir -p "$LIB_DIR"

cp -r "$TEMP_DIR/SDL/include/SDL3/"* "$INCLUDE_DIR/"
cp "$TEMP_DIR/SDL/install/lib/"*.a "$LIB_DIR/"

echo "[SDL3] ✅ SDL3 statique installé dans : $INSTALL_DIR"

# Nettoyage
rm -rf "$TEMP_DIR"
