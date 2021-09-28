#pragma once
#include "board.h"
#include "math.h"
#include "chessLib.h"
#include <vector>
#include <map>
class Search
{
public:
    ///search for all possible moves on a given position for a certain side
    static std::vector<std::string> GenerateMoves(const Board &board, PieceColors sideToMove);
    static const std::map<PieceName, std::vector<Vector2>> pieceToMoveVectorMap;
};