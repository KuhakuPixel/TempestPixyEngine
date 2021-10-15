#include "evaluation.h"
#include "analyzer.h"
#include "search.h"
const std::map<PieceName, int> Evaluation::pieceNameToValue = {
    {PieceName::pawn, 1},
    {PieceName::bishop, 3},
    {PieceName::knight, 3},
    {PieceName::rook, 5},
    {PieceName::queen, 9},
    {PieceName::king, 0},
};
float Evaluation::EvaluateMaterial(const Board &board, PieceColors sideToEvaluate)
{
    int evalValue = 0;
    for (int rankItr = 1; rankItr <= 8; rankItr++)
    {
        for (int fileItr = 1; fileItr <= 8; fileItr++)
        {
            if (!board.IsSquareEmpty(fileItr, rankItr))
            {
                if (board.GetPieceColor(fileItr, rankItr) == sideToEvaluate)
                {
                    PieceName pieceName = board.GetPieceNameEnum(fileItr, rankItr);
                    evalValue += Evaluation::pieceNameToValue.at(pieceName);
                }
            }
        }
    }
    return evalValue;
}
double Evaluation::EvaluateSide(const Board &board, PieceColors sideToEvaluate)
{
    int evaluation = EvaluateMaterial(board, sideToEvaluate) +
                     Analyzer::GetDefendedPiecesCount(board, sideToEvaluate) * 0.5 +
                     Analyzer::GetHangingPiecesCount(board, sideToEvaluate) * -0.3;

    return evaluation;
}
double Evaluation::Evaluate(const Board &board)
{

    return EvaluateSide(board, PieceColors::white) - EvaluateSide(board, PieceColors::black);
    //evaluate black and white
}
