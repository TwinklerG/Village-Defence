#!/usr/bin/bash
cmake -B cmake-build-debug -DCMAKE_MAKE_PROGRAM=ninja -G Ninja && \
cmake --build cmake-build-debug && \
"./cmake-build-debug/main"