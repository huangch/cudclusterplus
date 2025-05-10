# Find Python
find_package(Python COMPONENTS Interpreter Development REQUIRED)

# Find pybind11
include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        v2.11.1  # Adjust to the version you want
)
FetchContent_MakeAvailable(pybind11)

# Add Python module
pybind11_add_module(cudclusterplus_python cudclusterplus_python.cpp)

# Link with the main library
target_link_libraries(cudclusterplus_python PRIVATE cudclusterplus)

# Rename output to match Python import conventions
set_target_properties(cudclusterplus_python PROPERTIES
    OUTPUT_NAME "cudclusterplus"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/python"
)