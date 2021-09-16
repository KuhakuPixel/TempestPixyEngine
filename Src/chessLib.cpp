#include "chessLib.h"
#include <ctype.h>
#include "CharHelper.h"
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