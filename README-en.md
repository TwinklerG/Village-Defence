<h1 style="text-align: center">Village Defence</h1>

<div style="text-align: center;"><a href="./README.md">[简体中文]</a>|[English]</div>

## Quick Start

Please use a compiler that supports C++17

Recommended operating system: Linux/Windows

Recommended CMake generator: Ninja

### Windows

Please install [ninja](https://github.com/ninja-build/ninja/releases) in advance

Since the project uses the latest SFML3.0, it is recommended to use the official compilation tool,
see [https://www.sfml-dev.org/download/sfml/3.0.0/](https://www.sfml-dev.org/download/sfml/3.0.0/) for details

**Note**: This project contains Chinese characters, please do not use MSBuild (Visual Studio) to build**MinGW + Ninja**

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

## Reference

Some basic framework codes under `src/GUI` are referenced from *SFML Game Development By Example* (Raimondas Pupius)

## Use of Open source libraries

[SFML3.0.0](https://github.com/SFML/SFML.git)

[JSON](https://github.com/nlohmann/json.git)

# Use of Copyrighted Resources

**textures** from

- [Lots of free 2d tiles and sprites by Hyptosis](https://opengameart.org/content/lots-of-free-2d-tiles-and-sprites-by-hyptosis)

**bgm** from

- [Loading Screen Loop](https://opengameart.org/content/loading-screen-loop)
- [Battle Theme A](https://opengameart.org/content/battle-theme-a)

**sound effects** from

- [Voiceover Pack: Fighter (40+ taunts)](https://opengameart.org/content/voiceover-pack-fighter-40-taunts)