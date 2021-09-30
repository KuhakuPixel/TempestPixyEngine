#pragma once
#include <string>
#define EMPTYSQUARE '-'
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
    pawnDiagonalMove,
    shortCastle,
    longCastle,
    promotion,
    null,
};

class ChessLib
{

public:
    ///Expand number to empty square like rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
    ///to rnbqkbnr/pppppppp/--------/--------/--------/--------/PPPPPPPP/RNBQKBNR
    ///(assuming [emptySquare] is '-')
    static std::string ExpandFenPosition(std::string fenPosition, char emptySquare);
    static std::string ShrinkFenPosition(std::string fenPosition, char emptySquare);
    static PieceName ToPieceNameEnum(char pieceChar);
    static PieceColors ToPieceColorEnum(char pieceChar);

    static std::string GetPieceNameStr(PieceName pieceName);
    static std::string GetPieceColorStr(PieceColors pieceName);
    static PieceColors InvertPieceColor(PieceColors color);
};
