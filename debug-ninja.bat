cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -B "cmake-build-debug-ninja"
cmake --build cmake-build-debug-ninja
"./cmake-build-debug-ninja/main.exe"