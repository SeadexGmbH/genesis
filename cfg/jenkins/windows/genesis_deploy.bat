rem ECHO OFF

cd ../../..

rem create folder that will be archived
set genesis_new_version=%CD%\deploy\genesis

mkdir %genesis_new_version%\build\Windows
mkdir %genesis_new_version%\build\Linux

mkdir %genesis_new_version%\build\Windows\x64
mkdir %genesis_new_version%\build\Linux\x64

mkdir "%genesis_new_version%\build\Windows\x64\VS2019 142"
mkdir "%genesis_new_version%\build\Linux\x64\gcc 10"
mkdir "%genesis_new_version%\build\Linux\x64\clang 13"

mkdir "%genesis_new_version%\build\Windows\x64\VS2019 142\Release"
mkdir "%genesis_new_version%\build\Linux\x64\gcc 10\Release"
mkdir "%genesis_new_version%\build\Linux\x64\clang 13\Release"

mkdir "%genesis_new_version%\build\Windows\x64\VS2019 142\Debug"
mkdir "%genesis_new_version%\build\Linux\x64\gcc 10\Debug"
mkdir "%genesis_new_version%\build\Linux\x64\clang 13\Debug"

mkdir "%genesis_new_version%\build\Windows\x64\VS2019 142\Release\bin"
mkdir "%genesis_new_version%\build\Linux\x64\gcc 10\Release\bin"
mkdir "%genesis_new_version%\build\Linux\x64\clang 13\Release\bin"

mkdir "%genesis_new_version%\build\Windows\x64\VS2019 142\Release\lib"
mkdir "%genesis_new_version%\build\Linux\x64\gcc 10\Release\lib"
mkdir "%genesis_new_version%\build\Linux\x64\clang 13\Release\lib"

mkdir "%genesis_new_version%\build\Windows\x64\VS2019 142\Debug\lib"
mkdir "%genesis_new_version%\build\Linux\x64\gcc 10\Debug\lib"
mkdir "%genesis_new_version%\build\Linux\x64\clang 13\Debug\lib"

copy %CD%\win-cmake\essentials.lib "%genesis_new_version%\build\Windows\x64\VS2019 142\Release\lib"
copy %CD%\win-cmaked\essentials.lib "%genesis_new_version%\build\Windows\x64\VS2019 142\Debug\lib"
copy %CD%\win-cmaked\essentials.pdb "%genesis_new_version%\build\Windows\x64\VS2019 142\Debug\lib"

copy %CD%\win-cmake\lib\Release\genesis.lib "%genesis_new_version%\build\Windows\x64\VS2019 142\Release\lib"
copy %CD%\win-cmaked\lib\Debug\genesis.lib "%genesis_new_version%\build\Windows\x64\VS2019 142\Debug\lib"
copy %CD%\win-cmaked\lib\Debug\genesis.pdb "%genesis_new_version%\build\Windows\x64\VS2019 142\Debug\lib"

rem copy includes of essentials
robocopy %CD%\externals\essentials\include "%genesis_new_version%\build\Windows\x64\VS2019 142\Release\include" /E
robocopy %CD%\externals\essentials\include "%genesis_new_version%\build\Windows\x64\VS2019 142\Debug\include" /E
robocopy %CD%\externals\essentials\include "%genesis_new_version%\build\Linux\x64\gcc 10\Release\include" /E
robocopy %CD%\externals\essentials\include "%genesis_new_version%\build\Linux\x64\gcc 10\Debug\include" /E
robocopy %CD%\externals\essentials\include "%genesis_new_version%\build\Linux\x64\clang 13\Release\include" /E
robocopy %CD%\externals\essentials\include "%genesis_new_version%\build\Linux\x64\clang 13\Debug\include" /E

copy %CD%\cmake\libgenesis.so "%genesis_new_version%\build\Linux\x64\gcc 10\Release\lib"
copy %CD%\cmake\libessentials.so "%genesis_new_version%\build\Linux\x64\gcc 10\Release\lib"
copy %CD%\cmaked\libgenesis.so "%genesis_new_version%\build\Linux\x64\gcc 10\Debug\lib"
copy %CD%\cmaked\libessentials.so "%genesis_new_version%\build\Linux\x64\gcc 10\Debug\lib"

copy %CD%\clang-cmake\libgenesis.so "%genesis_new_version%\build\Linux\x64\clang 13\Release\lib"
copy %CD%\clang-cmake\libessentials.so "%genesis_new_version%\build\Linux\x64\clang 13\Release\lib"
copy %CD%\clang-cmaked\libgenesis.so "%genesis_new_version%\build\Linux\x64\clang 13\Debug\lib"
copy %CD%\clang-cmaked\libessentials.so "%genesis_new_version%\build\Linux\x64\clang 13\Debug\lib"

rem copy applications
copy %CD%\win-cmake\bin\Release\html_page_generator.exe "%genesis_new_version%\build\Windows\x64\VS2019 142\Release\bin"
robocopy %CD%\examples\html_page_generator\templates "%genesis_new_version%\build\Windows\x64\VS2019 142\Release\bin\templates"
copy %CD%\cmake\html_page_generator "%genesis_new_version%\build\Linux\x64\gcc 10\Release\bin"
robocopy %CD%\examples\html_page_generator\templates "%genesis_new_version%\build\Linux\x64\gcc 10\Release\bin\templates"
copy %CD%\clang-cmake\html_page_generator "%genesis_new_version%\build\Linux\x64\clang 13\Release\bin"
robocopy %CD%\examples\html_page_generator\templates "%genesis_new_version%\build\Linux\x64\clang 13\Release\bin\templates"

rem copy documentation
robocopy %CD%\docs\release\ %genesis_new_version%\documentation\ /E

rem remove not needed directories
rmdir /s /q %genesis_new_version%\source@tmp
rmdir /s /q %genesis_new_version%\source\.git

rem set a variable with the path of zip archive
set archiveZip=%genesis_new_version%_%1.zip

rem 7zip-ing
"C:\Program Files\7-Zip"\7z a -t7z %archiveZip% %genesis_new_version%

curl -u %2:%3 -T %archiveZip% "%4/genesis_%1.7z"

rem delete old folder
RD /Q /S %genesis_new_version%