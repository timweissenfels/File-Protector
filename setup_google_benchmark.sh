#!/bin/bash
git clone https://github.com/google/googletest.git benchmark/googletest
cd benchmark/googletest
cmake -E make_directory "build"
cmake -E chdir "build" cmake -DCMAKE_BUILD_TYPE=Release ../
cmake --build "build" --config Release

