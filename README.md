<h1 style="text-align: center">村庄保卫战</h1>

<div style="text-align: center;">[简体中文]|<a href="./README-en.md">[English]</a></div>

## 快速开始

推荐操作系统: Windows/Linux

推荐CMake生成器: Visual Studio/Ninja

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

## 参考

`src/GUI`下的部分基础框架代码参考自*SFML Game Development By Example*(Raimondas Pupius)