#pragma once
#include "board.h"
#include "chessLib.h"
#include <map>
class Evaluation
{
public:
    static const std::map<PieceName, int> pieceNameToValue;
    static int EvaluateMaterial(const Board &board, PieceColors sideToEvaluate);
    static int EvaluateHangingPieces(const Board &board, PieceColors sideToEvaluate);
    static int EvaluateDefendedPieces(const Board &board, PieceColors sideToEvaluate);
    static int EvaluateKingSafety(const Board &board, PieceColors sideToEvaluate);
    static int EvaluateSide(const Board &board, PieceColors sideToEvaluate);
    static int Evaluate(const Board &board);
};