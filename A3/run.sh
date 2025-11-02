#!/bin/bash
# Assemble the ARM64 assembly file into an object file
as -arch arm64 -o main.o main.s

# Link with the C standard library (libSystem) to resolve printf, scanf, etc.
ld -o main main.o -lSystem -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -e _main -syslibroot $(xcrun --sdk macosx --show-sdk-path)

# Run the program
./main
echo "Exit code (x0): $?"