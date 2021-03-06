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
// reference : https://github.com/catchorg/Catch2/issues/850
// https://stackoverflow.com/questions/43762651/how-does-stdtie-work
// https://stackoverflow.com/questions/20705702/stl-pair-like-triplet-class-do-i-roll-my-own

void TestGeneratePieceLegalMoves(std::string fenPosition, int fileNum, int rankNum, int expect)
{

    Board board = Board();
    board.LoadFromFen(fenPosition);
    std::vector<std::string> generatedPieceMoves = Search::GeneratePieceLegalMoves(board, fileNum, rankNum);
    std::vector<std::string> generatedPieceMovesNoDuplicate = {};
    for (int i = 0; i < generatedPieceMoves.size(); i++)
    {
        if (std::find(generatedPieceMovesNoDuplicate.begin(), generatedPieceMovesNoDuplicate.end(), generatedPieceMoves.at(i)) == generatedPieceMovesNoDuplicate.end())
        {
            generatedPieceMovesNoDuplicate.push_back(generatedPieceMoves.at(i));
        }
        else
        {
            std::string errorMsg = std::string("duplicate moves when testing GenerateMoves function : ") + "\n" +
                                   generatedPieceMoves.at(i);
            throw std::invalid_argument(errorMsg);
        }
    }
    if (generatedPieceMoves.size() != expect)
    {
        Square sq = Square(fileNum, rankNum);
        printf("test cases failed \n");
        printf("fenPosition : %s \n On square: %s\n generated moves count: %zu \n", fenPosition.c_str(), sq.GetNotation().c_str(), generatedPieceMoves.size());
        printf("Generated moves : \n");
        for (int i = 0; i < generatedPieceMoves.size(); i++)
        {
            printf("move : %s\n", generatedPieceMoves.at(i).c_str());
        }
    }

    REQUIRE(generatedPieceMoves.size() == expect);
}

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
            // movedBoard.DisplayBoard();
        }
    }

    REQUIRE(generatedMoves.size() == expect);
}

void TestGenerateMoves(std::string fenPosition, PieceColors sideToMove, std::vector<std::string> expectedMoves)
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
    /*
    if (generatedMoves.size() != expectedMovebres)
    {
        printf("test cases failed \n");
        printf("fenPosition : %s \n side To Move : %s\n generated moves count: %zu \n", fenPosition.c_str(), ChessLib::GetPieceColorStr(sideToMove).c_str(), generatedMoves.size());
        printf("Generated moves : \n");
        for (int i = 0; i < generatedMoves.size(); i++)
        {

            printf("move : %s\n", generatedMoves.at(i).c_str());
            // movedBoard.DisplayBoard();
        }
    }
    */
    REQUIRE_THAT(generatedMoves, Catch::Matchers::UnorderedEquals(expectedMoves));
}
TEST_CASE("Test Generate Pieces Moves", "[TestGenerateMoves]")
{
    std::string fenPosition;
    int fileNum;
    int rankNum;
    int expect;

    std::tie(fenPosition, fileNum, rankNum, expect) = GENERATE(
        table<std::string, int, int, int>({
            // pawn endgame
            {"8/2p4p/2Pk2p1/6P1/5P2/8/6KP/8 w - - 1 2", 7, 2, 7}, // king legal moves
            {"8/2p4p/2Pk2p1/6P1/5P2/8/6KP/8 w - - 1 2", 8, 2, 2}, // pawn legal moves
            // queen vs  pawn
            {"8/8/8/8/6K1/6Q1/2p5/3k4 w - - 0 1", 7, 3, 18}, // queen legal moves
            // knight pawn vs  knight pawn
            {"8/1k6/8/2n5/p4N2/6K1/7P/8 w - - 0 1", 6, 4, 8}, // white knight legal moves
            {"8/1k6/8/2n5/p4N2/6KP/8/8 b - - 0 1", 3, 5, 6},  // black knight legal moves
            // bishop pawn vs  bishop pawn
            {"2b5/1k6/8/2B5/p6P/6K1/8/8 b - - 0 1", 3, 8, 5},  // black bishop legal moves
            {"8/1k1b4/8/2B5/p6P/6K1/8/8 w - - 1 2", 3, 5, 11}, // white bishop legal moves
            // rook endgame
            {"8/8/3rnk2/5p2/8/6P1/R4PK1/8 w - - 0 1", 1, 2, 11},  // white rook legal moves
            {"8/8/3rnk2/5p2/5P2/6P1/R5K1/8 b - - 0 1", 4, 6, 10}, // black rook legal moves
            // test generating moves even if it is not the current turn
            {"8/1k6/8/2n5/p4N2/6K1/7P/8 w - - 0 1", 3, 5, 6},     // black knight legal moves
            {"8/1k1b4/8/2B5/p6P/6K1/8/8 w - - 1 2", 4, 7, 8},     // black bishop legal moves
            {"8/8/3rnk2/5p2/5P2/6P1/R5K1/8 b - - 0 1", 1, 2, 12}, // white rook legal moves
            // move generation for promotion
            {"q7/1P6/8/8/8/2k2p1K/8/2bQ4 w - - 0 2", 2, 7, 8}, // white (can either take the black queen or not so legal moves should be 8)
            {"q7/1Q6/8/8/8/2k4K/5p2/2bQ4 b - - 1 3", 6, 2, 4}, // black
        }));

    SECTION("Test generating movements")
    {
        TestGeneratePieceLegalMoves(fenPosition, fileNum, rankNum, expect);
    }
}

TEST_CASE("Test Generate Moves", "[TestGenerateMoves]")
{
    std::string fenPosition;
    PieceColors sideToMove;
    int expect;

    std::tie(fenPosition, sideToMove, expect) = GENERATE(
        table<std::string, PieceColors, int>({
            // pawn endgame
            {"8/2p4p/2Pk2p1/6P1/5P2/8/6KP/8 w - - 1 2", PieceColors::white, 10},
            // queen vs  pawn
            {"8/8/8/8/6K1/6Q1/2p5/3k4 w - - 0 1", PieceColors::white, 25},
            // knight pawn vs  knight pawn
            {"8/1k6/8/2n5/p4N2/6K1/7P/8 w - - 0 1", PieceColors::white, 16},
            {"8/1k6/8/2n5/p4N1P/6K1/8/8 b - - 0 1", PieceColors::black, 15},
            // bishop pawn vs  bishop pawn
            {"2b5/1k6/8/2B5/p6P/6K1/8/8 b - - 0 1", PieceColors::black, 11},
            {"1k6/8/4b3/2B4P/8/4K3/8/n7 w - - 0 7", PieceColors::white, 17},
            // rook pawn vs  rook pawn
            {"1k4r1/8/8/p6P/8/4K3/2R5/8 w - - 0 7", PieceColors::white, 23},
            {"1k4r1/8/7P/p7/8/4K3/2R5/8 b - - 0 7", PieceColors::black, 16},
            {"3K4/r6p/5ppk/5P2/PR4PP/8/8/8 w - - 0 1", PieceColors::white, 17},
            // queen pawn vs queen pawn
            {"1k6/1q6/p7/p7/p5Q1/4K1PP/6PP/8 w - - 0 7", PieceColors::white, 26},
            {"1k6/1q6/p7/p7/p5QP/4K1P1/6PP/8 b - - 0 7", PieceColors::black, 24},
            // 3 pawn vs 3 pawn
            {"6k1/5ppp/8/8/8/8/5PPP/6K1 w - - 0 1", PieceColors::white, 8},
            // rook vs rook knight
            {"8/8/3rnk2/5p2/8/6P1/R4PK1/8 w - - 0 1", PieceColors::white, 20},
            // 2 bishops vs lone king
            {"4k3/8/8/8/8/8/8/2B1KB2 w - - 0 1", PieceColors::white, 18},
            // imbalanced endgame
            {"2r2k2/1p3ppp/p7/4p3/8/4BN2/1P3PPP/5K2 w - - 0 1", PieceColors::white, 25},
            // middle game of magnus and garry kasparov
            {"r1b2rk1/1pqn1ppp/2p2n2/p5B1/PbBP4/1NN5/1PQ2PPP/R4RK1 w - - 1 15", PieceColors::white, 53},
            {"4R3/2Q5/6R1/1K1B1N1P/3B4/3N4/P6P/1k6 w - - 0 1", PieceColors::white, 103},
            // only 1 move (block the rook with the bishop)
            {"2R3k1/5ppp/8/8/1b6/8/5PPP/6K1 b - - 0 1", PieceColors::black, 1},
            // test generating moves when pawns are promoting
            {"7r/1P6/8/8/8/7k/KR4p1/8 w - - 0 1", PieceColors::white, 18},
            {"7r/1P6/8/8/1R6/7k/K5p1/8 b - - 1 1", PieceColors::black, 17},
        }));

    SECTION("Test generating movements")
    {
        TestGenerateMoves(fenPosition, sideToMove, expect);
    }
}

TEST_CASE("Test Generate Algebraic Moves", "[TestGenerateMoves]")
{
    std::string fenPosition;
    PieceColors sideToMove;
    std::vector<std::string> expect;

    std::tie(fenPosition, sideToMove, expect) = GENERATE(
        table<std::string, PieceColors, std::vector<std::string>>({
            {
                "5R2/K5R1/8/8/7k/8/8/8 b - - 2 60",
                PieceColors::black,
                std::vector<std::string>{"h4h5", "h4h3"},
            },
        }));

    SECTION("Test generating movements")
    {
        TestGenerateMoves(fenPosition, sideToMove, expect);
    }
}
