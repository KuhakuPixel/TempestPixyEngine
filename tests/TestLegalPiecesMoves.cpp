#include "catch.hpp"
#include "../Src/board.h"
#include "../Src/stringHelper.h"
#include "../Src/chessLib.h"
#include <vector>
#include <string>
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
}

TEST_CASE("Test bishop legal moves", "[BoardLegalMoves]")
{

    Board board = Board();
}
#pragma endregion
