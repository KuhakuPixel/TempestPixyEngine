#include "catch.hpp"
#include "../Src/board.h"
#include "../Src/stringHelper.h"
#include "../Src/chessLib.h"
#include "../Src/analyzer.h"
#include <vector>
#include <string>

//reference : https://github.com/catchorg/Catch2/issues/850
//https://stackoverflow.com/questions/43762651/how-does-stdtie-work
//https://stackoverflow.com/questions/20705702/stl-pair-like-triplet-class-do-i-roll-my-own

void TestPiecesLegalMove(std::string fenPosition, PieceColors sideToMove, std::string move, bool expect)
{
    Board board = Board();
    board.LoadFromFen(fenPosition);

    bool actual;
    try
    {
        actual = Analyzer::IsMoveLegal(board, sideToMove, move);
    }
    //ref: https://stackoverflow.com/questions/6755991/catching-stdexception-by-reference/6756040#6756040
    catch (const std::exception &e)
    {
        printf("%s \n", e.what());
    }
    if (actual != expect)
    {
        printf("test cases failed \n");
        printf("fenPosition : %s \n move: %s\n", fenPosition.c_str(), move.c_str());
    }
    REQUIRE(actual == expect);
}
void TestPiecesLegalMove(std::string fenPosition, PieceColors sideToMove, std::vector<std::string> moves, bool expect)
{
    Board board = Board();
    board.LoadFromFen(fenPosition);

    for (int i = 0; i < moves.size(); i++)
    {
        bool isMoveLegal = Analyzer::IsMoveLegal(board, sideToMove, moves[i]);
        if (i < moves.size() - 1)
        {
            if (isMoveLegal)
                board.Move(moves[i]);
        }
        else if (i == moves.size() - 1)
        {
            if (isMoveLegal != expect)
            {
                printf("test cases failed \n");
                printf("fenPosition : %s \n move: %s\n", fenPosition.c_str(), moves[i].c_str());
                throw std::invalid_argument("move is invalid\n");
            }
            REQUIRE(isMoveLegal == expect);
            break;
        }
    }
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
            {"rnbqkbnr/ppp1pppp/8/3p4/4PP2/8/PPPP2PP/RNBQKBNR b KQkq - 0 2", PieceColors::black, "d5e4", true},
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

TEST_CASE("Test Illegal king moves by check", "[BoardLegalMoves]")
{
    std::string fenPosition;
    PieceColors sideToMove;
    std::string move;
    bool isMoveLegal;

    std::tie(fenPosition, sideToMove, move, isMoveLegal) = GENERATE(
        table<std::string, PieceColors, std::string, bool>({

            {"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", PieceColors::white, "e1e2", true},
            {"rnbqk1nr/pppp1ppp/8/2b1p3/4P3/2N5/PPPPKPPP/R1BQ1BNR w kq - 4 4", PieceColors::white, "e2e3", false},
            {"rnb1k1nr/pppq1ppp/3p4/4p3/1K2P3/2N5/PPPP1PPP/R1BQ1BNR w kq - 1 7", PieceColors::white, "b4b5", false},
            {"rnb1k1nr/pppq1ppp/3p4/4p3/1K2P3/2N5/PPPP1PPP/R1BQ1BNR w kq - 1 7", PieceColors::white, "b4a4", false},
            {"r1b1k1nr/pppq1ppp/2np4/4p3/2K1P3/2N5/PPPP1PPP/R1BQ1BNR w kq - 3 8", PieceColors::white, "c4b4", false},

            //test moving other piece when king is in check
            {"8/8/1P6/KP6/Pr6/8/3b4/Q3k3 b - - 0 1", PieceColors::black, "d2e3", false},

        }));

    SECTION("Test king moves illegal")
    {
        TestPiecesLegalMove(fenPosition, sideToMove, move, isMoveLegal);
    }
}

TEST_CASE("Test Absolute Pin move", "[BoardLegalMoves]")
{
    std::string fenPosition;
    PieceColors sideToMove;
    std::string move;
    bool isMoveLegal;

    std::tie(fenPosition, sideToMove, move, isMoveLegal) = GENERATE(
        table<std::string, PieceColors, std::string, bool>({
            //knight pinned
            {"rnbqk2r/ppp2ppp/8/3pP3/1b1Pnp2/2NB1N2/PPP3PP/R1BQK2R w KQkq - 3 8", PieceColors::white, "c3b5", false},
            {"rnbqk2r/ppp2ppp/8/3pP3/1b1P1p2/2NB1NnP/PPP3P1/R1BQK2R w KQkq - 1 9", PieceColors::white, "c3b5", false},
            //pawn pinned
            {"8/4k3/8/8/8/1rP1K3/8/8 w - - 0 1", PieceColors::white, "c3c4", false},
            {"8/8/6k1/1K2Pr2/8/8/8/8 w - - 0 1", PieceColors::white, "e5e6", false},
            //bishop pinned
            {"8/8/4r1k1/8/8/4B3/4K3/8 w - - 0 1", PieceColors::white, "e3g5", false},
            {"8/8/6k1/8/8/8/r2BK3/8 w - - 0 1", PieceColors::white, "d2f4", false},
            //queen pinned
            {"3r4/8/8/8/8/8/1k6/r4QK1 w - - 0 1", PieceColors::white, "f1f2", false},
            {"1r4bk/8/8/3Q4/2K5/8/8/8 w - - 0 1", PieceColors::white, "d5e5", false},
            //rook pinned
            {"8/8/8/3K4/3R4/8/8/3rk3 w - - 0 1", PieceColors::white, "d4e4", false},
            {"R7/8/8/K7/1R6/8/3b4/4k3 w - - 0 1", PieceColors::white, "b4b1", false},

        }));

    SECTION("Test Absolute Pin move")
    {
        TestPiecesLegalMove(fenPosition, sideToMove, move, isMoveLegal);
    }
}

TEST_CASE("Test Castling", "[BoardLegalMoves]")
{
    std::string fenPosition;
    PieceColors sideToMove;
    std::string move;
    bool isMoveLegal;

    std::tie(fenPosition, sideToMove, move, isMoveLegal) = GENERATE(
        table<std::string, PieceColors, std::string, bool>({
            //white short castle
            {"rnbqk2r/1ppp1ppp/p6n/2b1P3/5p2/2NP1N2/PPP1B1PP/R1BQK2R w KQkq - 0 8", PieceColors::white, "e1g1", false},
            {"rnbqk2r/ppppbppp/7n/4P3/5p2/2NP1N2/PPP1B1PP/R1BQK2R w KQkq - 3 8", PieceColors::white, "e1g1", true},
            //white long castle
            {"r1b1kbnr/1p1p4/p1n1pp1p/1Bp3q1/3PP2P/2NQ1N2/PPP2PP1/R3K2R w KQkq - 0 11", PieceColors::white, "e1c1", false},
            {"r1b1kbnr/1p1p1pq1/p1n1p2p/1Bp5/3PP2P/2NQ1N2/PPP2PP1/R3K2R w KQkq - 3 11", PieceColors::white, "e1g1", true},

        }));

    SECTION("Test Castling")
    {
        TestPiecesLegalMove(fenPosition, sideToMove, move, isMoveLegal);
    }
}

TEST_CASE("Test Loosing castling rights", "[BoardLegalMoves]")
{
    std::string fenPosition;
    PieceColors sideToMove;
    std::vector<std::string> moves;
    bool isMoveLegal;

    std::tie(fenPosition, sideToMove, moves, isMoveLegal) = GENERATE(
        table<std::string, PieceColors, std::vector<std::string>, bool>({
            //white loose castling rights because of a rook(a1) move
            {
                "r1bqkb1r/ppp1ppp1/2np1n1p/8/2B1P2P/5N2/PPPP1PP1/RNBQK2R w KQkq - 0 5",
                PieceColors::white,
                {
                    "h1h2",
                    "a7a6",
                    "h2h1",
                    "a6a5",
                    "e1g1",
                },
                false,
            },
            //white loose castling right because of a rook (h1) move
            {
                "r1bqk1n1/4b2r/2n5/8/2BQ4/2N1BN2/8/R3K2R w KQ - 10 6",
                PieceColors::white,
                {
                    "a1a2",
                    "a8a7",
                    "a2a1",
                    "a7a8",
                    "e1c1",
                },
                false,
            },

            //white loose castling right because of a king move
            {
                "rnbqk2r/6b1/5n2/8/2B5/5N2/8/RNBQK2R w KQkq - 4 3",
                PieceColors::white,
                {
                    "e1e2",
                    "e8e7",
                    "e2e1",
                    "e7e8",
                    "e1g1",
                },
                false,
            },
            //white loose castling right because of a king move
            {
                "rn1qkb2/3b3r/5n2/3Q4/8/2N1B3/8/R3KBNR w KQq - 6 4",
                PieceColors::white,
                {
                    "e1e2",
                    "e8e7",
                    "e2e1",
                    "e7e8",
                    "e1c1",
                },
                false,
            },
        }));

    SECTION("Test Loosing castling rights")
    {
        TestPiecesLegalMove(fenPosition, sideToMove, moves, isMoveLegal);
    }
}
