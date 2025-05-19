#!/bin/bash

if ! command -v vcpkg &> /dev/null; then
    echo "Erreur : vcpkg n'est pas installé. Veuillez l'installer avant de lancer ce script."
    exit 1
fi

if [[ -z "$VCPKG_ROOT" ]]; then
    echo "Erreur : La variable d'environnement VCPKG_ROOT n'est pas définie."
    exit 1
fi

# 🔍 Détection de l'OS
OS=$(uname -s)

if [[ "$OS" == "Linux" ]]; then
    TRIPLET="x64-linux"
elif [[ "$OS" == "Darwin" ]]; then
    TRIPLET="x64-osx-static"
else
    echo "⚠️ Système non supporté !"
    exit 1
fi

echo "🛠️ Installation des dépendances via vcpkg pour $OS ($TRIPLET)..."

# 📦 Installer les bibliothèques en mode statique
vcpkg install sdl3 sdl3-image --triplet=$TRIPLET

# 📂 Configurer et compiler le projet
mkdir -p build
cd build

cmake .. \
  -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake \
  -DVCPKG_TARGET_TRIPLET=$TRIPLET


cmake --build .

echo "✅ Build terminé !"
