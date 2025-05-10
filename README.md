# CuDClusterPlus

A CUDA-based DBSCAN implementation with Python and Java bindings.

## Requirements

- CUDA Toolkit (11.0 or newer recommended)
- CMake (3.18 or newer)
- Ninja (optional, for faster builds)
- Python 3.6+ (for Python bindings)
- JDK 8+ (for Java bindings)
- C++ compiler with C++17 support

## Setting Up with Conda (Recommended)

### Prerequisites

- [Miniconda](https://docs.conda.io/en/latest/miniconda.html) or [Anaconda](https://www.anaconda.com/products/distribution)
- Git
- CUDA-capable GPU with appropriate drivers installed

### Setup Instructions

1. **Clone the Repository**

```bash
git clone https://github.com/username/CuDClusterPlus.git
cd CuDClusterPlus
```

2. **Create and Activate Conda Environment**

```bash
# Create the conda environment from environment.yml
conda env create -f environment.yml

# Activate the environment
conda activate cudclusterplus
```

3. **Environment Variables**

The project includes a `.env` file with environment variables. You'll need to load these variables:

**On Windows (PowerShell):**

```powershell
Get-Content .env | ForEach-Object { 
    if($_ -match "(.+)=(.+)") { 
        $key = $matches[1]
        $value = $matches[2]
        # Expand environment variables in the value
        $value = $ExecutionContext.InvokeCommand.ExpandString($value)
        [System.Environment]::SetEnvironmentVariable($key, $value) 
    } 
}
```

**On Windows (CMD):**

```cmd
for /f "tokens=1,2 delims==" %a in (.env) do set %a=%b
```

**On Linux/macOS:**

```bash
export $(grep -v '^#' .env | xargs -0 | envsubst)
```

4. **Build the Project**

**Using provided build script:**

```bash
# On Linux/macOS
./build.sh

# On Windows
.\build.bat
```

**Or manually:**

```bash
mkdir -p build
cd build

# Configure with CMake
cmake -GNinja ..

# Build
ninja

# Or with standard CMake
# cmake ..
# cmake --build . --config Release
```

### Troubleshooting Conda Setup

#### CUDA Issues

- **Error: CUDA driver version is insufficient for CUDA runtime version**
  - Solution: Update your NVIDIA drivers

- **Error: No CUDA-capable device is detected**
  - Solution: Verify GPU compatibility and driver installation

#### Conda Environment Issues

- **Error: PackagesNotFoundError**
  - Solution: Try using the `-c conda-forge` channel or update conda

- **Error: EnvironmentNameNotFound**
  - Solution: Verify the environment name matches what's in environment.yml

#### Build Issues

- **Error: CMake can't find CUDA**
  - Solution: Ensure CUDA is in your PATH and verify installation with `nvcc --version`

- **Error: CMake can't find JNI**
  - Solution: Set the `JAVA_HOME` environment variable
  
- **Error: pybind11 not found**
  - Solution: Install pybind11 manually with `pip install pybind11`

#### Updating Dependencies

To update the conda environment after changes to `environment.yml`:

```bash
conda env update -f environment.yml --prune
```

## Building (Manual Setup)

### Using CMake and Ninja

```bash
# Create build directory
mkdir -p build && cd build

# Configure with CMake
cmake -GNinja ..

# Build
ninja

# Alternatively, using standard CMake
# cmake ..
# cmake --build .
```

### Build Options

- `BUILD_PYTHON_BINDINGS`: Enable/disable Python bindings (default: ON)
- `BUILD_JAVA_BINDINGS`: Enable/disable Java bindings (default: ON)

Example:
```bash
cmake -GNinja -DBUILD_PYTHON_BINDINGS=OFF ..
```

## Windows-Specific Instructions

### Building on Windows

1. Open Command Prompt or PowerShell
2. Navigate to your project directory
3. Create and enter the build directory:

```powershell
mkdir build
cd build
```

4. Configure with CMake (using Visual Studio generator):

```powershell
# For Visual Studio 2022
cmake -G "Visual Studio 17 2022" -A x64 ..

# For Visual Studio 2019
# cmake -G "Visual Studio 16 2019" -A x64 ..

# If you prefer using Ninja (faster builds)
# cmake -G Ninja ..
```

5. Build the project:

```powershell
# Using Visual Studio generator
cmake --build . --config Release

# If using Ninja
# ninja
```

### Setting Up Environment Variables on Windows

After building, you need to set up some environment variables to use the Python and Java bindings:

**For Python:**

```powershell
# Temporary (for current session)
$env:PYTHONPATH = "$env:PYTHONPATH;$(Get-Location)\build\python"

# Permanent (requires admin rights)
# [Environment]::SetEnvironmentVariable("PYTHONPATH", "$env:PYTHONPATH;C:\path\to\project\build\python", "User")
```

**For Java:**

```powershell
# Temporary (for current session)
$env:CLASSPATH = "$env:CLASSPATH;$(Get-Location)\build\java\cudclusterplus.jar"
$env:PATH = "$env:PATH;$(Get-Location)\build\java;$(Get-Location)\build\lib\Release"

# Permanent (requires admin rights)
# [Environment]::SetEnvironmentVariable("CLASSPATH", "$env:CLASSPATH;C:\path\to\project\build\java\cudclusterplus.jar", "User")
# [Environment]::SetEnvironmentVariable("PATH", "$env:PATH;C:\path\to\project\build\java;C:\path\to\project\build\lib\Release", "User")
```

## Python Usage

```python
import numpy as np
from cudclusterplus import dbscan, version

# Get version
print(f"Using {version()}")

# Generate sample data
points = np.random.rand(1000, 2).astype(np.float32)

# Run DBSCAN
labels = dbscan(points, eps=0.1, min_pts=5)

print(f"Found {len(set(labels))} clusters")
```

## Java Usage

```java
import com.cudclusterplus.CuDClusterPlus;

public class Example {
    public static void main(String[] args) {
        System.out.println("Using " + CuDClusterPlus.getVersion());
        
        // Create sample data
        int n = 1000;
        int dim = 2;
        float[] points = new float[n * dim];
        
        // Fill with random data
        for (int i = 0; i < points.length; i++) {
            points[i] = (float) Math.random();
        }
        
        // Run DBSCAN
        CuDClusterPlus clusterer = new CuDClusterPlus();
        int[] labels = clusterer.dbscan(points, n, dim, 0.1f, 5);
        
        // Count unique clusters
        java.util.Set<Integer> uniqueClusters = new java.util.HashSet<>();
        for (int label : labels) {
            uniqueClusters.add(label);
        }
        
        System.out.println("Found " + uniqueClusters.size() + " clusters");
    }
}
```

## Project Structure

```
CuDClusterPlus/
├── CMakeLists.txt             # Root CMake configuration file
├── README.md                  # Project documentation
├── .env                       # Environment variables
├── .gitignore                 # Git ignore patterns
├── environment.yml            # Conda environment definition
├── build.sh                   # Build script for Linux/macOS
├── build.bat                  # Build script for Windows
│
├── include/                   # Header files
│   └── cudclusterplus.h       # Main library header with API definitions
│
├── src/                       # Source code for main library
│   ├── CMakeLists.txt         # CMake configuration for main library
│   ├── main.cu                # CUDA implementation
│   └── cudclusterplus.cpp     # C++ implementation
│
├── python/                    # Python binding files
│   ├── CMakeLists.txt         # CMake configuration for Python bindings
│   ├── setup.py               # Python package setup script
│   └── cudclusterplus_python.cpp  # Python binding code (pybind11)
│
└── java/                      # Java binding files
    ├── CMakeLists.txt         # CMake configuration for Java bindings
    ├── com/
    │   └── cudclusterplus/
    │       ├── CuDClusterPlus.java      # Java wrapper class
    │       └── CuDClusterPlusJNI.java   # JNI method declarations
    └── jni/
        ├── cudclusterplus_jni.cpp       # JNI implementation
        └── com_cudclusterplus_CuDClusterPlusJNI.h  # JNI header file
```

## Additional Resources

- [CUDA Documentation](https://docs.nvidia.com/cuda/)
- [CMake Documentation](https://cmake.org/documentation/)
- [Pybind11 Documentation](https://pybind11.readthedocs.io/)
- [Conda Documentation](https://docs.conda.io/)

## License

MIT License

## Contributing

Pull requests welcome!