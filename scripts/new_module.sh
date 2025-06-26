#!/bin/bash

set -e

MODULE_NAME=$1

if [ -z "$MODULE_NAME" ]; then
    echo "Usage: ./scripts/add_module.sh <module_name>"
    exit 1
fi

if [[ ! "$MODULE_NAME" =~ ^[a-z][a-z0-9_]*$ ]]; then
    echo "Erreur : '$MODULE_NAME' n'est pas un nom valide (doit être en snake_case, ex : un_module)."
    exit 1
fi

MODULE_DIR="modules/$MODULE_NAME"

if [ -d "$MODULE_DIR" ]; then
    echo "Le module '$MODULE_NAME' existe déjà."
    exit 1
fi

# Création de la structure
mkdir -p "$MODULE_DIR/include/$MODULE_NAME"
mkdir -p "$MODULE_DIR/src"

CLASS_NAME=$(echo "$MODULE_NAME" | sed -E 's/(^|_)([a-z])/\U\2/g')

# Crée le .hpp
cat > "$MODULE_DIR/include/$MODULE_NAME/${MODULE_NAME}.hpp" <<EOF
#pragma once

class ${CLASS_NAME}{
public:
    ${CLASS_NAME}();
    ~${CLASS_NAME}();
};
EOF

# Crée le .cpp
cat > "$MODULE_DIR/src/${MODULE_NAME}.cpp" <<EOF
#include <${MODULE_NAME}/${MODULE_NAME}.hpp>
// other module
#include <iostream>

${CLASS_NAME}::${CLASS_NAME}() {}

${CLASS_NAME}::~${CLASS_NAME}() {}

EOF

# Crée le CMakeLists.txt
cat > "$MODULE_DIR/CMakeLists.txt" <<EOF
add_library($MODULE_NAME STATIC
    src/$MODULE_NAME.cpp
)

target_include_directories($MODULE_NAME PUBLIC
    \${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries($MODULE_NAME PUBLIC
    #add dependence lib here
)
EOF

#Crée le meta.json
cat > "$MODULE_DIR/meta.json" <<EOF
{
    "name" : "$MODULE_NAME",
    "description" : "This is à module : $MODULE_NAME",
    "dependences" : {
        "libs" : ["SDL3"],
        "modules" : []  
    },
    "fonctions" :[]
}
EOF

#Crée le README.md
cat >"$MODULE_DIR/README.md" <<EOF
# $MODULE_NAME
desc...
## Dependencies 
dep...
## Functions
fun...
## EXAMPLE : 
\`\`\`cpp
#include <iostream>
\`\`\`
# Motes
notes...
EOF

echo " Module '$MODULE_NAME' créé avec succès."
