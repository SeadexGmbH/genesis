#! /usr/bin/python3

import os

debug_configuration = """
[settings]
arch=x86_64
build_type=Debug
compiler=clang
compiler.cppstd=17
compiler.libcxx=libstdc++11
compiler.version=13
os=Linux
"""

release_configuration = """
[settings]
arch=x86_64
build_type=Release
compiler=clang
compiler.cppstd=17
compiler.libcxx=libstdc++11
compiler.version=13
os=Linux
"""

conan_config_dir = os.popen("conan config home").read().strip()

conan_profiles_dir = conan_config_dir + "/profiles"

dir_exist = os.path.exists(conan_profiles_dir)
if not dir_exist:
   os.makedirs(conan_profiles_dir)

debug_profile_path = os.path.join(conan_profiles_dir, "debug")
release_profile_path = os.path.join(conan_profiles_dir, "release")

with open(debug_profile_path, "w") as f:
    f.write(debug_configuration)

	
with open(release_profile_path, "w") as f:
    f.write(release_configuration)
