#!/bin/bash
#


# remove build direcotry if exixts
if [ -d ./build/ ]; then
	rm -rf ./build
fi

# create build direcotry
mkdir -p ./build && cd ./build || exit

# generate Makefiles
cmake ..

# Build project
cmake --build .



