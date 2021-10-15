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

//reference : https://github.com/catchorg/Catch2/issues/850
//https://stackoverflow.com/questions/43762651/how-does-stdtie-work
//https://stackoverflow.com/questions/20705702/stl-pair-like-triplet-class-do-i-roll-my-own

void TestPiecesLegalMove(std::string fenPosition, std::string move, bool expect)
{
    Board board = Board();
    board.LoadFromFen(fenPosition);

    bool actual;
    try
    {
        actual = Analyzer::IsMoveLegal(board, move);
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
void TestPiecesLegalMove(std::string fenPosition, std::vector<std::string> moves, bool expect)
{
    Board board = Board();
    board.LoadFromFen(fenPosition);

    for (int i = 0; i < moves.size(); i++)
    {
        bool isMoveLegal = Analyzer::IsMoveLegal(board, moves[i]);
        if (i < moves.size() - 1)
        {
            if (isMoveLegal)
                board.Move(moves[i]);
            else
            {
                throw std::invalid_argument("move is invalid\n");
            }
        }
        else if (i == moves.size() - 1)
        {
            if (isMoveLegal != expect)
            {
                printf("test cases failed \n");
                printf("fenPosition : %s \n move: %s\n", fenPosition.c_str(), moves[i].c_str());
            }
            REQUIRE(isMoveLegal == expect);
            break;
        }
    }
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
TEST_CASE("Test pawn legal moves", "[BoardLegalMoves]")
{
    std::string fenPosition;

    std::string move;
    bool isMoveLegal;

    std::tie(fenPosition, move, isMoveLegal) = GENERATE(
        table<std::string, std::string, bool>({
            //test pawm normal movement
            //white
            {"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", "f2f4", true},
            {"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", "d2d3", true},
            {"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", "e4e3", false},
            //black
            {"rnbqkbnr/ppp1pppp/8/3p4/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2", "d5d4", true},
            {"r1bqkbnr/pppp2pp/2n5/4pp2/2BPP3/5N2/PPP2PPP/RNBQK2R b KQkq - 0 4", "f5f4", true},
            {"rnbqkbnr/pppp1ppp/8/4p3/4PP2/8/PPPP2PP/RNBQKBNR b KQkq - 0 2", "e5e6", false},
            //test capture
            //white
            {"r1bqkbnr/pppp2pp/2n5/4pp2/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 4", "e4f5", true},
            {"r1bqkbnr/pppp2pp/2n5/4pp2/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 4", "e4d5", false},
            //black
            {"rnbqkbnr/ppp1pppp/8/3p4/4PP2/8/PPPP2PP/RNBQKBNR b KQkq - 0 2", "d5e4", true},
            {"rnbqkbnr/ppp1pppp/8/3p4/4PP2/8/PPPP2PP/RNBQKBNR b KQkq - 0 2", "d5c4", false},
            //test pawn can move 2 squares
            //white
            {"rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", "d2d4", true},
            {"rnbqkbnr/pp1ppppp/8/8/3pP3/8/PPP2PPP/RNBQKBNR w KQkq - 0 3", "e4e6", false},
            //black
            {"rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1", "e7e5", true},
            {"rnbqkbnr/ppp1pppp/8/3p4/4P3/7P/PPPP1PP1/RNBQKBNR b KQkq - 0 2", "d5d3", false},
            //test pawn movement blocked
            //white
            {"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", "e4e5", false},
            {"rnb1kbnr/pp1ppppp/8/2q5/2PpP3/3B4/PP3PPP/RNBQK1NR w KQkq - 3 5", "c4c5", false},
            //black
            {"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", "e5e4", false},
            {"rnb1kbnr/ppp1qppp/8/4p3/3NPP2/P2p2P1/1PPP3P/R1BQKBNR b KQkq - 1 7", "d3d2", false},
        }));

    SECTION("Test pawn moves")
    {
        TestPiecesLegalMove(fenPosition, move, isMoveLegal);
    }
}

TEST_CASE("Test bishop legal moves", "[BoardLegalMoves]")
{
    std::string fenPosition;

    std::string move;
    bool isMoveLegal;

    std::tie(fenPosition, move, isMoveLegal) = GENERATE(
        table<std::string, std::string, bool>({
            //test if bishop is blocked
            {"rnbqkbnr/ppp1pppp/8/8/3pP3/3P4/PPP2PPP/RNBQKBNR w KQkq - 0 3", "f1c4", false},
            {"rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", "f1h3", false},
            {"rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", "f8c5", false},
            {"rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", "c8e6", false},
            //test capture
            {"rnbqkbnr/p1p1pppp/8/1p1p4/4P3/7P/PPPP1PP1/RNBQKBNR w KQkq - 0 3", "f1b5", true},
            {"rnbqkbnr/1pppp2p/p4pp1/8/8/1P3N2/PBPPPPPP/RN1QKB1R w KQkq - 0 4", "b2f6", true},
            {"rn1qkbnr/pbpppppp/1p6/8/3PP3/8/PPP1NPPP/RNBQKB1R b KQkq - 2 3", "b7e4", true},
            {"rnbqk1nr/ppppppbp/6p1/8/2P1P3/1P6/P2P1PPP/RNBQKBNR b KQkq - 0 3", "g7a1", true},
        }));

    SECTION("Test Bishops moves")
    {
        TestPiecesLegalMove(fenPosition, move, isMoveLegal);
    }
}
TEST_CASE("Test rook legal moves", "[BoardLegalMoves]")
{
    std::string fenPosition;

    std::string move;
    bool isMoveLegal;

    std::tie(fenPosition, move, isMoveLegal) = GENERATE(
        table<std::string, std::string, bool>({
            //test rook movements
            {"r1bqkb1r/pp1p1ppp/2n1pn2/2p5/2B1P3/2N2N2/PPPP1PPP/R1BQK2R w KQkq - 0 5", "h1f1", true},
            {"r1bqkb1r/pp1p1ppp/2n1pn2/2p5/2B1P3/2N2N2/PPPP1PPP/R1BQK2R w KQkq - 0 5", "h1e1", false},
            {"r1bqk2r/pp3ppp/2n1pn2/b2p4/3P1B2/P1PB1N2/1P3PPP/RN1Q1RK1 b kq - 0 9", "h8f8", true},
            {"r1bqkbnr/1ppp1ppp/p1n5/4p3/4P3/2N2N1P/PPPP1PP1/R1BQKB1R b KQkq - 0 4", "h8e8", false},
            //test capture
            {"r1bqk2r/1p3pp1/p1n1pn1p/b2p4/3P1B2/P1PB1N2/1P3PPP/RN1QR1K1 w kq - 0 11", "e1e6", true},
            {"r1bqk2r/1p3pp1/p1n1pn1p/b2p4/3P1B2/P1PB1N2/1P3PPP/RN1QR1K1 w kq - 0 11", "e1d1", false},
            {"r1bqr1k1/1p3pp1/p1n2n1p/b2pB3/3P3P/P1PB1N2/1P1N1PP1/R2QR1K1 b - - 0 14", "e8e5", true},
            {"r1bqr1k1/1p3pp1/p1n2n1p/b2pB3/3P3P/P1PB1N2/1P1N1PP1/R2QR1K1 b - - 0 14", "e8g8", false},
        }));

    SECTION("Test rook moves")
    {
        TestPiecesLegalMove(fenPosition, move, isMoveLegal);
    }
}

TEST_CASE("Test queen legal moves", "[BoardLegalMoves]")
{
    std::string fenPosition;

    std::string move;
    bool isMoveLegal;

    std::tie(fenPosition, move, isMoveLegal) = GENERATE(
        table<std::string, std::string, bool>({
            //test queen movements
            {"rnbqkbnr/pp1p1ppp/2p5/4p3/3PP3/8/PPP2PPP/RNBQKBNR w KQkq - 0 3", "d1h5", true},
            {"rnbqkbnr/pp1p1ppp/2p5/4p3/3PP3/8/PPP2PPP/RNBQKBNR w KQkq - 0 3", "d1d3", true},
            {"rnbqkbnr/pp1p1ppp/2p5/4p3/3PP3/8/PPP2PPP/RNBQKBNR w KQkq - 0 3", "d1a4", false},
            {"rnbqkbnr/pp1p1ppp/2p5/4p3/3PP3/8/PPP2PPP/RNBQKBNR w KQkq - 0 3", "d1d5", false},

            {"rnbqkbnr/pp3ppp/2p5/3pp3/3PP3/5N1P/PPP2PP1/RNBQKB1R b KQkq - 1 4", "d8g5", true},
            {"rnbqkbnr/pp3ppp/2p5/3pp3/3PP3/5N1P/PPP2PP1/RNBQKB1R b KQkq - 1 4", "d8d6", true},
            {"rnbqk1nr/pp2bppp/2p5/3pp3/3PP3/5N1P/PPP2PP1/RNBQKB1R w KQkq - 2 5", "d8f6", false},
            {"rnbqk1nr/pp2bppp/2p5/3pp3/3PP3/5N1P/PPP2PP1/RNBQKB1R w KQkq - 2 5", "d8d3", false},
            //test capture
            {"rnbqkb1r/pp1p1ppp/2p5/4p3/3PP1nP/8/PPP2PP1/RNBQKBNR w KQkq - 1 5", "d1g4", true},
            {"rnbqkb1r/pp1p1ppp/2p5/4p3/3PP2P/4n3/PPP1QPP1/RNB1KBNR w KQkq - 3 6", "e2e3", true},
            {"rnbqkb1r/pp1p1ppp/2p5/4p3/3PP2P/4n3/PPP1QPP1/RNB1KBNR w KQkq - 3 6", "e2c2", false},
            {"rnbqkb1r/pp1p1ppp/2p4n/4p3/3PP2P/8/PPP1QPP1/RNB1KBNR w KQkq - 3 6", "e2e4", false},

            {"rnbqkb1r/pp1p1ppp/2p4n/4p3/3PP2P/N7/PPP1QPP1/R1B1KBNR b KQkq - 4 6", "d8h4", true},
            {"rnbqkb1r/1p3ppp/2pN3n/p2pp3/3PP2P/8/PPP1QPP1/R1B1KBNR b KQkq - 1 8", "d8d6", true},
            {"rnb1kb1r/1p3ppp/2pq3n/p2pp3/3PP2P/P7/1PP1QPP1/R1B1KBNR b KQkq - 0 9", "d6f8", false},
            {"rnb1kb1r/1p3ppp/2pq3n/p2pp3/3PP2P/P7/1PP1QPP1/R1B1KBNR b KQkq - 0 9", "d6d5", false},
        }));

    SECTION("Test queen moves")
    {
        TestPiecesLegalMove(fenPosition, move, isMoveLegal);
    }
}
TEST_CASE("Test knight legal moves", "[BoardLegalMoves]")
{
    std::string fenPosition;

    std::string move;
    bool isMoveLegal;

    std::tie(fenPosition, move, isMoveLegal) = GENERATE(
        table<std::string, std::string, bool>({
            //test knight movements
            {"r1bqkbnr/pppp1ppp/2n5/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 2 3", "b1c3", true},
            {"r1bqkbnr/2pp1ppp/p1n5/1p2p3/4P3/2N2N1P/PPPP1PP1/R1BQKB1R w KQkq - 0 5", "c3d6", false},
            {"r1bqkbnr/1ppp1ppp/p1n5/4p3/4P3/2N2N1P/PPPP1PP1/R1BQKB1R b KQkq - 0 4", "g8f6", true},
            {"r1bqkbnr/1ppp1ppp/p1n5/4p3/4P3/2N2N1P/PPPP1PP1/R1BQKB1R b KQkq - 0 4", "g8f5", false},
            //test capture
            {"r1bqkbnr/2pp1ppp/p1n5/1p2p3/4P3/2N2N1P/PPPP1PP1/R1BQKB1R w KQkq - 0 5", "c3b5", true},
            {"r1bqkbnr/2pp1ppp/p1n5/1p2p3/4P3/2N2N1P/PPPP1PP1/R1BQKB1R w KQkq - 0 5", "c3d1", false},
            {"r1bqkbnr/2pp1ppp/p1n5/1p6/3NP3/2N4P/PPP2PP1/R1BQKB1R b KQkq - 0 6", "c6d4", true},
            {"r1bqkbnr/2pp1ppp/2n5/pp6/P2NP3/2N4P/1PP2PP1/R1BQKB1R b KQkq - 0 7", "c6a5", false},
        }));

    SECTION("Test Knight moves")
    {
        TestPiecesLegalMove(fenPosition, move, isMoveLegal);
    }
}

TEST_CASE("Test Illegal king moves by check", "[BoardLegalMoves]")
{
    std::string fenPosition;

    std::string move;
    bool isMoveLegal;

    std::tie(fenPosition, move, isMoveLegal) = GENERATE(
        table<std::string, std::string, bool>({

            {"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", "e1e2", true},
            {"rnbqk1nr/pppp1ppp/8/2b1p3/4P3/2N5/PPPPKPPP/R1BQ1BNR w kq - 4 4", "e2e3", false},
            {"rnb1k1nr/pppq1ppp/3p4/4p3/1K2P3/2N5/PPPP1PPP/R1BQ1BNR w kq - 1 7", "b4b5", false},
            {"rnb1k1nr/pppq1ppp/3p4/4p3/1K2P3/2N5/PPPP1PPP/R1BQ1BNR w kq - 1 7", "b4a4", false},
            {"r1b1k1nr/pppq1ppp/2np4/4p3/2K1P3/2N5/PPPP1PPP/R1BQ1BNR w kq - 3 8", "c4b4", false},

            //test moving other piece when king is in check
            {"8/8/1P6/KP6/Pr6/8/3b4/Q3k3 b - - 0 1", "d2e3", false},
            {"2R3k1/5ppp/8/8/1b6/8/5PPP/6K1 b - - 0 1", "b4f8", true},

        }));

    SECTION("Test king moves illegal")
    {
        TestPiecesLegalMove(fenPosition, move, isMoveLegal);
    }
}

TEST_CASE("Test Absolute Pin move", "[BoardLegalMoves]")
{
    std::string fenPosition;

    std::string move;
    bool isMoveLegal;

    std::tie(fenPosition, move, isMoveLegal) = GENERATE(
        table<std::string, std::string, bool>({
            //knight pinned
            {"rnbqk2r/ppp2ppp/8/3pP3/1b1Pnp2/2NB1N2/PPP3PP/R1BQK2R w KQkq - 3 8", "c3b5", false},
            {"rnbqk2r/ppp2ppp/8/3pP3/1b1P1p2/2NB1NnP/PPP3P1/R1BQK2R w KQkq - 1 9", "c3b5", false},
            //pawn pinned
            {"8/4k3/8/8/8/1rP1K3/8/8 w - - 0 1", "c3c4", false},
            {"8/8/6k1/1K2Pr2/8/8/8/8 w - - 0 1", "e5e6", false},
            //bishop pinned
            {"8/8/4r1k1/8/8/4B3/4K3/8 w - - 0 1", "e3g5", false},
            {"8/8/6k1/8/8/8/r2BK3/8 w - - 0 1", "d2f4", false},
            //queen pinned
            {"3r4/8/8/8/8/8/1k6/r4QK1 w - - 0 1", "f1f2", false},
            {"1r4bk/8/8/3Q4/2K5/8/8/8 w - - 0 1", "d5e5", false},
            //rook pinned
            {"8/8/8/3K4/3R4/8/8/3rk3 w - - 0 1", "d4e4", false},
            {"R7/8/8/K7/1R6/8/3b4/4k3 w - - 0 1", "b4b1", false},

        }));

    SECTION("Test Absolute Pin move")
    {
        TestPiecesLegalMove(fenPosition, move, isMoveLegal);
    }
}

TEST_CASE("Test Castling", "[BoardLegalMoves]")
{
    std::string fenPosition;

    std::string move;
    bool isMoveLegal;

    std::tie(fenPosition, move, isMoveLegal) = GENERATE(
        table<std::string, std::string, bool>({
            //white short castle
            {"rnbqk2r/1ppp1ppp/p6n/2b1P3/5p2/2NP1N2/PPP1B1PP/R1BQK2R w KQkq - 0 8", "e1g1", false},
            {"rnbqk2r/ppppbppp/7n/4P3/5p2/2NP1N2/PPP1B1PP/R1BQK2R w KQkq - 3 8", "e1g1", true},
            //white long castle
            {"r1b1kbnr/1p1p4/p1n1pp1p/1Bp3q1/3PP2P/2NQ1N2/PPP2PP1/R3K2R w KQkq - 0 11", "e1c1", false},
            {"r1b1kbnr/1p1p1pq1/p1n1p2p/1Bp5/3PP2P/2NQ1N2/PPP2PP1/R3K2R w KQkq - 3 11", "e1g1", true},
            //test illegal castle
            {"rnbq1bnr/pppp1ppp/4k3/4p3/4P3/4K3/PPPP1PPP/RNBQ1BNR w - - 4 4", "e3g3", false},

        }));

    SECTION("Test Castling")
    {
        TestPiecesLegalMove(fenPosition, move, isMoveLegal);
    }
}

TEST_CASE("Test Loosing castling rights", "[BoardLegalMoves]")
{
    std::string fenPosition;

    std::vector<std::string> moves;
    bool isMoveLegal;

    std::tie(fenPosition, moves, isMoveLegal) = GENERATE(
        table<std::string, std::vector<std::string>, bool>({
            //white loose castling rights because of a rook(a1) move
            {
                "r1bqkb1r/ppp1ppp1/2np1n1p/8/2B1P2P/5N2/PPPP1PP1/RNBQK2R w KQkq - 0 5",

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
        TestPiecesLegalMove(fenPosition, moves, isMoveLegal);
    }
}
