cmake -B build -DBUILD_SHARED_LIBSTRUE=false
cmake --build build --target main --config Release
"./build/Release/main.exe"