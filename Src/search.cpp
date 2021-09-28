#include "search.h"
#include "analyzer.h"
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

std::vector<std::string> Search::GenerateMoves(const Board &board, PieceColors sideToMove)
{
    std::vector<std::string> moves = {};
    for (int rankItr = 1; rankItr <= 8; rankItr++)
    {
        for (int fileItr = 1; fileItr <= 8; fileItr++)
        {
            if (board.GetPieceColorFromBoard(fileItr, rankItr) == sideToMove &&
                !board.IsSquareEmpty(fileItr, rankItr))
            {
                Square from = Square(fileItr, rankItr);

                PieceName piece = board.GetPieceNameEnumFromBoard(fileItr, rankItr);
                std::vector<Vector2> moveVectors = pieceToMoveVectorMap.at(piece);
                switch (piece)
                {
                case PieceName::pawn:
                {
                    if (sideToMove == PieceColors::white)
                    {
                        for (int i = 0; i < moveVectors.size(); i++)
                        {
                            int toFileNum = from.fileNum + moveVectors.at(i).x;
                            int toRankNum = from.rankNum + moveVectors.at(i).y;
                            if (toFileNum >= 1 && toFileNum <= 8 && toRankNum >= 1 && toRankNum <= 8)
                            {
                                Square to = Square(toFileNum, toRankNum);
                                if (Analyzer::IsMoveLegal(board, from, to))
                                    moves.push_back(from.GetNotation() + to.GetNotation());
                            }
                        }
                    }
                    if (sideToMove == PieceColors::black)
                    {
                        for (int i = 0; i < moveVectors.size(); i++)
                        {
                            int toFileNum = from.fileNum + moveVectors.at(i).x;
                            int toRankNum = from.rankNum + moveVectors.at(i).y * -1;
                            if (toFileNum >= 1 && toFileNum <= 8 && toRankNum >= 1 && toRankNum <= 8)
                            {
                                Square to = Square(toFileNum, toRankNum);
                                if (Analyzer::IsMoveLegal(board, from, to))
                                    moves.push_back(from.GetNotation() + to.GetNotation());
                            }
                        }
                    }
                    break;
                }

                case PieceName::knight:
                {
                    for (int i = 0; i < moveVectors.size(); i++)
                    {
                        int toFileNum = from.fileNum + moveVectors.at(i).x;
                        int toRankNum = from.rankNum + moveVectors.at(i).y;
                        if (toFileNum >= 1 && toFileNum <= 8 && toRankNum >= 1 && toRankNum <= 8)
                        {
                            Square to = Square(toFileNum, toRankNum);
                            if (Analyzer::IsMoveLegal(board, from, to))
                                moves.push_back(from.GetNotation() + to.GetNotation());
                        }
                    }
                    break;
                }

                case PieceName::rook:
                {
                    for (int i = 0; i < moveVectors.size(); i++)
                    {
                        int toFileNum = from.fileNum + moveVectors.at(i).x;
                        int toRankNum = from.rankNum + moveVectors.at(i).y;
                        while (toFileNum >= 1 && toFileNum <= 8 && toRankNum >= 1 && toRankNum <= 8)
                        {
                            Square to = Square(toFileNum, toRankNum);
                            if (Analyzer::IsMoveLegal(board, from, to))
                                moves.push_back(from.GetNotation() + to.GetNotation());
                            else
                                break;
                            toFileNum += moveVectors.at(i).x;
                            toRankNum += moveVectors.at(i).y;
                        }
                    }
                    break;
                }

                case PieceName::bishop:
                {
                    for (int i = 0; i < moveVectors.size(); i++)
                    {
                        int toFileNum = from.fileNum + moveVectors.at(i).x;
                        int toRankNum = from.rankNum + moveVectors.at(i).y;
                        while (toFileNum >= 1 && toFileNum <= 8 && toRankNum >= 1 && toRankNum <= 8)
                        {
                            Square to = Square(toFileNum, toRankNum);
                            if (Analyzer::IsMoveLegal(board, from, to))
                                moves.push_back(from.GetNotation() + to.GetNotation());
                            else
                                break;
                            toFileNum += moveVectors.at(i).x;
                            toRankNum += moveVectors.at(i).y;
                        }
                    }
                    break;
                }

                case PieceName::king:
                {
                    for (int i = 0; i < moveVectors.size(); i++)
                    {
                        int toFileNum = from.fileNum + moveVectors.at(i).x;
                        int toRankNum = from.rankNum + moveVectors.at(i).y;
                        if (toFileNum >= 1 && toFileNum <= 8 && toRankNum >= 1 && toRankNum <= 8)
                        {
                            Square to = Square(toFileNum, toRankNum);
                            if (Analyzer::IsMoveLegal(board, from, to))
                                moves.push_back(from.GetNotation() + to.GetNotation());
                        }
                    }
                    break;
                }

                case PieceName::queen:
                {
                    for (int i = 0; i < moveVectors.size(); i++)
                    {
                        int toFileNum = from.fileNum + moveVectors.at(i).x;
                        int toRankNum = from.rankNum + moveVectors.at(i).y;
                        while (toFileNum >= 1 && toFileNum <= 8 && toRankNum >= 1 && toRankNum <= 8)
                        {
                            Square to = Square(toFileNum, toRankNum);
                            if (Analyzer::IsMoveLegal(board, from, to))
                                moves.push_back(from.GetNotation() + to.GetNotation());
                            else
                                break;
                            toFileNum += moveVectors.at(i).x;
                            toRankNum += moveVectors.at(i).y;
                        }
                    }
                    break;
                }

                default:
                    throw std::invalid_argument("Invalid Piece name");
                    break;
                }
            }
        }
    }
    return moves;
}