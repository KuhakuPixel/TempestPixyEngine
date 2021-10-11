#include "evaluation.h"

const std::map<PieceName, int> Evaluation::pieceNameToValue = {
    {PieceName::pawn, 1},
    {PieceName::bishop, 3},
    {PieceName::knight, 3},
    {PieceName::rook, 5},
    {PieceName::queen, 9},
};
int Evaluation::EvaluateMaterial(const Board &board, PieceColors sideToEvaluate)
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

int Evaluation::Evaluate(const Board &board)
{
    return -1;
    //evaluate black and white
}
