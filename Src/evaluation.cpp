#include "evaluation.h"
#include "analyzer.h"
#include "search.h"
void EvaluationVector::IncrementEvaluation(PieceColors side, double value)
{
    this->evaluation[side] += value;
}
double EvaluationVector::GetStaticEvaluation()
{
    return this->evaluation[PieceColors::white] - this->evaluation[PieceColors::black];
}
const std::map<PieceName, int> Evaluation::pieceNameToValueMap = {
    {PieceName::pawn, 1},
    {PieceName::bishop, 3},
    {PieceName::knight, 3},
    {PieceName::rook, 5},
    {PieceName::queen, 9},
    {PieceName::king, 0},
};
void Evaluation::EvaluateMaterial(EvaluationVector &evaluationVector, PieceName pieceName, PieceColors pieceColor)
{
    evaluationVector.IncrementEvaluation(pieceColor, Evaluation::pieceNameToValueMap.at(pieceName));
}
void Evaluation::EvaluateKnight(const Board &board, EvaluationVector &evaluationVector, int fileNum, int rankNum)
{
}
double Evaluation::Evaluate(const Board &board)
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
