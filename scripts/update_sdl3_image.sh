#!/bin/bash

set -euo pipefail

# Configuration
SDL_IMAGE_REPO="https://github.com/libsdl-org/SDL_image.git"
TEMP_DIR="$(mktemp -d)"
INSTALL_DIR="$(pwd)/libs/SDL3_image"
INCLUDE_DIR="$INSTALL_DIR/include/SDL3_image"
LIB_DIR="$INSTALL_DIR/lib"

# Chemin vers SDL3 déjà installé
SDL3_INSTALL_DIR="$(pwd)/libs/SDL3"

echo "[SDL_image] Clonage de SDL_image"
git clone --recurse-submodules $SDL_IMAGE_REPO "$TEMP_DIR/SDL_image"

echo "[SDL_image] Configuration de la build..."
cmake -S "$TEMP_DIR/SDL_image" -B "$TEMP_DIR/SDL_image/build" \
    -DSDLIMAGE_TESTS=OFF \
    -DSDLIMAGE_VENDORED=ON \
    -DSDLIMAGE_BACKEND_IMAGEIO=OFF \
    -DSDLIMAGE_AVIF=OFF \
    -DSDLIMAGE_JXL=OFF \
    -DSDLIMAGE_WEBP=OFF \
    -DSDL_STATIC=ON \
    -DSDL_SHARED=OFF \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    -DCMAKE_INSTALL_PREFIX="$TEMP_DIR/SDL_image/install" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_PREFIX_PATH="$SDL3_INSTALL_DIR"

echo "[SDL_image] Compilation..."
cmake --build "$TEMP_DIR/SDL_image/build" --target install -j"$(nproc)"

echo "[SDL_image] Installation des fichiers..."
mkdir -p "$INCLUDE_DIR"
mkdir -p "$LIB_DIR"

cp -r "$TEMP_DIR/SDL_image/include/SDL3_image/"* "$INCLUDE_DIR/"
cp "$TEMP_DIR/SDL_image/install/lib/"*.a "$LIB_DIR/"

echo "$TEMP_DIR/SDL_image/include/SDL3_image/"* "$INCLUDE_DIR/"
echo "$TEMP_DIR/SDL_image/install/lib/"*.a "$LIB_DIR/"
echo "[SDL_image] SDL_image statique installé dans : $INSTALL_DIR"

# Nettoyage
rm -rf "$TEMP_DIR"

