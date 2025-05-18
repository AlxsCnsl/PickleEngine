#!/bin/bash
set -e 
mkdir -p build-linux
cmake -S . -B build-linux -G Ninja 
cmake --build build-linux
