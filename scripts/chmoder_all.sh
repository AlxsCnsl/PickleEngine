#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
for file in "$SCRIPT_DIR"/*.sh; do
    [ "$file" != "$SCRIPT_DIR/chmoder_all.sh" ] && chmod +x "$file" && echo "chmod +x $file"
done
