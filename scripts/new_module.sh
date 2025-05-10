#!/bin/bash

set -e

MODULE_NAME=$1

if [ -z "$MODULE_NAME" ]; then
    echo "Usage: ./scripts/add_module.sh <module_name>"
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

# Crée le .hpp
cat > "$MODULE_DIR/include/$MODULE_NAME/${MODULE_NAME}.hpp" <<EOF
#pragma once

class ${MODULE_NAME^}Module : public InterfaceModule {
public:
    ${MODULE_NAME^}Module();
    ~${MODULE_NAME^}Module();

EOF

# Crée le .cpp
cat > "$MODULE_DIR/src/${MODULE_NAME}.cpp" <<EOF
#include <${MODULE_NAME}/${MODULE_NAME}.hpp>
// other module
#include <iostream>

${MODULE_NAME^}Module::${MODULE_NAME^}Module() {}

${MODULE_NAME^}Module::~${MODULE_NAME^}Module() {
}

EOF

# Crée le CMakeLists.txt
cat > "$MODULE_DIR/CMakeLists.txt" <<EOF
add_library($MODULE_NAME
    src/$MODULE_NAME.cpp
)

# Target public and private includes
target_include_directories($MODULE_NAME
    PUBLIC include
    PRIVATE ${CMAKE_SOURCE_DIR}/core
)

# Link SDL3 to window_render
target_link_libraries($MODULE_NAME PRIVATE SDL3)

# Ensure that PickleEngine uses window_render if present
if(TARGET PickleEngine)
    target_link_libraries(PickleEngine INTERFACE $MODULE_NAME)
endif()
EOF

#Crée le meta.json
cat > "$MODULE_DIR/CMakeLists.txt" <<EOF
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


echo " Module '$MODULE_NAME' créé avec succès."
