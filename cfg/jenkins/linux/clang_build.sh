#!/bin/bash

export CMAKE_C_COMPILER=clang-13
export CMAKE_CXX_COMPILER=clang++-13

echo 'Set Clang as default compiler'
chmod +x clang_set_compiler.py
./clang_set_compiler.py

echo 'Generate conan profiles'
conan profile detect
chmod +x conan_clang_profiles.py
./conan_clang_profiles.py

cd ../../..
conan install . -g CMakeToolchain --profile=debug --build=missing -of cmaked -o seadex-essentials*:shared=True

cd cmaked
cmake .. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DSPDLOG_FMT_EXTERNAL=ON -DCMAKE_BUILD_TYPE=Debug -DESS_BUILD_UNIT_TESTS=ON -DBUILD_SHARED_LIBS=ON -DGEN_BUILD_EXAMPLES=ON
cmake --build --preset conan-debug

cmake .. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DSPDLOG_FMT_EXTERNAL=ON -DCMAKE_BUILD_TYPE=Debug -DESS_BUILD_UNIT_TESTS=ON -DBUILD_SHARED_LIBS=OFF -DGEN_BUILD_EXAMPLES=ON
cmake --build --preset conan-debug

cd ..
conan install . -g CMakeToolchain --profile=release --build=missing -of cmake -o seadex-essentials*:shared=True

cd cmake
cmake .. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DSPDLOG_FMT_EXTERNAL=ON -DCMAKE_BUILD_TYPE=Release -DESS_BUILD_UNIT_TESTS=ON -DBUILD_SHARED_LIBS=ON -DGEN_BUILD_EXAMPLES=ON
cmake --build --preset conan-release

cmake .. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DSPDLOG_FMT_EXTERNAL=ON -DCMAKE_BUILD_TYPE=Release -DESS_BUILD_UNIT_TESTS=ON -DBUILD_SHARED_LIBS=OFF -DGEN_BUILD_EXAMPLES=ON
cmake --build --preset conan-release
