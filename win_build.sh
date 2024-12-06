#!/bin/bash

# Set the source files
SOURCE_FILES="main.cpp food.cpp snake.cpp sound.cpp"

# Set the output binary name
OUTPUT_BINARY="snake_game.exe"

# Compiler and linker flags
CXX=g++
CXXFLAGS="-std=c++11 -Wall"
LDFLAGS="-lraylib -lgdi32 -lwinmm"

# Compile and link the program
$CXX $CXXFLAGS $SOURCE_FILES -o $OUTPUT_BINARY $LDFLAGS

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Build successful! Running the program..."
    ./$OUTPUT_BINARY
else
    echo "Build failed!"
    exit 1
fi
