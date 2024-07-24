#!/bin/bash

set -e

TESTER="../tester/"
VERSION="0.0.1"
LIB_EXT="dummy"
INSTALL_DIR="/dev/null"

# Remove build directory if it exists
if [ -d ./build/ ]; then
	rm -rf ./build
fi

# Create build directory and navigate to it
mkdir -p ./build && cd ./build 

# Check for OS type and set the correct library extension and installation directory
if [[ "$OSTYPE" == "darwin"* ]]; then
    LIB_EXT="dylib"
    INSTALL_DIR="/usr/local/Cellar/easyjson/$VERSION"
else
    INSTALL_DIR="/usr/local/easyjson/$VERSION"
    LIB_EXT="so"
fi

# Generate Makefiles using CMake
cmake ..

# Build the project
cmake --build .

# Create the installation directories
mkdir -p "$INSTALL_DIR/lib"
mkdir -p "$INSTALL_DIR/include"

# Copy the library file
cp "libeasyjson.$LIB_EXT" "$INSTALL_DIR/lib"

# Copy the header files
cp -R ../include/* "$INSTALL_DIR/include/" 

# Copy config files to tester(s)
cp -R ../configs/* "$TESTER" 

echo "[100%] Installation completed successfully."