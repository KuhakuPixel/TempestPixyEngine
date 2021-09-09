#!/bin/bash

printf "Compiling program..........\n\n"
g++ -g  Src/main.cpp Src/CharHelper.cpp Src/math.cpp -o build/Release/main
./build/Release/main
