#pragma once
#include <string>
#include <map>
#include "CharHelper.h"
#define EMPTYSQUARE '-'

const std::string pieceColorStr[2] = {"white", "black"};
enum class PieceColors
{
    white,
    black
};
enum class PieceName
{
    king,
    queen,
    pawn,
    rook,
    knight,
    bishop,

};
struct Piece{
    PieceName pieceName;
    PieceColors pieceColor;
    Piece(PieceName pieceName,PieceColors pieceColor);
};
const std::map<char, PieceName> pieceAbbreviationsToPieceNameMapping = {
    {'K', PieceName::king},
    {'Q', PieceName::queen},
    {'R', PieceName::rook},
    {'N', PieceName::knight},
    {'B', PieceName::bishop},
    {'P', PieceName::pawn},

    {'k', PieceName::king},
    {'q', PieceName::queen},
    {'r', PieceName::rook},
    {'n', PieceName::knight},
    {'b', PieceName::bishop},
    {'p', PieceName::pawn},
};
const std::map<char, PieceColors> pieceAbbreviationsToPieceColorMapping = {
    {'K', PieceColors::white},
    {'Q', PieceColors::white},
    {'R', PieceColors::white},
    {'N', PieceColors::white},
    {'B', PieceColors::white},
    {'P', PieceColors::white},

    {'k', PieceColors::black},
    {'q', PieceColors::black},
    {'r', PieceColors::black},
    {'n', PieceColors::black},
    {'b', PieceColors::black},
    {'p', PieceColors::black},
};
struct Square
{
    char file;
    char rank;
    int fileNum;
    int rankNum;
    Square(char file, char rank);
};
struct Board
{
    PieceColors currentTurn = PieceColors::white;
    char board[8][8] = {

        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE},
        {EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE},
        {EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE},
        {EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},

    };
    void LoadBoard(char board[8][8]);

    void LoadFromFen(std::string fen);

    ///w for white , b for black
    void DisplayBoard(char orientation = 'w');

    bool IsMoveLegal(char piece, Square from, Square to);

    ///The move format is in long algebraic notation.
    ///A nullmove from the Engine to the GUI should be send as 0000.
    ///Examples:  e2e4, e7e5, e1g1 (white short castling), e7e8q (for promotion)
    void Move(std::string moveNotation, bool allowIllegalMove = false);
};