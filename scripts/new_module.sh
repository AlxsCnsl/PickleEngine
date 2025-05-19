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
add_library($MODULE_NAME
    src/$MODULE_NAME.cpp
)

execute_process(
    COMMAND bash \${CMAKE_SOURCE_DIR}/scripts/get_libs.sh \${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE result_libs
    OUTPUT_VARIABLE libs_output
    ERROR_VARIABLE libs_error
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Run get_modules.sh and store the output in a variable
execute_process(
    COMMAND bash \${CMAKE_SOURCE_DIR}/scripts/get_modules.sh \${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE result_modules
    OUTPUT_VARIABLE modules_output
    ERROR_VARIABLE modules_error
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Target public and private includes
target_include_directories($MODULE_NAME
    PUBLIC include
    PRIVATE \${CMAKE_SOURCE_DIR}/core
)

# Link SDL3 to $MODULE_NAME
target_link_libraries($MODULE_NAME PUBLIC \${libs_output} \${modules_output})

# Ensure that PickleEngine uses $MODULE_NAME if present
if(TARGET PickleEngine)
    target_link_libraries(PickleEngine INTERFACE $MODULE_NAME)
endif()

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
