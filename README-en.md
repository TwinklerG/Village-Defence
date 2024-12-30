<h1 style="text-align: center">Villege Defence</h1>

<div style="text-align: center;"><a href="./README.md">[简体中文]</a>|[English]</div>

## Quick Start

Recommended OS: Windows/Linux

Recommended CMake generator: Visual Studio/Ninja

### Windows

**MinGW + Ninja**

```cmd
debug-ninja.bat
```

**Visual Studio**

```cmd
release-vs.bat # or debug-vs.bat
```

### Linux

**Ubuntu:latest**

```bash
apt-get update -y && apt-get install libxrandr-dev libxcursor-dev libudev-dev libopenal-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev libfreetype6-dev -y
apt install gcc g++ cmake git -y
bash ./release-ubuntu.sh
```

**Fedora41**

```bash
yum update -y && yum install freetype-devel libX11-devel libXcursor-devel libXrandr-devel mesa-libGL-devel systemd-devel openal-soft-devel libvorbis-devel libogg-devel flac-devel -y
yum install gcc g++ cmake git -y
bash ./release-fedora.sh
```

## Reference

Some basic framework codes under `src/GUI` are referenced from *SFML Game Development By Example* (Raimondas Pupius)