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
