#!/bin/bash

# Configuration file path
CONFIG_FILE="../easy_config.json"

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

# Copy configuration file
echo "Copying $CONFIG_FILE"
cp "$CONFIG_FILE" . || echo "Copy failed." 
