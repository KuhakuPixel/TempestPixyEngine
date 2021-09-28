#include "catch.hpp"
#include "../Src/board.h"
#include "../Src/stringHelper.h"
#include "../Src/analyzer.h"
#include "../Src/chessLib.h"
#include "../Src/search.h"
#include <vector>
#include <string>

//reference : https://github.com/catchorg/Catch2/issues/850
//https://stackoverflow.com/questions/43762651/how-does-stdtie-work
//https://stackoverflow.com/questions/20705702/stl-pair-like-triplet-class-do-i-roll-my-own

void TestGenerateMoves(std::string fenPosition, PieceColors sideToMove, int expect)
{

    Board board = Board();
    board.LoadFromFen(fenPosition);
    std::vector<std::string> generatedMoves = Search::GenerateMoves(board, sideToMove);
    if (generatedMoves.size() != expect)
    {
        printf("test cases failed \n");
        printf("fenPosition : %s \n side To Move : %s\n generated moves count: %zu \n", fenPosition.c_str(), ChessLib::GetPieceColorStr(sideToMove).c_str(), generatedMoves.size());
        printf("Generated moves : \n");
        for (int i = 0; i < generatedMoves.size(); i++)
        {
            Board movedBoard = Board();
            movedBoard.LoadFromFen(fenPosition);
            movedBoard.Move(generatedMoves.at(i));
            printf("move : %s\n", generatedMoves.at(i).c_str());
            printf("to \n");
            movedBoard.DisplayBoard();
        }
    }

    REQUIRE(generatedMoves.size() == expect);
}

TEST_CASE("Test Generate Moves", "[TestGenerateMoves]")
{
    std::string fenPosition;
    PieceColors sideToMove;
    int expect;

    std::tie(fenPosition, sideToMove, expect) = GENERATE(
        table<std::string, PieceColors, int>({
            //king pawn endgame
            {"8/2p4p/2Pk2p1/6P1/5P2/8/6KP/8 w - - 1 2", PieceColors::white, 10},
            //king queen vs king pawn
            {"8/8/8/8/6K1/6Q1/2p5/3k4 w - - 0 1", PieceColors::white, 25},
            //king knight pawn vs king knight pawn
            {"8/1k6/8/2n5/p4N2/6K1/7P/8 w - - 0 1", PieceColors::white, 16},
            {"8/1k6/8/2n5/p4N1P/6K1/8/8 b - - 0 1", PieceColors::black, 15},
            //king bishop pawn vs king bishop pawn
            {"2b5/1k6/8/2B5/p6P/6K1/8/8 b - - 0 1", PieceColors::black, 11},
            {"1k6/8/4b3/2B4P/8/4K3/8/n7 w - - 0 7", PieceColors::white, 17},

            //king rook pawn vs king rook pawn
            {"1k4r1/8/8/p6P/8/4K3/2R5/8 w - - 0 7", PieceColors::white, 23},
            {"1k4r1/8/7P/p7/8/4K3/2R5/8 b - - 0 7", PieceColors::black, 16},
            //king queen pawn vs king queen pawn
            {"1k6/1q6/p7/p7/p5Q1/4K1PP/6PP/8 w - - 0 7", PieceColors::white, 26},
            {"1k6/1q6/p7/p7/p5QP/4K1P1/6PP/8 b - - 0 7", PieceColors::black, 24},
            //middle game of magnus and garry kasparov
            {"r1b2rk1/1pqn1ppp/2p2n2/p5B1/PbBP4/1NN5/1PQ2PPP/R4RK1 w - - 1 15", PieceColors::white, 53}, //todo:count again the expected value
        }));

    SECTION("Test piece correct movements")
    {
        TestGenerateMoves(fenPosition, sideToMove, expect);
    }
}
