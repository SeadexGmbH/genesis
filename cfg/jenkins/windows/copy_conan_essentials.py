import re
import sys
import shutil
import os

if len(sys.argv) != 3:
    print(f"Usage: {sys.argv[0]} <conan_toolchain_path> <destination_path>")
    sys.exit(1)

conan_toolchain_path = sys.argv[1]
destination_path = sys.argv[2]

# Read the contents of the conan_toolchain.cmake file
with open(conan_toolchain_path, "r") as f:
    contents = f.read()

# Use regular expressions to extract the paths in the CMAKE_LIBRARY_PATH variable
pattern = r'CMAKE_LIBRARY_PATH\s+\"?([^\)]+)'
match = re.search(pattern, contents)
if match:
    paths = match.group(1).strip().split("\" \"")
    paths = [p.strip("\"") for p in paths]
    sead_paths = [p for p in paths if "seade" in p]
    print(sead_paths[0])
    shutil.copy(os.path.join(sead_paths[0], "essentials.lib"), destination_path)
    pdb_build_path = os.path.join(sead_paths[0], "../../b/build/lib/Debug")
    pdb_file = os.path.join(pdb_build_path, "essentials.pdb")
    if os.path.isfile(pdb_file):
        shutil.copy(pdb_file, destination_path)
    else:
        print(f"No essentials.pdb found! Searched for: ", pdb_file)
else:
    print("CMAKE_LIBRARY_PATH not found in the file.")


