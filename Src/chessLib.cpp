#include "chessLib.h"
#include <ctype.h>
#include <stdexcept>
#include "CharHelper.h"
#include <map>

const std::string ChessLib::pieceColorStr[2] = {"white", "black"};
std::string ChessLib::ExpandFenPosition(std::string fenPosition, char emptySquare)
{
    std::string expanded = "";
    for (int i = 0; i < fenPosition.length(); i++)
    {
        if (isdigit(fenPosition[i]))
        {
            expanded += std::string(CharHelper::ToInt(fenPosition[i]), emptySquare);
        }
        else
        {
            expanded += fenPosition[i];
        }
    }
    return expanded;
}

PieceName ChessLib::ToPieceNameEnum(char pieceChar)
{
    std::map<char, PieceName> pieceAbbreviationsToPieceNameMapping = {
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
        {EMPTYSQUARE, PieceName::null},
    };
    if (pieceAbbreviationsToPieceNameMapping.count(pieceChar) == 1)
    {
        return pieceAbbreviationsToPieceNameMapping.at(pieceChar);
    }
    else
    {
        std::string errorMsg = "the piece representation of ";
        errorMsg += pieceChar;
        errorMsg += " is invalid!\n";
        throw std::invalid_argument(errorMsg);
    }
}

PieceColors ChessLib::ToPieceColorEnum(char pieceChar)
{
    std::map<char, PieceColors> pieceAbbreviationsToPieceColorMapping = {
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
        {EMPTYSQUARE, PieceColors::null},
    };
    if (pieceAbbreviationsToPieceColorMapping.count(pieceChar) == 1)
    {
        return pieceAbbreviationsToPieceColorMapping.at(pieceChar);
    }
    else
    {
        std::string errorMsg = "the piece representation of ";
        errorMsg += pieceChar;
        errorMsg += " is invalid!\n";
        throw std::invalid_argument(errorMsg);
    }
}