#include "catch.hpp"
#include "../Src/board.h"
TEST_CASE("Test Load fen to board", "[LoadFen]")
{
    Board board = Board();

    SECTION("TestLoad1")
    {
        board.LoadFromFen("B4r1k/p1p1Nppp/1p1q2b1/8/3P2P1/PQP3nP/5P2/3RR1K1 b - - 0 26");
        //board.DisplayBoard();
    }
}

