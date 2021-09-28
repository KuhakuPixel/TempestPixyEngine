#pragma once
#include "board.h"
#include <vector>
class Search
{
public:
    ///search for all possible moves on a given position for a certain side
    static std::vector<std::string> SearchPosition(const Board &board, PieceColors sideToMove);
};