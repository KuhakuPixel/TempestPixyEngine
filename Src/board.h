#pragma once
#include <string>
#include <map>
#include "CharHelper.h"
#include <vector>
#define EMPTYSQUARE '-'

const std::string pieceColorStr[2] = {"white", "black"};
enum class PieceColors
{
    white,
    black,
    null,
};
enum class PieceName
{
    king,
    queen,
    pawn,
    rook,
    knight,
    bishop,
    null,

};
enum class MoveFlag
{
    normal,
    capture,
    check,
    shortCastle,
    longCastle,
    enpassant,
    promotion,
    checkMate
};


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
    PieceColors GetCurrentTurn();
    std::string GetCurrentTurnStr();
    void PlacePiece(char piece, int fileNum, int rankNum);
    void PlacePiece(char piece, Square square);
    char GetPieceNameFromBoard(int fileNum, int rankNum);

    char GetPieceNameFromBoard(Square square);


    PieceColors GetPieceColorFromBoard(int filenum, int rankNum);
    PieceColors GetPieceColorFromBoard(Square square);
   
    MoveFlag GetMoveFlag(const Board &board, PieceName pieceName, Square from, Square to);

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