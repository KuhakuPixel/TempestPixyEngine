#include "search.h"
#include "analyzer.h"
#include "tree.hh"
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
                if (piece == PieceName::pawn)
                {
                    for (int i = 0; i < moveVectors.size(); i++)
                    {
                        int toFileNum = from.fileNum + moveVectors.at(i).x;
                        int toRankNum = sideToMove == PieceColors::white ? (from.rankNum + moveVectors.at(i).y * 1) : (from.rankNum + moveVectors.at(i).y * -1);
                        if (toFileNum >= 1 && toFileNum <= 8 && toRankNum >= 1 && toRankNum <= 8)
                        {
                            Square to = Square(toFileNum, toRankNum);
                            if (Analyzer::IsMoveLegal(board, from, to))
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
                            if (Analyzer::IsMoveLegal(board, from, to))
                                moves.push_back(from.GetNotation() + to.GetNotation());
                            else
                                break;
                            toFileNum += moveVectors.at(i).x;
                            toRankNum += moveVectors.at(i).y;
                        }
                    }
                }
            }
        }
    }
    return moves;
}

/*
int Search::SearchMoves(const Board &board, PieceColors sideToMove, int maxDepth)
{
    tree<SearchNode> searchTrees;
    auto head = searchTrees.set_head(SearchNode(board, sideToMove, ""));
    std::vector<tree<SearchNode>::pre_order_iterator> previousNodes = {};
    previousNodes.push_back(head);
    for (int currentDepth = 0; currentDepth <= maxDepth; currentDepth++)
    {
        std::vector<tree<SearchNode>::pre_order_iterator> currentNodes = {};
        for (int j = 0; j < previousNodes.size(); j++)
        {
            std::vector<std::string> moves = Search::GenerateMoves(board, sideToMove);
            for (int k = 0; k < moves.size(); k++)
            {
                auto searchNodeItr = searchTrees.append_child(head, SearchNode(board, sideToMove, moves.at(k)));
                currentNodes.push_back(searchNodeItr);
            }
        }
        previousNodes.clear();
        previousNodes = currentNodes;
    }
    return -1;
}
*/