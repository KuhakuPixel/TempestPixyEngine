#include "catch.hpp"
#include "../Src/board.h"
#include "../Src/stringHelper.h"
#include "../Src/chessLib.h"
#include <vector>
#include <string>

//reference : https://github.com/catchorg/Catch2/issues/850
//https://stackoverflow.com/questions/43762651/how-does-stdtie-work
//https://stackoverflow.com/questions/20705702/stl-pair-like-triplet-class-do-i-roll-my-own

void TestDoesPieceMoveCorrectly(std::string fenPosition, PieceColors sideToMove, std::string move, bool expect)
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

TEST_CASE("Test pawn legal moves", "[BoardLegalMoves]")
{
    std::string fenPosition;
    PieceColors sideToMove;
    std::string move;
    bool isMoveLegal;

    std::tie(fenPosition, sideToMove, move, isMoveLegal) = GENERATE(
        table<std::string, PieceColors, std::string, bool>({
            //test pawm normal movement

            {"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", PieceColors::white, "f2f4", true},
            {"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", PieceColors::white, "d2d3", true},
            {"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", PieceColors::white, "e4e3", false},
            {"rnbqkbnr/ppp1pppp/8/3p4/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2", PieceColors::black, "d5d4", true},
            {"r1bqkbnr/pppp2pp/2n5/4pp2/2BPP3/5N2/PPP2PPP/RNBQK2R b KQkq - 0 4", PieceColors::black, "f5f4", true},
            {"rnbqkbnr/pppp1ppp/8/4p3/4PP2/8/PPPP2PP/RNBQKBNR b KQkq - 0 2", PieceColors::black, "e5e6", false},
            //test capture
            {"r1bqkbnr/pppp2pp/2n5/4pp2/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 4", PieceColors::white, "e4f5", true},
            {"r1bqkbnr/pppp2pp/2n5/4pp2/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 4", PieceColors::white, "e4d5", false},
            {"rnbqkbnr/ppp1pppp/8/3p4/4PP2/8/PPPP2PP/RNBgQKBNR b KQkq - 0 2", PieceColors::black, "d5e4", true},
            {"rnbqkbnr/ppp1pppp/8/3p4/4PP2/8/PPPP2PP/RNBQKBNR b KQkq - 0 2", PieceColors::black, "d5c4", false},
            //test pawn can move 2 squares
            {"rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", PieceColors::white, "d2d4", true},
            {"rnbqkbnr/pp1ppppp/8/8/3pP3/8/PPP2PPP/RNBQKBNR w KQkq - 0 3", PieceColors::white, "e4e6", false},
            {"rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1", PieceColors::black, "e7e5", true},
            {"rnbqkbnr/ppp1pppp/8/3p4/4P3/7P/PPPP1PP1/RNBQKBNR b KQkq - 0 2", PieceColors::black, "d5d3", false},
            //test pawn movement blocked
            {"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", PieceColors::white, "e4e5", false},
            {"rnb1kbnr/pp1ppppp/8/2q5/2PpP3/3B4/PP3PPP/RNBQK1NR w KQkq - 3 5", PieceColors::white, "c4c5", false},
            {"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", PieceColors::black, "e5e4", false},
            {"rnb1kbnr/ppp1qppp/8/4p3/3NPP2/P2p2P1/1PPP3P/R1BQKBNR b KQkq - 1 7", PieceColors::black, "d3d2", false},
            //test pawn move backwards
        }));

    SECTION("Test pawn moves")
    {
        TestDoesPieceMoveCorrectly(fenPosition, sideToMove, move, isMoveLegal);
    }
}

