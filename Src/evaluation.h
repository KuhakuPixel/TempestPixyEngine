#pragma once
#include "board.h"
#include "chessLib.h"
#include <map>
class EvaluationVector
{
private:
    std::map<PieceColors, double> pieceColorToEvaluation = {
        {PieceColors::white, 0},
        {PieceColors::black, 0},
    };

public:
    void IncrementEvaluation(PieceColors side, double value);
    double GetStaticEvaluation();
};
class Evaluation
{
private:
    std::map<PieceName, std::map<ESquare, double>> piecesSquaresValue;

public:
    static const std::map<PieceName, double> pieceNameToValueMap;
    Evaluation();
    void SetPieceSquareValue(PieceName pieceName, std::string square, double value);
    /// initialize knight square value on
    /// a1 to a8,a8 to h8,a1 to h1 or h1 to h8.
    void InitializeKnightPeriphery0(double value);
    /// initialize knight square value on
    /// b2 to b7,b7 to g7,b2 to g2 or g2 to g7.
    void InitializeKnightPeriphery1(double value);
    /// initialize knight square value on
    /// c3 to c6,c6 to f6,c3 to f3 or f3 to f6.
    void InitializeKnightPeriphery2(double value);
    /// initialize knight square value on
    /// e4, e5,d4 or d5
    void InitializeKnightPeriphery3(double value);

    void EvaluateMaterial(EvaluationVector &evaluationVector, PieceName pieceName, PieceColors pieceColors) const;
    double EvaluateHangingPieces(const Board &board, PieceColors sideToEvaluate) const;
    double EvaluateDefendedPieces(const Board &board, PieceColors sideToEvaluate) const;
    double EvaluateKingSafety(const Board &board, PieceColors sideToEvaluate) const;
    void EvaluateKnight(const Board &board, EvaluationVector &evaluationVector, PieceColors pieceColor, int fileNum, int rankNum) const;
    double Evaluate(const Board &board) const;
};