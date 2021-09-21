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
    if (actual != expect)
    {
        printf("test cases failed \n");
        printf("pieceName:%s , pieceColor:%s , move:%s ,",
               ChessLib::GetPieceNameStr(pieceName).c_str(),
               ChessLib::GetPieceColorStr(pieceColor).c_str(),
               move.c_str());
    }
    REQUIRE(actual == expect);
}

void TestIsPieceMovementBlocked(std::string fenPosition, PieceName pieceName, PieceColors sideToMove, std::string move, bool expect)
{
    Board board = Board();
    board.LoadFromFen(fenPosition);
    bool actual = board.IsMoveLegal(sideToMove, move);
    if (actual != expect)
    {
        printf("test cases failed \n");
        printf("fenPosition : %s \n move: %s\n", fenPosition.c_str(), move.c_str());
    }
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
            //pawn
            {PieceName::pawn, PieceColors::white, "e2e4", true},
            {PieceName::pawn, PieceColors::white, "e2e3", true},
            {PieceName::pawn, PieceColors::white, "e4d5", true},
            {PieceName::pawn, PieceColors::white, "e4e3", false},
            {PieceName::pawn, PieceColors::white, "e4e6", false},

            {PieceName::pawn, PieceColors::black, "e7e5", true},
            {PieceName::pawn, PieceColors::black, "e7e6", true},
            {PieceName::pawn, PieceColors::black, "e5d4", true},
            {PieceName::pawn, PieceColors::black, "e6e7", false},
            {PieceName::pawn, PieceColors::black, "e5e3", false},

            //rook
            {PieceName::rook, PieceColors::white, "a1h1", true},
            {PieceName::rook, PieceColors::white, "h3a3", true},
            {PieceName::rook, PieceColors::white, "a1a8", true},
            {PieceName::rook, PieceColors::white, "b3b8", true},
            {PieceName::rook, PieceColors::white, "c8b6", false},
            {PieceName::rook, PieceColors::white, "a1b2", false},

            {PieceName::rook, PieceColors::black, "a1h1", true},
            {PieceName::rook, PieceColors::black, "h3a3", true},
            {PieceName::rook, PieceColors::black, "a1a8", true},
            {PieceName::rook, PieceColors::black, "b3b8", true},
            {PieceName::rook, PieceColors::black, "c8b6", false},
            {PieceName::rook, PieceColors::black, "a1b2", false},

            //knight
            {PieceName::knight, PieceColors::white, "b1c3", true},
            {PieceName::knight, PieceColors::white, "b2a4", true},
            {PieceName::knight, PieceColors::white, "e5d7", true},
            {PieceName::knight, PieceColors::white, "b2b4", false},
            {PieceName::knight, PieceColors::white, "a2b3", false},
            {PieceName::knight, PieceColors::white, "a4b4", false},

            {PieceName::knight, PieceColors::black, "b1c3", true},
            {PieceName::knight, PieceColors::black, "b2a4", true},
            {PieceName::knight, PieceColors::black, "e5d7", true},
            {PieceName::knight, PieceColors::black, "b2b4", false},
            {PieceName::knight, PieceColors::black, "a2b3", false},
            {PieceName::knight, PieceColors::black, "a4b4", false},

            //bishop
            {PieceName::bishop, PieceColors::white, "c1b2", true},
            {PieceName::bishop, PieceColors::white, "c1d2", true},
            {PieceName::bishop, PieceColors::white, "d3c2", true},
            {PieceName::bishop, PieceColors::white, "d4c2", false},
            {PieceName::bishop, PieceColors::white, "c4f3", false},
            {PieceName::bishop, PieceColors::white, "c5d5", false},

            {PieceName::bishop, PieceColors::black, "c1b2", true},
            {PieceName::bishop, PieceColors::black, "c1d2", true},
            {PieceName::bishop, PieceColors::black, "d3c2", true},
            {PieceName::bishop, PieceColors::black, "d4c2", false},
            {PieceName::bishop, PieceColors::black, "c4f3", false},
            {PieceName::bishop, PieceColors::black, "c5d5", false},
            //queen

            {PieceName::queen, PieceColors::white, "d1d2", true},
            {PieceName::queen, PieceColors::white, "d1c2", true},
            {PieceName::queen, PieceColors::white, "d1h5", true},
            {PieceName::queen, PieceColors::white, "d1c3", false},
            {PieceName::queen, PieceColors::white, "a1b4", false},
            {PieceName::queen, PieceColors::white, "c3h4", false},

            {PieceName::queen, PieceColors::black, "d1d2", true},
            {PieceName::queen, PieceColors::black, "d1c2", true},
            {PieceName::queen, PieceColors::black, "d1h5", true},
            {PieceName::queen, PieceColors::black, "d1c3", false},
            {PieceName::queen, PieceColors::black, "a1b4", false},
            {PieceName::queen, PieceColors::black, "c3h4", false},
            //king
            {PieceName::king, PieceColors::white, "e1e2", true},
            {PieceName::king, PieceColors::white, "e1d2", true},
            {PieceName::king, PieceColors::white, "e3d2", true},
            {PieceName::king, PieceColors::white, "e1e3", false},
            {PieceName::king, PieceColors::white, "e1g3", false},
            {PieceName::king, PieceColors::white, "e1d3", false},
        }));

    SECTION("Test piece correct movements")
    {
        TestDoesPieceMoveCorrectly(pieceName, pieceColor, move, expect);
    }
}
