#include "catch.hpp"
#include "../Src/board.h"
#include "../Src/stringHelper.h"
#include "../Src/analyzer.h"
#include "../Src/chessLib.h"
#include <vector>
#include <string>

//reference : https://github.com/catchorg/Catch2/issues/850
//https://stackoverflow.com/questions/43762651/how-does-stdtie-work
//https://stackoverflow.com/questions/20705702/stl-pair-like-triplet-class-do-i-roll-my-own

void TestDoesPieceMoveCorrectly(PieceName pieceName, PieceColors pieceColor, std::string move, bool expect)
{
    Square from = Square(1, 1);
    Square to = Square(1, 1);
    std::tie(from, to) = Square::GetMoveFromStr(move);

    bool actual = Analyzer::DoesPieceMoveCorrectly(pieceName, pieceColor, from, to);
    REQUIRE(actual == expect);
}

TEST_CASE("Test Piece correct movement", "[PiecesCorrectMovements]")
{
    PieceName pieceName;
    PieceColors pieceColor;
    std::string move;
    bool expect;

    std::tie(pieceName, pieceColor, move, expect) = GENERATE(
        table<PieceName, PieceColors, std::string, bool>({
            {PieceName::pawn, PieceColors::white, "e2e4", true},
            {PieceName::pawn, PieceColors::white, "e4e3", false},
            {PieceName::pawn, PieceColors::white, "e4e6", false},

            {PieceName::pawn, PieceColors::black, "e7e5", true},
            {PieceName::pawn, PieceColors::black, "e6e7", false},
            {PieceName::pawn, PieceColors::black, "e5e3", false},

            {PieceName::rook, PieceColors::white, "a1h1", true},
            {PieceName::rook, PieceColors::white, "a1b2", false},
        }));

    SECTION("Test pawn moves")
    {
        TestDoesPieceMoveCorrectly(pieceName, pieceColor, move, expect);
    }
}
