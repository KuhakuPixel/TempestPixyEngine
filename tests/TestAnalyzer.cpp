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

void TestIsPieceMovementBlocked(std::string fenPosition, std::string move, bool expect)
{
    Board board = Board();
    board.LoadFromFen(fenPosition);
    Square from = Square(1, 1);
    Square to = Square(1, 1);
    std::tie(from, to) = Square::GetMoveFromStr(move);

    bool actual = Analyzer::IsPieceMovementBlocked(board, from, to);
    if (actual != expect)
    {
        printf("test cases failed \n");
        printf("fenPosition : %s \n move: %s\n", fenPosition.c_str(), move.c_str());
    }
    REQUIRE(actual == expect);
}

void TestIsSquareUnderAttack(std::string fenPosition, std::string square, PieceColors attackingColor, bool expect)
{
    Board board = Board();
    board.LoadFromFen(fenPosition);
    bool actual = Analyzer::IsSquareAttacked(board, attackingColor, Square(square));
    if (actual != expect)
    {
        printf("test cases failed \n");
        printf("fenPosition : %s \n square: %s\n attackingColor: %s\n", fenPosition.c_str(), square.c_str(), ChessLib::GetPieceColorStr(attackingColor).c_str());
    }
    REQUIRE(actual == expect);
}

void TestGetGameResult(std::string fenPosition, PieceColors sideToMove, GameResult expect)
{
    Board board = Board();
    board.LoadFromFen(fenPosition);
    GameResult actual = Analyzer::GetGameResult(board, sideToMove);
    if (actual != expect)
    {
        printf("test cases failed \n");
        printf("fenPosition : %s \n sideToMove: %s\n actual:%s \n expect:%s",
               fenPosition.c_str(),
               ChessLib::GetPieceColorStr(sideToMove).c_str(),
               ChessLib::GetGameResultStr(actual).c_str(),
               ChessLib::GetGameResultStr(expect).c_str());
    }
    REQUIRE(actual == expect);
}
void TestGetDefendedPiecesCount(std::string fenPosition, PieceColors side, int expect)
{
    Board board = Board();
    board.LoadFromFen(fenPosition);
    int actual = Analyzer::GetDefendedPiecesCount(board, side);
    if (actual != expect)
    {
        printf("TestGetDefendedPiecesCount test cases failed \n");
        printf("fenPosition : %s \n side : %s\n actual:%d \n expect:%d",
               fenPosition.c_str(),
               ChessLib::GetPieceColorStr(side).c_str(),
               actual,
               expect);
    }
    REQUIRE(actual == expect);
}
void TestGetHangingPiecesCount(std::string fenPosition, PieceColors side, int expect)
{
    Board board = Board();
    board.LoadFromFen(fenPosition);
    int actual = Analyzer::GetHangingPiecesCount(board, side);
    if (actual != expect)
    {
        printf("TestGetHangingPiecesCount test cases failed \n");
        printf("fenPosition : %s \n side : %s\n actual:%d \n expect:%d",
               fenPosition.c_str(),
               ChessLib::GetPieceColorStr(side).c_str(),
               actual,
               expect);
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

TEST_CASE("Test Is Piece Movement Blocked", "[PiecesCorrectMovements]")
{
    std::string fenPosition;
    std::string move;
    bool expect;

    std::tie(fenPosition, move, expect) = GENERATE(
        table<std::string, std::string, bool>({
            //bishops
            {"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", "f1d3", true},
            {"rnbqkbnr/pppp1ppp/8/4p3/8/4P3/PPPP1PPP/RNBQKBNR w KQkq - 0 2", "f1d3", false}, //e3e5 (van'tkruijs)
            {"rnbqkbnr/pppp1ppp/8/4p3/8/4P3/PPPP1PPP/RNBQKBNR w KQkq - 0 2", "c1f4", true},
            {"rnbqkbnr/pppp1ppp/8/8/3P4/8/PPP2PPP/RNBQKBNR b KQkq - 0 3", "c8g4", true},
            {"rnbqkbnr/ppp2ppp/8/3p4/3P4/2N5/PPP2PPP/R1BQKBNR b KQkq - 1 4", "c8e6", false},
            {"rnbq1bnr/ppp1kppp/8/3p4/3P2Q1/2N5/PPP2PPP/R1B1KBNR b KQ - 3 5", "f8d6", true},

            //rook
            {"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", "a1a3", true},
            {"r1b1k2r/ppp1qp2/3p1npp/8/4P3/2NPQ3/PPP1B1PP/2KR3R w kq - 0 12", "d1d6", true},
            {"r1b1k2r/ppp1qp2/3p1npp/8/4P3/2NPQ3/PPP1B1PP/2KR3R w kq - 0 12", "h1f1", false},
            {"r1b1k2r/1pp1qp2/p2p1npp/8/4P3/2NPQ3/PPP1B1PP/2KR1R2 w kq - 0 13", "f1f6", false},
            {"r1b1k2r/1pp1qp2/p2p1npp/8/4P3/2NPQ3/PPP1B1PP/2KR1R2 w kq - 0 13", "f1f7", true},
            {"r3k2r/ppp1qp2/3p1np1/8/4PRbp/2NPQ3/PPP1B1PP/2K1R3 w kq - 0 15", "f4f7", true},

            //queen
            {"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", "d1b3", true},
            {"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", "d1d3", true},
            {"r3kbnr/pppqpppp/2n5/3p1b2/3P1B2/4PN2/PPP2PPP/RN1QKB1R w KQkq - 1 5", "d1d5", true},
            {"r3kbnr/pppqpppp/8/3p1b2/P2n1B2/4PN2/1PP2PPP/RN1QKB1R w KQkq - 0 6", "d1d4", false},
            {"r3kbnr/pppqpppp/8/3p1b2/P2n1B2/4PN2/1PP2PPP/RN1QKB1R w KQkq - 0 6", "d1e2", false},
            {"r3kbnr/pppqpppp/8/3p1b2/P1Pn1B2/4PN2/1P3PPP/RN1QKB1R b KQkq - 0 6", "d1d3", false},

            //pawns
            {"rnbqkbnr/ppppp1pp/8/4P3/8/N4p2/PPPP1PPP/R1BQKBNR w KQkq - 0 4", "f2f3", true},
            {"rnbqkbnr/ppppp1pp/8/4P3/8/N4p2/PPPP1PPP/R1BQKBNR w KQkq - 0 4", "f2f4", true},
            {"r2qkbnr/ppp1pppp/2n5/3p1b2/3P1B2/5N2/PPP1PPPP/RN1QKB1R w KQkq - 4 4", "e2e4", false},
            //king
            {"r2qkbnr/ppp1ppp1/2n5/3p1b1p/3P1B2/5N2/PPPKPPPP/RN1Q1B1R w kq - 0 5", "d2d1", true},
            {"r2qkbnr/ppp1ppp1/2n5/3p1b1p/3P1B2/5N2/PPPKPPPP/RN1Q1B1R w kq - 0 5", "d2c2", true},
            {"r2qkbnr/ppp1ppp1/2n5/3p1b1p/3P1B2/5N2/PPPKPPPP/RN1Q1B1R w kq - 0 5", "d2e2", true},
            {"r2qkbnr/ppp1ppp1/2n5/3p1b1p/3P1B2/5N2/PPPKPPPP/RN1Q1B1R w kq - 0 5", "d2c3", false},
            {"r2qkbnr/ppp1ppp1/2n5/3p1b1p/3P1B2/5N2/PPPKPPPP/RN1Q1B1R w kq - 0 5", "d2d3", false},
            //knight
            {"rn1qkb1r/pp2pppp/2p2nb1/8/3P1P2/6N1/PPP3PP/R1BQKBNR b KQkq - 0 7", "f6h5", false},
            {"rn1qkb1r/pp2pppp/2p2nb1/8/3P1P2/6N1/PPP3PP/R1BQKBNR b KQkq - 0 7", "f6g4", false},
            {"rn1qkb1r/pp2pppp/2p2nb1/8/3P1P2/6N1/PPP3PP/R1BQKBNR b KQkq - 0 7", "f6h7", true},
            {"rn1qkb1r/pp2pppp/2p2nb1/8/3P1P2/6N1/PPP3PP/R1BQKBNR b KQkq - 0 7", "f6e8", true},
        }));

    SECTION("Test piece correct movements")
    {
        TestIsPieceMovementBlocked(fenPosition, move, expect);
    }
}

TEST_CASE("Test Is Square under attack", "[IsSquareAttacked]")
{
    std::string fenPosition;
    std::string square;
    PieceColors attackingColor;
    bool isSquareAttacked;

    std::tie(fenPosition, square, attackingColor, isSquareAttacked) = GENERATE(
        table<std::string, std::string, PieceColors, bool>({
            {"rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", "d4", PieceColors::black, true},
            {"rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", "c6", PieceColors::black, true},
            {"rnbqkbnr/pp1pp1pp/8/2p2p2/4P3/2N5/PPPP1PPP/R1BQKBNR w KQkq - 0 3", "e4", PieceColors::black, true},
            {"rnbqkbnr/pppp1p1p/8/4P1p1/5p2/2N2N2/PPPP2PP/R1BQKB1R w KQkq - 0 6", "d6", PieceColors::white, true},
            {"rnbqkbnr/pppp1p1p/8/4P1p1/5p2/2N2N2/PPPP2PP/R1BQKB1R w KQkq - 0 6", "f6", PieceColors::white, true},
            {"r1bqkbnr/pppp1p1p/2n5/4P1p1/5p1P/2N5/PPPP2P1/R1BQKBNR b KQkq - 0 7", "g5", PieceColors::white, true},
            {"rnb2bnr/pp1p1ppp/8/2p1p1k1/4P1q1/8/PPPP1P1P/RNBQKB2 w - - 2 16", "h3", PieceColors::white, true},
            {"rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", "a3", PieceColors::white, true},
            {"rnbqkbnr/pp1ppppp/8/2p5/2B1P3/8/PPPP1PPP/RNBQK1NR b KQkq - 1 2", "a3", PieceColors::white, true},
            {"rnbqkbnr/pp1ppppp/8/2p5/2B1P3/8/PPPP1PPP/RNBQK1NR b KQkq - 1 2", "a3", PieceColors::white, true},
            {"rnb2bnr/pp1p1ppp/8/2p1p1k1/4P1q1/8/PPPP1P1P/RNBQKB2 w - - 2 16", "c4", PieceColors::white, true},

            {"rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", "d5", PieceColors::black, false},
            {"rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1", "e5", PieceColors::black, false},
            {"rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", "d4", PieceColors::white, false},
            {"rnbqkbnr/pppp1p1p/8/4P1p1/5p2/2N2N2/PPPP2PP/R1BQKB1R w KQkq - 0 6", "e6", PieceColors::white, false},
            {"rnbqkbnr/pppp1p1p/8/4P1p1/5p2/2N2N2/PPPP2PP/R1BQKB1R w KQkq - 0 6", "e6", PieceColors::white, false},
            {"1r6/6p1/b4pk1/P7/1B3K2/5P2/6P1/7R w - - 2 46", "e6", PieceColors::white, false},
            {"1r6/6p1/b4pk1/P7/1B3K2/5P2/6P1/7R w - - 2 46", "b5", PieceColors::white, false},
            {"1r6/6p1/b4pk1/P7/1B3K2/5P2/6P1/7R w - - 2 46", "c8", PieceColors::white, false},
            {"1r6/6p1/b4pk1/P7/1B3K2/5P2/6P1/7R w - - 2 46", "b3", PieceColors::black, false},
            {"1r6/6p1/b4pk1/P7/1B3K2/5P2/6P1/7R w - - 2 46", "c7", PieceColors::black, false},

        }));

    SECTION("Test piece correct movements")
    {
        TestIsSquareUnderAttack(fenPosition, square, attackingColor, isSquareAttacked);
    }
}

TEST_CASE("Test Get Game Result", "[GetGameResult]")
{
    std::string fenPosition;
    PieceColors sideToMove;
    GameResult gameResult;

    std::tie(fenPosition, sideToMove, gameResult) = GENERATE(
        table<std::string, PieceColors, GameResult>({
            //check mate by queen
            {"4k3/4Q3/4K3/8/8/8/8/8 b - - 0 1", PieceColors::black, GameResult::whiteWins},
            //mate by rook
            {"4k1R1/8/4K3/8/8/8/8/8 b - - 0 1", PieceColors::black, GameResult::whiteWins},
            //mate by 2 bishops
            {"4k3/2K5/3B2B1/8/8/8/8/8 b - - 0 1", PieceColors::black, GameResult::whiteWins},
            //mate in middle game
            {"r5kr/4qp1p/p4p1B/1pp5/8/1PPP2R1/1P3PPP/R5K1 b - - 1 4", PieceColors::black, GameResult::whiteWins},
            //mate by back rank
            {"1R4k1/5ppp/8/8/8/8/5PPP/6K1 b - - 0 3", PieceColors::black, GameResult::whiteWins},
            //stalemate
            {"k7/2Q5/8/6K1/8/8/8/8 b - - 0 1", PieceColors::black, GameResult::stalemate},
            {"4k3/4P3/4K3/8/8/8/8/8 b - - 0 1", PieceColors::black, GameResult::stalemate},
            //king is in check but not over
            {"4k3/4Q3/8/8/8/8/1P6/7K b - - 0 1", PieceColors::black, GameResult::ongoing},                               //black king can still takes queen
            {"r1bqkbnr/pppp1Qpp/2n5/4p3/4P3/8/PPPP1PPP/RNB1KBNR b KQkq - 0 3", PieceColors::black, GameResult::ongoing}, //black king can still takes queen
            {"2R3k1/5ppp/8/8/1b6/8/5PPP/6K1 b - - 0 1", PieceColors::black, GameResult::ongoing},                        //backrank check but can be blocked by bishops

        }));

    SECTION("Test piece correct movements")
    {
        TestGetGameResult(fenPosition, sideToMove, gameResult);
    }
}
TEST_CASE("Test Get Defended Pieces count", "[GetDefendedPiecesCount]")
{
    std::string fenPosition;
    PieceColors side;
    int defendedPiecesCount;

    std::tie(fenPosition, side, defendedPiecesCount) = GENERATE(
        table<std::string, PieceColors, int>({
            //opening
            {"rnbqkbnr/pppp1ppp/8/4p3/4P3/2N5/PPPP1PPP/R1BQKBNR b KQkq - 1 2", PieceColors::white, 14},
            {"rnbqkbnr/pppp1ppp/8/4p3/4P3/2N5/PPPP1PPP/R1BQKBNR b KQkq - 1 2", PieceColors::black, 13},
            //middle game
            {"3rr1k1/1np2qpp/1p2bp2/pPn1p3/P3P3/B1P1N2P/2B2PP1/RQ2R1K1 b - - 9 26", PieceColors::white, 13},
            {"3rr1k1/1np2qpp/1p2bp2/pPn1p3/P3P3/B1P1N2P/2B2PP1/RQ2R1K1 b - - 9 26", PieceColors::black, 14},
            //end game
            {"8/1R6/1p3kp1/N1n1p3/8/1r6/4K3/8 w - - 1 78", PieceColors::white, 1},
            {"8/1R6/1p3kp1/N1n1p3/8/1r6/4K3/8 w - - 1 78", PieceColors::black, 5},
        }));

    SECTION("Test piece correct movements")
    {
        TestGetDefendedPiecesCount(fenPosition, side, defendedPiecesCount);
    }
}
TEST_CASE("Test Get hanging Pieces count", "[GetHangingPiecesCount]")
{
    std::string fenPosition;
    PieceColors side;
    int defendedPiecesCount;

    std::tie(fenPosition, side, defendedPiecesCount) = GENERATE(
        table<std::string, PieceColors, int>({
            //opening
            {"rnbqk2r/pppp1ppp/4pn2/8/1bPP4/2N5/PP2PPPP/R1BQKBNR w KQkq - 2 4", PieceColors::white, 3},
            {"rnbqk2r/pppp1ppp/4pn2/8/1bPP4/2N5/PP2PPPP/R1BQKBNR w KQkq - 2 4", PieceColors::black, 4},
            //middle game
            {"rnb1k2r/pp1p1ppp/4p3/q1p5/2PPQ3/6P1/PP1NPP1P/R3KB1R b KQkq - 0 9", PieceColors::white, 2},
            {"rnb1k2r/pp1p1ppp/4p3/q1p5/2PPQ3/6P1/PP1NPP1P/R3KB1R b KQkq - 0 9", PieceColors::black, 5},
            //end game
            {"8/3rkp2/1P2p3/6rp/1R1P2P1/3K1P2/8/2R5 b - - 0 37", PieceColors::white, 4},
            {"8/3rkp2/1P2p3/6rp/1R1P2P1/3K1P2/8/2R5 b - - 0 37", PieceColors::black, 1},
        }));

    SECTION("Test piece correct movements")
    {
        TestGetHangingPiecesCount(fenPosition, side, defendedPiecesCount);
    }
}