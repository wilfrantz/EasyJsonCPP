#!/bin/bash

# This script is used to install the unit test for the EasyJsonCPP library.

set -e

# Remove build directory if it exists
if [ -d "./build" ]; then
    echo "-- Removing build directory"
    rm -rf "./build"
fi

# Create build directory
echo "-- Creating build directory"
mkdir -p "./build" && cd "./build" 

# Generate Makefiles
echo "-- Generating Makefiles using CMake"
cmake ..

# Build project
echo "-- Building the project"
cmake --build .
