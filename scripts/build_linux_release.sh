mkdir -p build-linux-release
cmake -S . -B build-linux-release -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build-linux-release