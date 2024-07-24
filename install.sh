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

# Check for OS and set the correct library extension and installation directory
if [[ "$OSTYPE" == "darwin"* ]]; then
    LIB_EXT="dylib"
    INSTALL_DIR="/usr/local/Cellar/easyjson/$VERSION"
	# Create the installation directories
	mkdir -p "$INSTALL_DIR/lib" "$INSTALL_DIR/include"
	# Copy the header files
	cp -R ../include/* "$INSTALL_DIR/include/" 
else
    INSTALL_DIR="/usr/local/lib/easyjson/$VERSION"
	# Create the installation directories
	mkdir -p "$INSTALL_DIR/lib"
	# Copy the header files
	cp -R ../include/* "/usr/local/include/" 
    LIB_EXT="so"
fi

# Generate Makefiles using CMake
cmake ..

# Build the project
cmake --build .

# Copy the library file
cp "libeasyjson.$LIB_EXT" "$INSTALL_DIR/lib"

# Copy config files to tester(s)
cp -R ../configs/* "$TESTER" 

echo "-- Installation completed successfully."