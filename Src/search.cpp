#include "search.h"
#include "analyzer.h"
#include "evaluation.h"
#include <limits>
SearchNode::SearchNode(const Board &currentBoard, PieceColors sideToMove, std::string move)
    : currentBoard(currentBoard),
      sideToMove(sideToMove),
      move(move){};

const std::map<PieceName, std::vector<Vector2>> Search::pieceToMoveVectorMap = {
    {
        PieceName::pawn,
        {
            Vector2(0, 1),
            Vector2(0, 2),
            Vector2(1, 1),
            Vector2(-1, 1),
        },
    },
    {
        PieceName::knight,
        {
            Vector2(1, 2),
            Vector2(2, 1),
            Vector2(-1, 2),
            Vector2(-2, 1),

            Vector2(1, -2),
            Vector2(2, -1),
            Vector2(-1, -2),
            Vector2(-2, -1),
        },
    },
    {
        PieceName::bishop,
        {
            Vector2(1, 1),
            Vector2(1, -1),
            Vector2(-1, 1),
            Vector2(-1, -1),
        },
    },
    {
        PieceName::rook,
        {
            Vector2(0, 1),
            Vector2(0, -1),
            Vector2(1, 0),
            Vector2(-1, 0),
        },
    },
    {
        PieceName::queen,
        {
            Vector2(1, 1),
            Vector2(1, -1),
            Vector2(-1, 1),
            Vector2(-1, -1),
            Vector2(0, 1),
            Vector2(0, -1),
            Vector2(1, 0),
            Vector2(-1, 0),
        },
    },
    {
        PieceName::king,
        {
            Vector2(0, 1),
            Vector2(0, -1),
            Vector2(1, 0),
            Vector2(-1, 0),
            Vector2(1, 1),
            Vector2(1, -1),
            Vector2(-1, 1),
            Vector2(-1, -1),

        },
    },
};

std::vector<std::string> Search::GeneratePieceLegalMoves(const Board &board, int fileNum, int rankNum)
{
    std::vector<std::string> moves = {};
    if (!board.IsSquareEmpty(fileNum, rankNum))
    {
        PieceName pieceName = board.GetPieceNameEnum(fileNum, rankNum);
        PieceColors sideToMove = board.GetPieceColor(fileNum, rankNum);
        Square from = Square(fileNum, rankNum);
        std::vector<Vector2> moveVectors = Search::pieceToMoveVectorMap.at(pieceName);
        if (pieceName == PieceName::pawn)
        {
            for (int i = 0; i < moveVectors.size(); i++)
            {
                int toFileNum = from.fileNum + moveVectors.at(i).x;
                int toRankNum = sideToMove == PieceColors::white ? (from.rankNum + moveVectors.at(i).y * 1) : (from.rankNum + moveVectors.at(i).y * -1);
                if (toFileNum >= 1 && toFileNum <= 8 && toRankNum >= 1 && toRankNum <= 8)
                {
                    Square to = Square(toFileNum, toRankNum);
                    if (Analyzer::IsMoveLegal(board, from, to, false))
                        moves.push_back(from.GetNotation() + to.GetNotation());
                }
            }
        }
        else
        {
            for (int i = 0; i < moveVectors.size(); i++)
            {
                int toFileNum = from.fileNum + moveVectors.at(i).x;
                int toRankNum = from.rankNum + moveVectors.at(i).y;
                while (toFileNum >= 1 && toFileNum <= 8 && toRankNum >= 1 && toRankNum <= 8)
                {
                    Square to = Square(toFileNum, toRankNum);
                    if (Analyzer::IsMoveLegal(board, from, to, false))
                        moves.push_back(from.GetNotation() + to.GetNotation());
                    if (pieceName == PieceName::king || pieceName == PieceName::knight)
                    {
                        break;
                    }
                    else if (pieceName == PieceName::bishop || pieceName == PieceName::rook || pieceName == PieceName::queen)
                    {
                        toFileNum += moveVectors.at(i).x;
                        toRankNum += moveVectors.at(i).y;
                    }
                }
            }
        }
    }
    return moves;
}
std::vector<std::string> Search::GenerateMoves(const Board &board, PieceColors sideToMove)
{
    std::vector<std::string> moves = {};
    for (int rankItr = 1; rankItr <= 8; rankItr++)
    {
        for (int fileItr = 1; fileItr <= 8; fileItr++)
        {
            if (board.GetPieceColor(fileItr, rankItr) == sideToMove &&
                !board.IsSquareEmpty(fileItr, rankItr))
            {
                std::vector<std::string> pieceLegalMoves = Search::GeneratePieceLegalMoves(board, fileItr, rankItr);
                moves.insert(moves.end(), pieceLegalMoves.begin(), pieceLegalMoves.end());
            }
        }
    }
    return moves;
}

double Search::SearchPosition(const Board &board, const Evaluation &evaluation, int currentDepth, int maxDepth)
{

    std::string bestMove = "EMPTY";
    PieceColors sideToMove = board.GetCurrentTurn();
    double bestValue = (sideToMove == PieceColors::white) ? -std::numeric_limits<double>::infinity() : std::numeric_limits<double>::infinity();
    if (currentDepth < maxDepth)
    {
        std::vector<std::string> generatedMoves = Search::GenerateMoves(board, sideToMove);
        for (int i = 0; i < generatedMoves.size(); i++)
        {
            Board tempBoard = Board(board);
            tempBoard.Move(generatedMoves.at(i), false);
            if (sideToMove == PieceColors::white)
            {
                double value = SearchPosition(board, evaluation, currentDepth + 1, maxDepth);
                if (value > bestValue)
                {
                    bestValue = value;
                    bestMove = generatedMoves.at(i);
                }
                printf("Evaluating %s Move %s has an evaluation of %f at depth %d\n", ChessLib::GetPieceColorStr(sideToMove).c_str(), generatedMoves.at(i).c_str(), value, currentDepth);
            }
            else if (sideToMove == PieceColors::black)
            {
                double value = SearchPosition(board, evaluation, currentDepth + 1, maxDepth);
                if (value < bestValue)
                {
                    bestValue = value;
                    bestMove = generatedMoves.at(i);
                }
                printf("Evaluating %s Move %s has an evaluation of %f at depth %d\n", ChessLib::GetPieceColorStr(sideToMove).c_str(), generatedMoves.at(i).c_str(), value, currentDepth);
            }
        }
        if (currentDepth == 0)
            printf("Best move for %s is %s\n", ChessLib::GetPieceColorStr(sideToMove).c_str(), bestMove.c_str());
        return bestValue;
    }
    else if (currentDepth == maxDepth)
    {
        bestValue = evaluation.Evaluate(board);
    }
    return bestValue;
}