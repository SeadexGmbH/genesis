rem @ECHO OFF
conan profile detect
conan_profiles.py

cd ../../..
conan install . -g CMakeToolchain --profile=debug --build=missing -o seadex-essentials*:shared=False -s build_type=Debug -of win-cmaked
conan install . -g CMakeToolchain --profile=release --build=missing -o seadex-essentials*:shared=False -s build_type=Release -of win-cmake
