@echo off
setlocal

:: Create build directory
if not exist build mkdir build
cd build

:: Check if Ninja is available
where ninja >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo Configuring with CMake and Ninja...
    cmake -GNinja ..
    
    echo Building with Ninja...
    ninja
) else (
    echo Configuring with CMake and Visual Studio...
    cmake -G "Visual Studio 17 2022" -A x64 ..
    
    echo Building...
    cmake --build . --config Release
)

echo Build completed successfully.
cd ..

:: Set up environment variables for testing
echo Setting up Python path for testing...
set PYTHONPATH=%PYTHONPATH%;%CD%\build\python

:: Check if Java directories exist and set up classpath
if exist build\java (
    echo Setting up Java classpath for testing...
    set CLASSPATH=%CLASSPATH%;%CD%\build\java\cudclusterplus.jar
    set PATH=%PATH%;%CD%\build\java;%CD%\build\lib\Release
)

echo.
echo You can now use CuDClusterPlus in this terminal session.
echo For Python imports, use: from cudclusterplus import dbscan, version
echo.

endlocal