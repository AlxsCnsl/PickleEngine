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

# Extraction des Modules depuis le fichier JSON
modules=$(awk '/"modules" : \[/,/\]/' "$meta_file" | tr -d '\n"[]:' | sed 's/modules//')

modules_cleaned=$(echo "$modules" | tr ',' ' ' | sed 's/  */ /g' | sed 's/^[[:space:]]*//;s/[[:space:]]*$//' )

# Affichage du résultat
if [ -z "$modules_cleaned" ]; then
    echo ""
else
    echo "$modules_cleaned"
fi
