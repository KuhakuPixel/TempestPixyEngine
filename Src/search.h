#pragma once
#include "board.h"
#include "math.h"
#include "chessLib.h"
#include "evaluation.h"
#include <vector>
#include <map>
#include <string>
struct SearchNode
{
    const Board &currentBoard;
    PieceColors sideToMove;
    std::string move;
    SearchNode(const Board &currentBoard, PieceColors sideToMove, std::string move);
};

class Search
{
public:
    /// Get the number of legal moves that a piece standing on the specified squares
    /// returns 0 if empty square
    static std::vector<std::string> GeneratePieceLegalMoves(const Board &board, int fileNum, int rankNum);
    /// search for all possible moves on a given position for a certain side
    static std::vector<std::string> GenerateMoves(const Board &board, PieceColors sideToMove);

    static const std::map<PieceName, std::vector<Vector2>> pieceToMoveVectorMap;
    static double SearchPosition(const Board &board, const Evaluation &evaluation, int currentDepth, int maxDepth, std::string *bestMove = nullptr);
};