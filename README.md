<h1 style="text-align: center">村庄保卫战</h1>

<div style="text-align: center;">[简体中文]|<a href="./README-en.md">[English]</a></div>

## 快速开始

请使用支持C++17的编译器

推荐操作系统: Linux/Windows

推荐CMake生成器: Ninja

### Windows

请预先安装[ninja](https://github.com/ninja-build/ninja/releases)

由于项目使用最新的SFML3.0，因此推荐采用官方提供的编译工具，详见[https://www.sfml-dev.org/download/sfml/3.0.0/](https://www.sfml-dev.org/download/sfml/3.0.0/)

**注意**：本项目包含中文字符，请不要使用MSBuild(Visual Studio)进行构建

**MinGW + Ninja**

```cmd
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -B "cmake-build-debug-ninja"
cmake --build cmake-build-debug-ninja
"./cmake-build-debug-ninja/main.exe"
```

### Linux

**Ubuntu:latest**

```bash
apt-get update -y && apt-get install libxrandr-dev libxcursor-dev libudev-dev libopenal-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev libfreetype6-dev libxi-dev -y
apt install gcc g++ cmake git -y
cmake -B build && \
cmake --build build && \
./build/main
```

**Fedora41**

```bash
yum update -y && yum install freetype-devel libX11-devel libXcursor-devel libXrandr-devel mesa-libGL-devel systemd-devel openal-soft-devel libvorbis-devel libogg-devel flac-devel libxi-devel -y
yum install gcc g++ cmake git -y
cmake -B build -DCMAKE_MAKE_PROGRAM=ninja -G Ninja && \
cmake --build build && \
./build/main
```

## 参考

`src/GUI`下的部分基础框架代码参考自*SFML Game Development By Example*(Raimondas Pupius)

## 开源库的使用

[SFML3.0.0](https://github.com/SFML/SFML.git)

[JSON](https://github.com/nlohmann/json.git)

# 版权资源的使用

**贴图**取自

- [Lots of free 2d tiles and sprites by Hyptosis](https://opengameart.org/content/lots-of-free-2d-tiles-and-sprites-by-hyptosis)

**背景音乐**取自

- [Loading Screen Loop](https://opengameart.org/content/loading-screen-loop)
- [Battle Theme A](https://opengameart.org/content/battle-theme-a)

**音效**取自

- [Voiceover Pack: Fighter (40+ taunts)](https://opengameart.org/content/voiceover-pack-fighter-40-taunts)