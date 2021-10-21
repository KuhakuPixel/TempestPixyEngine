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
    //initialize piecesSquaresValue
    for (int i = (int)PieceName::pawn; i <= (int)PieceName::king; i++)
    {
        PieceName piece = static_cast<PieceName>(i);
        for (int i = (int)ESquare::A1; i <= (int)ESquare::H8; i++)
        {
            ESquare eSquare = static_cast<ESquare>(i);
            this->piecesSquaresValue[piece][eSquare] = 0;
        }
    }
}
void Evaluation::SetPieceSquareValue(PieceName pieceName, std::string squareStr, double value)
{
    ESquare eSquare = ChessLib::ToESquare(squareStr);
    this->piecesSquaresValue[pieceName][eSquare] = value;
}
void Evaluation::InitializeKnightPeriphery0(double value)
{
    for (int i = 0; i < 7; i++)
    {
        // a1 to h1
        this->piecesSquaresValue[PieceName::knight][static_cast<ESquare>(i)] = value;
        // a8 to h8
        this->piecesSquaresValue[PieceName::knight][static_cast<ESquare>(56 + i)] = value;
        // a1 to a8
        this->piecesSquaresValue[PieceName::knight][static_cast<ESquare>(i * 8)] = value;
        // h1 to h8
        this->piecesSquaresValue[PieceName::knight][static_cast<ESquare>((i * 8) + 7)] = value;
    }
}
void Evaluation::InitializeKnightPeriphery1(double value)
{
    for (int i = 0; i < 6; i++)
    {
        // b2 to g2
        this->piecesSquaresValue[PieceName::knight][static_cast<ESquare>(9 + i)] = value;
        // b7 to g7
        this->piecesSquaresValue[PieceName::knight][static_cast<ESquare>(49 + i)] = value;
        // b2 to b7
        this->piecesSquaresValue[PieceName::knight][static_cast<ESquare>(i * 8 + 9)] = value;
        // g2 to g7
        this->piecesSquaresValue[PieceName::knight][static_cast<ESquare>(i * 8 + 14)] = value;
    }
}
void Evaluation::InitializeKnightPeriphery2(double value)
{
    for (int i = 0; i < 4; i++)
    {
        // c3 to f3
        this->piecesSquaresValue[PieceName::knight][static_cast<ESquare>(18 + i)] = value;
        // c6 to f6
        this->piecesSquaresValue[PieceName::knight][static_cast<ESquare>(42 + i)] = value;
        // c3 to c6
        this->piecesSquaresValue[PieceName::knight][static_cast<ESquare>(i * 8 + 18)] = value;
        // f3 to f6
        this->piecesSquaresValue[PieceName::knight][static_cast<ESquare>(i * 8 + 21)] = value;
    }
}
void Evaluation::InitializeKnightPeriphery3(double value)
{
    //center
    this->piecesSquaresValue[PieceName::knight][ESquare::E4] = value;
    this->piecesSquaresValue[PieceName::knight][ESquare::D4] = value;
    this->piecesSquaresValue[PieceName::knight][ESquare::E5] = value;
    this->piecesSquaresValue[PieceName::knight][ESquare::D5] = value;
}

const std::map<PieceName, double> Evaluation::pieceNameToValueMap = {
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
    const Board &board, EvaluationVector &evaluationVector, PieceColors pieceColor, int fileNum, int rankNum) const
{
    ESquare eSquare = ChessLib::ToESquare(fileNum, rankNum);
    double squareValue = this->piecesSquaresValue.at(PieceName::knight).at(eSquare);
    evaluationVector.IncrementEvaluation(pieceColor, squareValue);
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
                    EvaluateKnight(board, evalVector, pieceColor, fileItr, rankItr);
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
