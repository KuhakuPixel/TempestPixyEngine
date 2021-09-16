printf "Starting unit testing\n"
g++ tests/test.cpp Src/CharHelper.cpp Src/math.cpp Src/board.cpp Src/analyzer.cpp -o tests/test 
./tests/test
