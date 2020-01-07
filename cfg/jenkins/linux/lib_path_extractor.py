import re
import sys

if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} <conan_toolchain_path>")
    sys.exit(1)

conan_toolchain_path = sys.argv[1]

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
else:
    print("CMAKE_LIBRARY_PATH not found in the file.")
