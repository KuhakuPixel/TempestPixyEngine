#include "catch.hpp"
#include "../Src/board.h"
#include "../Src/stringHelper.h"
#include "../Src/analyzer.h"
#include "../Src/chessLib.h"
#include "../Src/search.h"
#include <vector>
#include <string>
#include <algorithm>
#include <exception>
//reference : https://github.com/catchorg/Catch2/issues/850
//https://stackoverflow.com/questions/43762651/how-does-stdtie-work
//https://stackoverflow.com/questions/20705702/stl-pair-like-triplet-class-do-i-roll-my-own

void TestGenerateMoves(std::string fenPosition, PieceColors sideToMove, int expect)
{

    Board board = Board();
    board.LoadFromFen(fenPosition);
    std::vector<std::string> generatedMoves = Search::GenerateMoves(board, sideToMove);
    std::vector<std::string> generatedMovesNoDuplicate = {};
    for (int i = 0; i < generatedMoves.size(); i++)
    {
        if (std::find(generatedMovesNoDuplicate.begin(), generatedMovesNoDuplicate.end(), generatedMoves.at(i)) == generatedMovesNoDuplicate.end())
        {
            generatedMovesNoDuplicate.push_back(generatedMoves.at(i));
        }
        else
        {
            std::string errorMsg = std::string("duplicate moves when testing GenerateMoves function : ") + "\n" +
                                   generatedMoves.at(i);
            throw std::invalid_argument(errorMsg);
        }
    }
    if (generatedMoves.size() != expect)
    {
        printf("test cases failed \n");
        printf("fenPosition : %s \n side To Move : %s\n generated moves count: %zu \n", fenPosition.c_str(), ChessLib::GetPieceColorStr(sideToMove).c_str(), generatedMoves.size());
        printf("Generated moves : \n");
        for (int i = 0; i < generatedMoves.size(); i++)
        {
            /*
            Board movedBoard = Board();
            movedBoard.LoadFromFen(fenPosition);
            movedBoard.Move(generatedMoves.at(i));
            */
            printf("move : %s\n", generatedMoves.at(i).c_str());
            //movedBoard.DisplayBoard();
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
            //pawn endgame
            {"8/2p4p/2Pk2p1/6P1/5P2/8/6KP/8 w - - 1 2", PieceColors::white, 10},
            //queen vs  pawn
            {"8/8/8/8/6K1/6Q1/2p5/3k4 w - - 0 1", PieceColors::white, 25},
            //knight pawn vs  knight pawn
            {"8/1k6/8/2n5/p4N2/6K1/7P/8 w - - 0 1", PieceColors::white, 16},
            {"8/1k6/8/2n5/p4N1P/6K1/8/8 b - - 0 1", PieceColors::black, 15},
            //bishop pawn vs  bishop pawn
            {"2b5/1k6/8/2B5/p6P/6K1/8/8 b - - 0 1", PieceColors::black, 11},
            {"1k6/8/4b3/2B4P/8/4K3/8/n7 w - - 0 7", PieceColors::white, 17},
            //rook pawn vs  rook pawn
            {"1k4r1/8/8/p6P/8/4K3/2R5/8 w - - 0 7", PieceColors::white, 23},
            {"1k4r1/8/7P/p7/8/4K3/2R5/8 b - - 0 7", PieceColors::black, 16},
            {"3K4/r6p/5ppk/5P2/PR4PP/8/8/8 w - - 0 1", PieceColors::white, 17},
            //queen pawn vs queen pawn
            {"1k6/1q6/p7/p7/p5Q1/4K1PP/6PP/8 w - - 0 7", PieceColors::white, 26},
            {"1k6/1q6/p7/p7/p5QP/4K1P1/6PP/8 b - - 0 7", PieceColors::black, 24},
            //3 pawn vs 3 pawn
            {"6k1/5ppp/8/8/8/8/5PPP/6K1 w - - 0 1", PieceColors::white, 8},
            //rook vs rook knight
            {"8/8/3rnk2/5p2/8/6P1/R4PK1/8 w - - 0 1", PieceColors::white, 20},
            //2 bishops vs lone king
            {"4k3/8/8/8/8/8/8/2B1KB2 w - - 0 1", PieceColors::white, 18},
            //imbalanced endgame
            {"2r2k2/1p3ppp/p7/4p3/8/4BN2/1P3PPP/5K2 w - - 0 1", PieceColors::white, 25},
            //middle game of magnus and garry kasparov
            {"r1b2rk1/1pqn1ppp/2p2n2/p5B1/PbBP4/1NN5/1PQ2PPP/R4RK1 w - - 1 15", PieceColors::white, 53},
            {"4R3/2Q5/6R1/1K1B1N1P/3B4/3N4/P6P/1k6 w - - 0 1", PieceColors::white, 103},
            //only 1 move (block the rook with the bishop)
            {"2R3k1/5ppp/8/8/1b6/8/5PPP/6K1 b - - 0 1", PieceColors::black, 1},
        }));

    SECTION("Test generating movements")
    {
        TestGenerateMoves(fenPosition, sideToMove, expect);
    }
}
