from setuptools import setup, find_packages
import os

# This is a simplified setup.py for installation
# A more complete version would include proper build system integration

setup(
    name="cudclusterplus",
    version="0.1.0",
    description="CUDA-based DBSCAN Implementation",
    author="CuDClusterPlus Team",
    packages=find_packages(),
    package_data={
        "cudclusterplus": ["*.so", "*.dll", "*.dylib"],
    },
    install_requires=[
        "numpy",
    ],
    classifiers=[
        "Development Status :: 3 - Alpha",
        "Intended Audience :: Science/Research",
        "License :: OSI Approved :: MIT License",
        "Programming Language :: Python :: 3",
        "Programming Language :: C++",
        "Topic :: Scientific/Engineering",
    ],
    python_requires=">=3.6",
)