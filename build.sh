#!/bin/bash

if [[ "$1" = "debug" ]]
then
	printf "Compiling program (DEBUG) ..........\n\n"
	g++ -g Src/main.cpp Src/CharHelper.cpp Src/math.cpp Src/board.cpp Src/analyzer.cpp Src/stringHelper.cpp Src/chessLib.cpp -o build/Debug/main
	gdb build/Debug/main
elif [[ "$1" = "test" ]]
then
	printf "Starting unit testing\n"
	#don't recompile the catch library every unit testing
	#ref :https://github.com/catchorg/Catch2/blob/devel/docs/slow-compiles.md
	g++ tests/TestMain.o tests/TestLegalPiecesMoves.cpp tests/TestLib.cpp tests/TestBoard.cpp tests/TestAnalyzer.cpp Src/CharHelper.cpp Src/math.cpp Src/board.cpp Src/analyzer.cpp Src/stringHelper.cpp Src/chessLib.cpp -o tests/test 
	./tests/test


elif [[ "$1" = "debugtest" ]]
then
	printf "Starting unit testing (Debug mode)\n"
        #don't recompile the catch library every unit testing
        #ref :https://github.com/catchorg/Catch2/blob/devel/docs/slow-compiles.md
        g++ -g tests/TestMain.o tests/TestLegalPiecesMoves.cpp tests/TestLib.cpp tests/TestBoard.cpp tests/TestAnalyzer.cpp Src/CharHelper.cpp Src/math.cpp Src/board.cpp Src/analyzer.cpp Src/stringHelper.cpp Src/chessLib.cpp -o tests/test 
        gdb tests/test

else
	printf "Compiling program (NORMAL)..........\n\n"
	g++ Src/main.cpp Src/CharHelper.cpp Src/math.cpp Src/board.cpp Src/analyzer.cpp Src/stringHelper.cpp Src/chessLib.cpp -o build/Release/main
	./build/Release/main

fi
