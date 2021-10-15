#include "chessLib.h"
#include <ctype.h>
#include <stdexcept>
#include "CharHelper.h"
#include <map>
const std::map<char, PieceName> ChessLib::pieceAbbreviationsToPieceNameMapping = {
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
const std::map<char, PieceColors> ChessLib::pieceAbbreviationsToPieceColorMapping = {
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
std::string ChessLib::GetPieceNameStr(PieceName pieceName)
{
    std::string pieceNames[] = {"king", "queen", "pawn", "rook", "knight", "bishop", "null"};
    return pieceNames[(int)pieceName];
}

std::string ChessLib::GetPieceColorStr(PieceColors pieceColors)
{
    std::string pieceColorStr[] = {"white", "black", "null"};
    return pieceColorStr[(int)pieceColors];
}
std::string ChessLib::GetGameResultStr(GameResult gameResult)
{
    std::string gameResultStr[] = {"whiteWins", "stalemate", "blackWins", "ongoing"};
    return gameResultStr[(int)gameResult];
}
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
std::string ChessLib::ShrinkFenPosition(std::string fenPosition, char emptySquare)
{
    std::string shrinked = "";
    for (int i = 0; i < fenPosition.length(); i++)
    {
        int emptySquareCount = 0;
        if (fenPosition[i] == emptySquare)
        {
            for (int j = i; i < fenPosition.length(); j++)
            {
                if (fenPosition[j] == emptySquare)
                {
                    emptySquareCount++;
                    i++;
                }
                else
                {
                    i--;
                    break;
                }
            }
            shrinked += std::to_string(emptySquareCount);
        }
        else
        {
            shrinked += fenPosition[i];
        }
    }
    return shrinked;
}
PieceName ChessLib::ToPieceNameEnum(char pieceChar)
{

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

PieceColors ChessLib::InvertPieceColor(PieceColors color)
{
    if (color == PieceColors::black)
        return PieceColors::white;
    else if (color == PieceColors::white)
        return PieceColors::black;
    else
    {
        return PieceColors::null;
    }
}