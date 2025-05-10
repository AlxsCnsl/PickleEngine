#!/bin/bash

module="$1"

if [ -z "$module" ]; then
    echo "Erreur : aucun chemin de module fourni."
    echo "Usage : ./get_libs_no_deps.sh /chemin/vers/le/module"
    exit 1
fi

meta_file="${module}/meta.json"

if [ ! -f "$meta_file" ]; then
    echo "Erreur : fichier ${meta_file} introuvable."
    exit 1
fi

# Extraction des bibliothèques depuis le fichier JSON
libs=$(awk '/"libs" : \[/,/\]/' "$meta_file" | tr -d '\n"[]:' | sed 's/libs//')

libs_cleaned=$(echo "$libs" | tr ',' ' ' | sed 's/  */ /g' | sed 's/^[[:space:]]*//;s/[[:space:]]*$//' )

# Affichage du résultat
if [ -z "$libs_cleaned" ]; then
    echo ""
else
    echo "$libs_cleaned"
fi
