#pragma once
#include <string>
#include <map>
#include "CharHelper.h"
#include <vector>
#include "chessLib.h"

struct Square
{
    char file;
    char rank;
    int fileNum;
    int rankNum;
    Square(char file, char rank);
    Square(int fileNum, int rankNum);
    std::string GetBoardNotation();
};

class Board
{
private:
    std::map<PieceColors, std::vector<MoveFlag>> playersToCastlingRightsMap = {
        {PieceColors::white, {MoveFlag::shortCastle, MoveFlag::longCastle}},
        {PieceColors::black, {MoveFlag::shortCastle, MoveFlag::longCastle}},
    };

    PieceColors currentTurn = PieceColors::white;
    char board[8][8] = {

        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE},
        {EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE},
        {EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE},
        {EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},

    };
    void ClearBoard();

public:
    //getter are const to tell the compiler that this function will not change
    //the property of this instance
    //ref:
    //https://stackoverflow.com/questions/26963510/error-passing-const-as-this-argument-of-discards-qualifiers/26963552
    //https://stackoverflow.com/questions/13103755/intellisense-the-object-has-type-qualifiers-that-are-not-compatible-with-the-me/13103791
    //https://stackoverflow.com/questions/28987916/cannot-call-a-method-of-const-reference-parameter-in-c
    PieceColors GetCurrentTurn() const;
    std::string GetCurrentTurnStr() const;

    bool IsSquareEmpty(int fileNum, int rankNum) const;
    bool IsSquareEmpty(Square square) const;
    void PlacePiece(char piece, int fileNum, int rankNum);
    void PlacePiece(char piece, Square square);

    char GetPieceNameFromBoard(int fileNum, int rankNum) const;
    char GetPieceNameFromBoard(Square square) const;

    PieceName GetPieceNameEnumFromBoard(int fileNum, int rankNum) const;
    PieceName GetPieceNameEnumFromBoard(Square square) const;

    PieceColors GetPieceColorFromBoard(int fileNum, int rankNum) const;
    PieceColors GetPieceColorFromBoard(Square square) const;

    void LoadBoard(char board[8][8]);
    void LoadFromFen(std::string fen);

    std::string ExportFen();

    ///w for white , b for black
    void DisplayBoard(char orientation = 'w');

    bool IsMoveLegal(PieceColors sideToMove, Square from, Square to);
    ///The move format is in long algebraic notation.
    ///A nullmove from the Engine to the GUI should be send as 0000.
    ///Examples:  e2e4, e7e5, e1g1 (white short castling), e7e8q (for promotion)
    bool IsMoveLegal(PieceColors sideToMove, std::string moveNotation);

    ///The move format is in long algebraic notation.
    ///A nullmove from the Engine to the GUI should be send as 0000.
    ///Examples:  e2e4, e7e5, e1g1 (white short castling), e7e8q (for promotion)
    void Move(std::string moveNotation, bool allowIllegalMove = false);
};