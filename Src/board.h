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
    ///square size must be exactly 2
    ///for example :e2 ,h3 and ect
    Square(std::string square);
    std::string GetNotation();

    ///the first element of the tuple is the original square
    ///the second element of the tuple is the destination square
    static std::pair<Square, Square> GetMoveFromStr(std::string move);
};

class Board
{
private:
    std::vector<MoveFlag> blackCastlingRights = {MoveFlag::shortCastle, MoveFlag::longCastle};
    std::vector<MoveFlag> whiteCastlingRights = {MoveFlag::shortCastle, MoveFlag::longCastle};
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
    std::vector<MoveFlag> GetCastlingRights(PieceColors color) const;
    bool IsSquareEmpty(int fileNum, int rankNum) const;
    bool IsSquareEmpty(Square square) const;
    void PlacePiece(char piece, int fileNum, int rankNum);
    void PlacePiece(char piece, Square square);

    char GetPieceName(int fileNum, int rankNum) const;
    char GetPieceName(Square square) const;

    PieceName GetPieceNameEnum(int fileNum, int rankNum) const;
    PieceName GetPieceNameEnum(Square square) const;

    PieceColors GetPieceColor(int fileNum, int rankNum) const;
    PieceColors GetPieceColor(Square square) const;

    void LoadPseudoBoard(const Board &board);
    void LoadFromFen(std::string fen);
    std::string ExportFen();

    ///w for white , b for black
    void DisplayBoard(char orientation = 'w');

    ///The move format is in long algebraic notation.
    ///A nullmove from the Engine to the GUI should be send as 0000.
    ///Examples:  e2e4, e7e5, e1g1 (white short castling), e7e8q (for promotion)
    void Move(std::string moveNotation, bool psuedoLegalMove = false);

    ///The move format is in long algebraic notation.
    ///A nullmove from the Engine to the GUI should be send as 0000.
    ///Examples:  e2e4, e7e5, e1g1 (white short castling), e7e8q (for promotion)
    void Move(Square from, Square to, bool psuedoLegalMove = false);
};