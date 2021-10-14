#pragma once
#include "board.h"
#include "chessLib.h"
#include <map>
class Evaluation
{
public:
    static const std::map<PieceName, int> pieceNameToValue;
    static float EvaluateMaterial(const Board &board, PieceColors sideToEvaluate);
    static int EvaluateHangingPieces(const Board &board, PieceColors sideToEvaluate);
    static int EvaluateDefendedPieces(const Board &board, PieceColors sideToEvaluate);
    static int EvaluateKingSafety(const Board &board, PieceColors sideToEvaluate);
    static float EvaluateSide(const Board &board, PieceColors sideToEvaluate);
    static float Evaluate(const Board &board);
};