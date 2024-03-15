#!/bin/bash

TESTER="../tester/"
# Remove build directory if exists
if [ -d ./build/ ]; then
	rm -rf ./build
fi

# Create build directory and navigate to it
mkdir -p ./build && cd ./build || exit

# Generate Makefiles using CMake
cmake ..

# Build the project
cmake --build .

# Install the library and headers
INSTALL_DIR="/usr/local/Cellar/easyjson/0.0.1"
mkdir -p "$INSTALL_DIR/lib"
mkdir -p "$INSTALL_DIR/include"

# Copy the library file
cp libeasyjson.dylib "$INSTALL_DIR/lib"

# Copy the header files
cp -R ../include/* "$INSTALL_DIR/include/"

# Copy config files to tester(s)
cp -R ../configs/* "$TESTER"