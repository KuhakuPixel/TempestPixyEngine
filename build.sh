#!/bin/bash
printf "args : $1\n\n" 
if [[ "$1" = "debug" ]]
then
	printf "Compiling program (DEBUG) ..........\n\n"
	g++ -g Src/main.cpp Src/CharHelper.cpp Src/math.cpp Src/board.cpp Src/analyzer.cpp -o build/Debug/main
	./build/Debug/main
else
	printf "Compiling program (NORMAL)..........\n\n"
	g++   Src/main.cpp Src/CharHelper.cpp Src/math.cpp Src/board.cpp Src/analyzer.cpp -o build/Release/main
	./build/Release/main

fi
