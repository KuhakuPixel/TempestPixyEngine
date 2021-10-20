#include "evaluation.h"
#include "analyzer.h"
#include "search.h"

void EvaluationVector::IncrementEvaluation(PieceColors side, double value)
{
    this->pieceColorToEvaluation[side] += value;
}
double EvaluationVector::GetStaticEvaluation()
{
    return this->pieceColorToEvaluation[PieceColors::white] - this->pieceColorToEvaluation[PieceColors::black];
}
Evaluation::Evaluation()
{
    for (int i = (int)ESquare::A1; i <= (int)ESquare::H8; i++)
    {
        ESquare itr = static_cast<ESquare>(i);
        this->knightSquaresValue.insert({itr, 0});
        this->bishopSquaresValue.insert({itr, 0});
    }
}
void Evaluation::InitializeKnightPeriphery0(int value)
{
    for (int i = 0; i < 7; i++)
    {
        // a1 to h1
        this->knightSquaresValue.at(static_cast<ESquare>(i)) = value;
        // a8 to h8
        this->knightSquaresValue.at(static_cast<ESquare>(56 + i)) = value;
        // a1 to a8
        this->knightSquaresValue.at(static_cast<ESquare>(i * 8)) = value;
        // h1 to h8
        this->knightSquaresValue.at(static_cast<ESquare>((i * 8) + 7)) = value;
    }
}
void Evaluation::InitializeKnightPeriphery1(int value)
{
}
void Evaluation::InitializeKnightPeriphery2(int value)
{
}
void Evaluation::InitializeKnightPeriphery3(int value)
{
}

const std::map<PieceName, int> Evaluation::pieceNameToValueMap = {
    {PieceName::pawn, 1},
    {PieceName::bishop, 3},
    {PieceName::knight, 3},
    {PieceName::rook, 5},
    {PieceName::queen, 9},
    {PieceName::king, 0},
};
void Evaluation::EvaluateMaterial(
    EvaluationVector &evaluationVector, PieceName pieceName, PieceColors pieceColor) const
{
    evaluationVector.IncrementEvaluation(pieceColor, Evaluation::pieceNameToValueMap.at(pieceName));
}
void Evaluation::EvaluateKnight(
    const Board &board, EvaluationVector &evaluationVector, int fileNum, int rankNum) const
{
}
double Evaluation::Evaluate(const Board &board) const
{
    EvaluationVector evalVector = EvaluationVector();
    for (int rankItr = 1; rankItr <= 8; rankItr++)
    {
        for (int fileItr = 1; fileItr <= 8; fileItr++)
        {
            if (!board.IsSquareEmpty(fileItr, rankItr))
            {
                PieceName pieceName = board.GetPieceNameEnum(fileItr, rankItr);
                PieceColors pieceColor = board.GetPieceColor(fileItr, rankItr);
                EvaluateMaterial(evalVector, pieceName, pieceColor);
                switch (pieceName)
                {
                case PieceName::pawn:
                {
                }
                case PieceName::knight:
                {
                    EvaluateKnight(board, evalVector, fileItr, rankItr);
                }
                case PieceName::bishop:
                {
                }
                case PieceName::rook:
                {
                }
                case PieceName::queen:
                {
                }
                case PieceName::king:
                {
                }
                }
            }
        }
    }
    return evalVector.GetStaticEvaluation();
}
