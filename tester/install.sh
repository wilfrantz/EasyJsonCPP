#!/bin/bash

# Remove build directory if it exists
if [ -d "./build" ]; then
    rm -rf "./build"
fi

# Create build directory
mkdir -p "./build" && cd "./build" || exit

# Generate Makefiles
cmake ..

# Build project
cmake --build .
