#include "search.h"
#include "analyzer.h"
#include "evaluation.h"
#include <limits>
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
/// This function has no PieceColors parameter because it it will know for certain what piece color at the given square
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
                    if ((sideToMove == PieceColors::white && toRankNum == 8) ||
                        (sideToMove == PieceColors::black && toRankNum == 1))
                    {
                        if (Analyzer::IsMoveLegal(board, from, to, false, PieceName::queen))
                        {
                            moves.push_back(from.GetNotation() + to.GetNotation() + "q");
                            moves.push_back(from.GetNotation() + to.GetNotation() + "n");
                            moves.push_back(from.GetNotation() + to.GetNotation() + "b");
                            moves.push_back(from.GetNotation() + to.GetNotation() + "r");
                        }
                    }
                    else
                    {
                        if (Analyzer::IsMoveLegal(board, from, to, false))
                            moves.push_back(from.GetNotation() + to.GetNotation());
                    }
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

/// Generate all possible moves for either white or black
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
double Search::SearchPosition(const Board &board, const Evaluation &evaluation, int currentDepth, int maxDepth, double alpha, double beta, std::string *bestMove)
{
    std::string currentBestMove = "EMPTY";
    PieceColors sideToMove = board.GetCurrentTurn();
    // initialize the best value (will always be initialized to the worst depending on the side to move)
    double bestValue = (sideToMove == PieceColors::white)
                           ? -std::numeric_limits<double>::infinity()
                           : std::numeric_limits<double>::infinity();
    // if the current depth hasn't reached the maxDepth yet then continue recursively
    if (currentDepth < maxDepth)
    {
        std::vector<std::string> generatedMoves = Search::GenerateMoves(board, sideToMove);
        for (int i = 0; i < generatedMoves.size(); i++)
        {
            // move newBoard
            Board newBoard = Board(board);
            newBoard.Move(generatedMoves.at(i), false);
            double newPositionValue = SearchPosition(newBoard, evaluation, currentDepth + 1, maxDepth, alpha, beta);
            // choose the best value and best move according to the sideToMove
            if (sideToMove == PieceColors::white)
            {
                if (newPositionValue >= bestValue)
                {
                    bestValue = newPositionValue;
                    alpha = newPositionValue;
                    currentBestMove = generatedMoves.at(i);
                    // Alpha Beta Pruning
                    if (bestValue >= beta)
                        break;
                }
            }
            else if (sideToMove == PieceColors::black)
            {
                if (newPositionValue <= bestValue)
                {
                    bestValue = newPositionValue;
                    beta = newPositionValue;
                    currentBestMove = generatedMoves.at(i);
                    // Alpha Beta Pruning
                    if (bestValue <= alpha)
                        break;
                }
            }
            // printf("Evaluating %s Move %s has an evaluation of %f at depth %d\n", ChessLib::GetPieceColorStr(sideToMove).c_str(), generatedMoves.at(i).c_str(), newPositionValue, currentDepth + 1);
        }
        if (currentDepth == 0)
            *bestMove = currentBestMove;
    }
    // recursion will stop here once the max depth is reached
    else if (currentDepth == maxDepth)
        return evaluation.Evaluate(board);

    return bestValue;
}