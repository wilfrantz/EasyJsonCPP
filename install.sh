#!/bin/bash

set -e

TESTER="../tester/"
VERSION="0.0.1"
LIB_EXT="dummy"
INSTALL_DIR="/dev/null"

# Remove build directory if it exists
if [ -d ./build/ ]; then
    echo "-- Removing build directory"
    rm -rf ./build
fi

# Create build directory and navigate to it
echo "-- Creating build directory"
mkdir -p ./build && cd ./build 

# Check for OS and set the correct library extension and installation directory
if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "-- Setting the correct library extension and installation directory for macOS"
    LIB_EXT="dylib"
    INSTALL_DIR="/usr/local/Cellar/easyjson/$VERSION"
    # Create the installation directories
    echo "-- Creating the installation directories"
    mkdir -p "$INSTALL_DIR/lib" "$INSTALL_DIR/include"
    # Copy the header files
    echo "-- Copying the header files"
    cp -R ../include/* "$INSTALL_DIR/include/" 
else # linux
    echo "-- Setting the correct library extension and installation directory for Linux"
    INSTALL_DIR="/usr/local/lib/easyjson/$VERSION"
    # Create the installation directories
    mkdir -p "$INSTALL_DIR/lib"
    # Copy the header files
    cp -R ../include/* "/usr/include/" 
    LIB_EXT="so"
fi

# Generate Makefiles using CMake
echo "-- Generating Makefiles using CMake"
cmake ..

# Build the project
echo "-- Building the project"
cmake --build .

# Copy the library file
echo "-- Copying the library file"
cp "libeasyjson.$LIB_EXT" "$INSTALL_DIR/lib"

# Copy config files to tester(s)
echo "-- Copying config files to tester(s)"
cp -R ../configs/* "$TESTER" 

echo "-- Installation completed successfully. --"
