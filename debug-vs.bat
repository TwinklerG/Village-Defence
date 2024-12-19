cmake -B cmake-build-debug-visual-studio -G "Visual Studio" -DBUILD_SHARED_LIBS=TRUE
cmake --build cmake-build-debug-visual-studio --target main --config Debug
"./cmake-build-debug-visual-studio/Debug/main.exe"