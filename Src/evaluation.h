#pragma once
#include "board.h"
#include "chessLib.h"
#include <map>
class EvaluationVector
{
private:
    std::map<PieceColors, double> evaluation = {
        {PieceColors::white, 0},
        {PieceColors::black, 0},
    };

public:
    void IncrementEvaluation(PieceColors side, double value);
    double GetStaticEvaluation();
};
class Evaluation
{
public:
    static const std::map<PieceName, int> pieceNameToValue;
    static float EvaluateMaterial(const Board &board, PieceColors sideToEvaluate);
    static double EvaluateHangingPieces(const Board &board, PieceColors sideToEvaluate);
    static double EvaluateDefendedPieces(const Board &board, PieceColors sideToEvaluate);
    static double EvaluateKingSafety(const Board &board, PieceColors sideToEvaluate);
    static double EvaluateSide(const Board &board, PieceColors sideToEvaluate);
    static double Evaluate(const Board &board);
};