cmake -B build -DCMAKE_MAKE_PROGRAM=ninja -G Ninja && \
cmake --build build --config Release && \
./build/main