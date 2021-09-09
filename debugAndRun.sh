#!/bin/bash

printf "Compiling program..........\n\n"
g++ -g Src/main.cpp Src/CharHelper.cpp Src/math.cpp -o build/Debug/main 
./build/Debug/main

