apt-get update -y && apt-get install libxrandr-dev libxcursor-dev libudev-dev libopenal-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev libfreetype6-dev -y
apt install gcc g++ cmake git -y
cmake -B build
cmake --build build --config Release
./build/main