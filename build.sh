#!/bin/bash
set -e

# Create build directory
mkdir -p build
cd build

# Configure with CMake
if command -v ninja &> /dev/null
then
    echo "Configuring with CMake and Ninja..."
    cmake -GNinja ..
    
    echo "Building with Ninja..."
    ninja
else
    echo "Configuring with CMake..."
    cmake ..
    
    echo "Building..."
    cmake --build . -- -j$(nproc)
fi

echo "Build completed successfully."
cd ..

# If running on Linux/Mac, make the Python module accessible for testing
if [[ "$OSTYPE" == "linux-gnu"* || "$OSTYPE" == "darwin"* ]]; then
    echo "Setting up Python path for testing..."
    export PYTHONPATH=$PYTHONPATH:$(pwd)/build/python
    
    # Check if Java directories exist and set up classpath
    if [ -d "build/java" ]; then
        echo "Setting up Java classpath for testing..."
        export CLASSPATH=$CLASSPATH:$(pwd)/build/java/cudclusterplus.jar
        export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/build/java:$(pwd)/build/lib
    fi