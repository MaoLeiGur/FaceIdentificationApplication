@echo off
echo "Building Face ID Application..."

:: Create build directory
if not exist build mkdir build
cd build

:: Configure with CMake
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release

:: Build
cmake --build ../../ --config Release

echo Build completed!