#include "catch.hpp"
#include "../Src/board.h"
#include "../Src/stringHelper.h"
#include "../Src/chessLib.h"
#include <vector>
#include <string>

//reference : https://github.com/catchorg/Catch2/issues/850
//https://stackoverflow.com/questions/43762651/how-does-stdtie-work
//https://stackoverflow.com/questions/20705702/stl-pair-like-triplet-class-do-i-roll-my-own

void TestPiecesLegalMove(std::string fenPosition, PieceColors sideToMove, std::string move, bool expect)
{
    Board board = Board();
    board.LoadFromFen(fenPosition);
    bool actual = board.IsMoveLegal(sideToMove, move);
    if (actual != expect)
    {
        printf("test cases failed \n");
    }
    REQUIRE(actual == expect);
}
#pragma region Test Legal moves
TEST_CASE("Test Pawn legal moves", "[BoardLegalMoves]")
{

    Board board = Board();
#pragma region TestWhitePawn
#pragma region Test legal moves
    SECTION("TestIsMoveLegalPawnWhite0")
    {
        bool actual = board.IsMoveLegal(PieceColors::white, "e2e5");
        REQUIRE(actual == false);
    }
    SECTION("TestIsMoveLegalPawnWhite1")
    {
        bool actual = board.IsMoveLegal(PieceColors::white, "e2e4");
        REQUIRE(actual == true);
    }
    SECTION("TestIsMoveLegalPawnWhite2")
    {
        board.Move("e2e4");
        board.Move("e7e5");
        bool actual = board.IsMoveLegal(PieceColors::white, "e2e3");
        REQUIRE(actual == false);
    }
    SECTION("TestIsMoveLegalPawnWhite3")
    {
        board.Move("e2e4");
        board.Move("e7e5");
        bool actual = board.IsMoveLegal(PieceColors::white, "e4e6");
        REQUIRE(actual == false);
    }
    SECTION("TestIsMoveLegalPawnWhite4")
    {
        board.Move("e2e4");
        board.Move("e7e5");
        bool actual = board.IsMoveLegal(PieceColors::white, "e4e3");
        REQUIRE(actual == false);
    }
    SECTION("TestIsMoveLegalPawnWhite5")
    {
        board.Move("e2e4");
        board.Move("e7e5");
        bool actual = board.IsMoveLegal(PieceColors::white, "e4e5");
        REQUIRE(actual == false);
    }
#pragma endregion

#pragma region TestCapture
    SECTION("TestPawnCaptureWhiteCaptureEnemy")
    {
        board.LoadFromFen("rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2");
        bool actual = board.IsMoveLegal(PieceColors::white, "e4d5");
        REQUIRE(actual == true);
    }
    SECTION("TestPawnCaptureWhiteCaptureEmptySquares")
    {
        board.LoadFromFen("rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2");
        bool actual = board.IsMoveLegal(PieceColors::white, "e4f5");
        REQUIRE(actual == false);
    }
    SECTION("TestPawnCaptureWhiteCaptureFriendlyPawn")
    {
        board.LoadFromFen("rnbqkbnr/ppp2ppp/8/3pp3/4P3/3P4/PPP2PPP/RNBQKBNR w KQkq - 0 3");

        bool actual = board.IsMoveLegal(PieceColors::white, "d3e4");
        REQUIRE(actual == false);
    }
    SECTION("TestPawnCaptureWhiteCaptureFriendlyQueen")
    {
        board.LoadFromFen("rnbqkb1r/2pppppp/p7/1p1P4/3Q2n1/4P3/PPP2PPP/RNB1KBNR w KQkq - 2 5");

        bool actual = board.IsMoveLegal(PieceColors::white, "e3d4");
        REQUIRE(actual == false);
    }
    SECTION("TestPawnCaptureWhiteCaptureKnight")
    {
        board.LoadFromFen("r1bqkbnr/pppppppp/8/2n5/3PP3/8/PPP2PPP/RNBQKBNR w KQkq - 1 3");

        bool actual = board.IsMoveLegal(PieceColors::white, "d4c5");
        REQUIRE(actual == true);
    }
#pragma endregion
#pragma endregion

#pragma region TestBlackPawn

#pragma region Test legal moves
    SECTION("TestIsMoveLegalPawnBlack0")
    {
        board.Move("e2e4");
        bool actual = board.IsMoveLegal(PieceColors::black, "e7e4");
        REQUIRE(actual == false);
    }
    SECTION("TestIsMoveLegalPawnBlack1")
    {
        board.Move("e2e4");
        bool actual = board.IsMoveLegal(PieceColors::black, "e7e5");
        REQUIRE(actual == true);
    }
    SECTION("TestIsMoveLegalPawnBlack2")
    {
        board.Move("e2e4");
        board.Move("e7e5");
        board.Move("b1c3");
        bool actual = board.IsMoveLegal(PieceColors::white, "e7e6");
        REQUIRE(actual == false);
    }
    SECTION("TestIsMoveLegalPawnBlack3")
    {
        board.Move("e2e4");
        board.Move("e7e5");
        board.Move("b1c3");
        bool actual = board.IsMoveLegal(PieceColors::white, "e5e4");
        REQUIRE(actual == false);
    }
    SECTION("TestIsMoveLegalPawnBlack4")
    {
        board.Move("e2e4");
        board.Move("e7e5");
        board.Move("b1c3");
        bool actual = board.IsMoveLegal(PieceColors::white, "e5e6");
        REQUIRE(actual == false);
    }
#pragma endregion

#pragma region TestCapture
    SECTION("TestPawnCaptureBlackCaptureEnemy")
    {
        board.LoadFromFen("rnbqkbnr/pp2pppp/2p5/3P4/3P4/8/PPP2PPP/RNBQKBNR b KQkq - 0 3");
        bool actual = board.IsMoveLegal(PieceColors::black, "c6d5");
        REQUIRE(actual == true);
    }
    SECTION("TestPawnCaptureBlackCaptureEmptySquares")
    {
        board.LoadFromFen("rnbqkbnr/pp2pppp/2p5/3P4/3P4/8/PPP2PPP/RNBQKBNR b KQkq - 0 3");
        bool actual = board.IsMoveLegal(PieceColors::black, "c6b5");
        REQUIRE(actual == false);
    }
    SECTION("TestPawnCaptureBlackCaptureFriendlyPawn")
    {
        board.LoadFromFen("rnbqkbnr/pp2pppp/2p5/3pP3/3P4/8/PPP2PPP/RNBQKBNR b KQkq - 0 3");

        bool actual = board.IsMoveLegal(PieceColors::black, "c6d5");
        REQUIRE(actual == false);
    }
    SECTION("TestPawnCaptureWhiteCaptureFriendlyQueen")
    {
        board.LoadFromFen("rnb1kbnr/pB2pppp/2p5/3qP3/3p4/P7/1PPP1PPP/RNBQK1NR b KQkq - 0 5");

        bool actual = board.IsMoveLegal(PieceColors::black, "c6d5");
        REQUIRE(actual == false);
    }
    SECTION("TestPawnCaptureWhiteCaptureKnight")
    {
        board.LoadFromFen("r1b1kbnr/pB1npppp/2p5/3qP3/3p4/P1N5/1PPP1PPP/R1BQK1NR b KQkq - 2 6");

        bool actual = board.IsMoveLegal(PieceColors::black, "d4c3");
        REQUIRE(actual == true);
    }
#pragma endregion
#pragma endregion
}

#pragma endregion

TEST_CASE("Test bishop legal moves", "[BoardLegalMoves]")
{

    Board board = Board();

    std::string fenPosition;
    PieceColors sideToMove;
    std::string move;
    bool isMoveLegal;

    std::tie(fenPosition, sideToMove, move, isMoveLegal) = GENERATE(
        table<std::string, PieceColors, std::string, bool>({
            //test if bishop is blocked
            {"rnbqkbnr/ppp1pppp/8/8/3pP3/3P4/PPP2PPP/RNBQKBNR w KQkq - 0 3", PieceColors::white, "f1c4", false},
            {"rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", PieceColors::white, "f1h3", false},
            {"rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", PieceColors::black, "f8c5", false},
            {"rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", PieceColors::black, "c8e6", false},
            //test capture
            {"rnbqkbnr/p1p1pppp/8/1p1p4/4P3/7P/PPPP1PP1/RNBQKBNR w KQkq - 0 3", PieceColors::white, "f1b5", true},
            {"rnbqkbnr/1pppp2p/p4pp1/8/8/1P3N2/PBPPPPPP/RN1QKB1R w KQkq - 0 4", PieceColors::white, "b2f6", true},
            {"rn1qkbnr/pbpppppp/1p6/8/3PP3/8/PPP1NPPP/RNBQKB1R b KQkq - 2 3", PieceColors::black, "b7e4", true},
            {"rnbqk1nr/ppppppbp/6p1/8/2P1P3/1P6/P2P1PPP/RNBQKBNR b KQkq - 0 3", PieceColors::black, "g7a1", true},
        }));

    SECTION("Test Bishops moves")
    {
        TestPiecesLegalMove(fenPosition, sideToMove, move, isMoveLegal);
    }
}