#pragma once
#include <string>
#include <map>
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
enum class GameResult
{
    whiteWins,
    stalemate,
    blackWins,
    ongoing,

};
class ChessLib
{

public:
    static const std::map<char, PieceName> pieceAbbreviationsToPieceNameMapping;
    static const std::map<char, PieceColors> pieceAbbreviationsToPieceColorMapping;
    static const std::map<PieceName, char> pieceNameToPieceAbbreviationsMapping;
    ///Expand number to empty square like rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
    ///to rnbqkbnr/pppppppp/--------/--------/--------/--------/PPPPPPPP/RNBQKBNR
    ///(assuming [emptySquare] is '-')
    static std::string ExpandFenPosition(std::string fenPosition, char emptySquare);
    static std::string ShrinkFenPosition(std::string fenPosition, char emptySquare);
    static PieceName ToPieceNameEnum(char pieceChar);
    static PieceColors ToPieceColorEnum(char pieceChar);
    static char ToPieceNameAbbreviations(PieceName pieceName, PieceColors pieceColor);
    static std::string GetPieceNameStr(PieceName pieceName);
    static std::string GetPieceColorStr(PieceColors pieceName);
    static std::string GetGameResultStr(GameResult gameResult);
    static PieceColors InvertPieceColor(PieceColors color);
};
