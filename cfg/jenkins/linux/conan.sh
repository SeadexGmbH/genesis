#!/bin/bash

echo 'Generate conan profiles'
conan profile detect
chmod +x conan_profiles.py
./conan_profiles.py
