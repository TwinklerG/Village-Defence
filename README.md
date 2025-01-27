<h1 align="center">村庄保卫战</h1>

<div align="center">[简体中文]|<a href="./README-en.md">[English]</a></div>

<p align="center">
  <img alt="GitHub" src="https://img.shields.io/github/license/TwinklerG/Village-Defence">
  <img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/TwinklerG/Village-Defence">	
  <img alt="GitHub release (latest by date)" src="https://img.shields.io/github/v/release/TwinklerG/Village-Defence">
  <img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/TwinklerG/Village-Defence">
  <img alt="GitHub top language" src="https://img.shields.io/github/languages/top/TwinklerG/Village-Defence">
  <img alt="GitHub stars" src="https://img.shields.io/github/stars/TwinklerG/Village-Defence">
  <img alt="GitHub All Releases" src="https://img.shields.io/github/downloads/TwinklerG/Village-Defence/total">
  <img alt="GitHub issues" src="https://img.shields.io/github/issues-raw/TwinklerG/Village-Defence">
  <img alt="GitHub closed issues" src="https://img.shields.io/github/issues-closed-raw/TwinklerG/Village-Defence">
  <img alt="PRs welcome" src="https://img.shields.io/badge/PRs-welcome-brightgreen">
</p>

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
cmake -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -B "cmake-build-debug-ninja"
cmake --build cmake-build-debug-ninja
cd cmake-build-debug-ninja
./main.exe
```

### Linux

**Ubuntu:latest**

```bash
apt-get update -y && apt-get install libxrandr-dev libxcursor-dev libudev-dev libopenal-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev libfreetype6-dev libxi-dev -y
apt install gcc g++ cmake git -y
cmake -B build && \
cmake --build build && \
cd build
./main
```

**Fedora41**

```bash
yum update -y && yum install freetype-devel libX11-devel libXcursor-devel libXrandr-devel mesa-libGL-devel systemd-devel openal-soft-devel libvorbis-devel libogg-devel flac-devel libxi-devel -y
yum install gcc g++ cmake git -y
cmake -B build -DCMAKE_MAKE_PROGRAM=ninja -G Ninja && \
cmake --build build && \
cd build
./main
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
