<h1 style="text-align: center">村庄保卫战</h1>

<div style="text-align: center;">[简体中文]|<a href="./README-en.md">[English]</a></div>

## 快速开始

推荐操作系统: Windows/Linux

推荐CMake生成器: Visual Studio/Ninja

### Windows

**MinGW + Ninja**

```cmd
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -B "cmake-build-debug-ninja"
cmake --build cmake-build-debug-ninja
"./cmake-build-debug-ninja/main.exe"
```

**Visual Studio**

```cmd
cmake -B cmake-build-debug-visual-studio -G "Visual Studio" -DBUILD_SHARED_LIBS=TRUE
cmake --build cmake-build-debug-visual-studio --target main --config Debug
"./cmake-build-debug-visual-studio/Debug/main.exe"
```

### Linux

**Ubuntu:latest**

```bash
apt-get update -y && apt-get install libxrandr-dev libxcursor-dev libudev-dev libopenal-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev libfreetype6-dev -y
apt install gcc g++ cmake git -y
cmake -B build && \
cmake --build build && \
./build/main
```

**Fedora41**

```bash
yum update -y && yum install freetype-devel libX11-devel libXcursor-devel libXrandr-devel mesa-libGL-devel systemd-devel openal-soft-devel libvorbis-devel libogg-devel flac-devel -y
yum install gcc g++ cmake git -y
cmake -B build -DCMAKE_MAKE_PROGRAM=ninja -G Ninja && \
cmake --build build && \
./build/main
```

## 参考

`src/GUI`下的部分基础框架代码参考自*SFML Game Development By Example*(Raimondas Pupius)