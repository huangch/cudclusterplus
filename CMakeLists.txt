cmake_minimum_required(VERSION 3.18)
project(CuDClusterPlus CUDA CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set CUDA standard
set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# Find required packages
find_package(CUDA REQUIRED)
find_package(JNI)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CUDA_INCLUDE_DIRS}
)

# Add main library source
add_subdirectory(src)

# Optional Python bindings
option(BUILD_PYTHON_BINDINGS "Build Python bindings" ON)
if(BUILD_PYTHON_BINDINGS)
    add_subdirectory(python)
endif()

# Optional Java bindings
option(BUILD_JAVA_BINDINGS "Build Java bindings" ON)
if(BUILD_JAVA_BINDINGS AND JNI_FOUND)
    add_subdirectory(java)
endif()