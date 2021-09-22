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