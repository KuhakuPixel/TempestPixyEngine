#include "search.h"

std::vector<std::string> Search::SearchPosition(const Board &board, PieceColors sideToMove)
{
    std::vector<std::string> moves = {};
    //iterate if bishops? if pawn if queen bla bla bla
    for (int rankItr = 1; rankItr <= 8; rankItr++)
    {

        for (int fileItr = 1; fileItr <= 8; fileItr++)
        {
            if (board.GetPieceColorFromBoard(fileItr, rankItr) == sideToMove &&
                !board.IsSquareEmpty(fileItr, rankItr))
            {
                //fuck search for move
                PieceName piece = board.GetPieceNameEnumFromBoard(fileItr, rankItr);
                switch (piece)
                {
                case PieceName::knight:

                    break;
                case PieceName::rook:

                    break;

                case PieceName::bishop:

                    break;
                case PieceName::king:
                {

                    break;
                }

                case PieceName::queen:
                {

                    break;
                }

                case PieceName::pawn:

                    break;

                default:
                    break;
                }
            }
        }
    }
    return moves;
}