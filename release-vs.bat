cmake -B cmake-build-release-visual-studio -G "Visual Studio" -DBUILD_SHARED_LIBS=TRUE
cmake --build cmake-build-release-visual-studio --target main --config Release
"./cmake-build-release-visual-studio/Release/main.exe"