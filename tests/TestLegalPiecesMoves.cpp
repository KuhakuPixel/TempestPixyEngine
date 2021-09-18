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
        printf("fenPosition : %s", fenPosition.c_str());
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
        TestPiecesLegalMove(fenPosition, sideToMove, move, isMoveLegal);
    }
}

TEST_CASE("Test bishop legal moves", "[BoardLegalMoves]")
{
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
TEST_CASE("Test rook legal moves", "[BoardLegalMoves]")
{
    std::string fenPosition;
    PieceColors sideToMove;
    std::string move;
    bool isMoveLegal;

    std::tie(fenPosition, sideToMove, move, isMoveLegal) = GENERATE(
        table<std::string, PieceColors, std::string, bool>({
            //test rook movements
            {"r1bqkb1r/pp1p1ppp/2n1pn2/2p5/2B1P3/2N2N2/PPPP1PPP/R1BQK2R w KQkq - 0 5", PieceColors::white, "h1f1", true},
            {"r1bqkb1r/pp1p1ppp/2n1pn2/2p5/2B1P3/2N2N2/PPPP1PPP/R1BQK2R w KQkq - 0 5", PieceColors::white, "h1e1", false},
            {"r1bqk2r/pp3ppp/2n1pn2/b2p4/3P1B2/P1PB1N2/1P3PPP/RN1Q1RK1 b kq - 0 9", PieceColors::black, "h8f8", true},
            {"r1bqkbnr/1ppp1ppp/p1n5/4p3/4P3/2N2N1P/PPPP1PP1/R1BQKB1R b KQkq - 0 4", PieceColors::black, "h8e8", false},
            //test capture
            {"r1bqk2r/1p3pp1/p1n1pn1p/b2p4/3P1B2/P1PB1N2/1P3PPP/RN1QR1K1 w kq - 0 11", PieceColors::white, "e1e6", true},
            {"r1bqk2r/1p3pp1/p1n1pn1p/b2p4/3P1B2/P1PB1N2/1P3PPP/RN1QR1K1 w kq - 0 11", PieceColors::white, "e1d1", false},
            {"r1bqr1k1/1p3pp1/p1n2n1p/b2pB3/3P3P/P1PB1N2/1P1N1PP1/R2QR1K1 b - - 0 14", PieceColors::black, "e8e5", true},
            {"r1bqr1k1/1p3pp1/p1n2n1p/b2pB3/3P3P/P1PB1N2/1P1N1PP1/R2QR1K1 b - - 0 14", PieceColors::black, "e8g8", false},
        }));

    SECTION("Test rook moves")
    {
        TestPiecesLegalMove(fenPosition, sideToMove, move, isMoveLegal);
    }
}

TEST_CASE("Test queen legal moves", "[BoardLegalMoves]")
{
    std::string fenPosition;
    PieceColors sideToMove;
    std::string move;
    bool isMoveLegal;

    std::tie(fenPosition, sideToMove, move, isMoveLegal) = GENERATE(
        table<std::string, PieceColors, std::string, bool>({
            //test queen movements
            {"rnbqkbnr/pp1p1ppp/2p5/4p3/3PP3/8/PPP2PPP/RNBQKBNR w KQkq - 0 3", PieceColors::white, "d1h5", true},
            {"rnbqkbnr/pp1p1ppp/2p5/4p3/3PP3/8/PPP2PPP/RNBQKBNR w KQkq - 0 3", PieceColors::white, "d1d3", true},
            {"rnbqkbnr/pp1p1ppp/2p5/4p3/3PP3/8/PPP2PPP/RNBQKBNR w KQkq - 0 3", PieceColors::white, "d1a4", false},
            {"rnbqkbnr/pp1p1ppp/2p5/4p3/3PP3/8/PPP2PPP/RNBQKBNR w KQkq - 0 3", PieceColors::white, "d1d5", false},

            {"rnbqkbnr/pp3ppp/2p5/3pp3/3PP3/5N1P/PPP2PP1/RNBQKB1R b KQkq - 1 4", PieceColors::black, "d8g5", true},
            {"rnbqkbnr/pp3ppp/2p5/3pp3/3PP3/5N1P/PPP2PP1/RNBQKB1R b KQkq - 1 4", PieceColors::black, "d8d6", true},
            {"rnbqk1nr/pp2bppp/2p5/3pp3/3PP3/5N1P/PPP2PP1/RNBQKB1R w KQkq - 2 5", PieceColors::black, "d8f6", false},
            {"rnbqk1nr/pp2bppp/2p5/3pp3/3PP3/5N1P/PPP2PP1/RNBQKB1R w KQkq - 2 5", PieceColors::black, "d8d3", false},
            //test capture
            {"rnbqkb1r/pp1p1ppp/2p5/4p3/3PP1nP/8/PPP2PP1/RNBQKBNR w KQkq - 1 5", PieceColors::white, "d1g4", true},
            {"rnbqkb1r/pp1p1ppp/2p5/4p3/3PP2P/4n3/PPP1QPP1/RNB1KBNR w KQkq - 3 6", PieceColors::white, "e2e3", true},
            {"rnbqkb1r/pp1p1ppp/2p5/4p3/3PP2P/4n3/PPP1QPP1/RNB1KBNR w KQkq - 3 6", PieceColors::white, "e2c2", false},
            {"rnbqkb1r/pp1p1ppp/2p4n/4p3/3PP2P/8/PPP1QPP1/RNB1KBNR w KQkq - 3 6", PieceColors::white, "e2e4", false},

            {"rnbqkb1r/pp1p1ppp/2p4n/4p3/3PP2P/N7/PPP1QPP1/R1B1KBNR b KQkq - 4 6", PieceColors::black, "d8h4", true},
            {"rnbqkb1r/1p3ppp/2pN3n/p2pp3/3PP2P/8/PPP1QPP1/R1B1KBNR b KQkq - 1 8", PieceColors::black, "d8d6", true},
             {"rnb1kb1r/1p3ppp/2pq3n/p2pp3/3PP2P/P7/1PP1QPP1/R1B1KBNR b KQkq - 0 9", PieceColors::black, "d6f8", false},
            {"rnb1kb1r/1p3ppp/2pq3n/p2pp3/3PP2P/P7/1PP1QPP1/R1B1KBNR b KQkq - 0 9", PieceColors::black, "d6d5", false},
        }));

    SECTION("Test queen moves")
    {
        TestPiecesLegalMove(fenPosition, sideToMove, move, isMoveLegal);
    }
}
TEST_CASE("Test knight legal moves", "[BoardLegalMoves]")
{
    std::string fenPosition;
    PieceColors sideToMove;
    std::string move;
    bool isMoveLegal;

    std::tie(fenPosition, sideToMove, move, isMoveLegal) = GENERATE(
        table<std::string, PieceColors, std::string, bool>({
            //test knight movements
            {"r1bqkbnr/pppp1ppp/2n5/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 2 3", PieceColors::white, "b1c3", true},
            {"r1bqkbnr/2pp1ppp/p1n5/1p2p3/4P3/2N2N1P/PPPP1PP1/R1BQKB1R w KQkq - 0 5", PieceColors::white, "c3d6", false},
            {"r1bqkbnr/1ppp1ppp/p1n5/4p3/4P3/2N2N1P/PPPP1PP1/R1BQKB1R b KQkq - 0 4", PieceColors::black, "g8f6", true},
            {"r1bqkbnr/1ppp1ppp/p1n5/4p3/4P3/2N2N1P/PPPP1PP1/R1BQKB1R b KQkq - 0 4", PieceColors::black, "g8f5", false},
            //test capture
            {"r1bqkbnr/2pp1ppp/p1n5/1p2p3/4P3/2N2N1P/PPPP1PP1/R1BQKB1R w KQkq - 0 5", PieceColors::white, "c3b5", true},
            {"r1bqkbnr/2pp1ppp/p1n5/1p2p3/4P3/2N2N1P/PPPP1PP1/R1BQKB1R w KQkq - 0 5", PieceColors::white, "c3d1", false},
            {"r1bqkbnr/2pp1ppp/p1n5/1p6/3NP3/2N4P/PPP2PP1/R1BQKB1R b KQkq - 0 6", PieceColors::black, "c6d4", true},
            {"r1bqkbnr/2pp1ppp/2n5/pp6/P2NP3/2N4P/1PP2PP1/R1BQKB1R b KQkq - 0 7", PieceColors::black, "c6a5", false},
        }));

    SECTION("Test Knight moves")
    {
        TestPiecesLegalMove(fenPosition, sideToMove, move, isMoveLegal);
    }
}