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
    pawn,
    knight,
    bishop,
    rook,
    queen,
    king,
    null,

};
enum class MoveFlag
{
    normal,
    pawnDiagonalMove,
    shortCastle,
    longCastle,
    null,
};
enum class GameResult
{
    whiteWins,
    stalemate,
    blackWins,
    ongoing,

};
enum class ESquare
{
    A1,
    B1,
    C1,
    D1,
    E1,
    F1,
    G1,
    H1,
    A2,
    B2,
    C2,
    D2,
    E2,
    F2,
    G2,
    H2,
    A3,
    B3,
    C3,
    D3,
    E3,
    F3,
    G3,
    H3,
    A4,
    B4,
    C4,
    D4,
    E4,
    F4,
    G4,
    H4,
    A5,
    B5,
    C5,
    D5,
    E5,
    F5,
    G5,
    H5,
    A6,
    B6,
    C6,
    D6,
    E6,
    F6,
    G6,
    H6,
    A7,
    B7,
    C7,
    D7,
    E7,
    F7,
    G7,
    H7,
    A8,
    B8,
    C8,
    D8,
    E8,
    F8,
    G8,
    H8
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
    static char ToPieceNameChar(PieceName pieceName, PieceColors pieceColor);
    static std::string GetPieceNameStr(PieceName pieceName);
    static std::string GetPieceColorStr(PieceColors pieceName);
    static std::string GetGameResultStr(GameResult gameResult);
    static PieceColors InvertPieceColor(PieceColors color);

    //square conversion
    static ESquare ToESquare(int fileNum, int rankNum);
};
