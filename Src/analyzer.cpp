#include "analyzer.h"
#include "math.h"
#include "board.h"
#include <cmath>
bool Analyzer::IsPieceMovementBlocked(Board board, PieceName pieceName, PieceColors pieceColor, Square from, Square to)
{
    bool pieceMovementIsBlocked = false;
    Vector2 moveDir = Vector2::Direction(Vector2(from.fileNum, from.rankNum), Vector2(to.fileNum, to.rankNum));
    switch (pieceName)
    {
    case PieceName::pawn:
        if (pieceColor == PieceColors::white)
        {
            if (moveDir.x == 0 && moveDir.y == 1)
            {
                pieceMovementIsBlocked = board.board[to.rankNum - 1][to.fileNum - 1] != EMPTYSQUARE;
            }
        }
        else if (pieceColor == PieceColors::black)
        {
            if (moveDir.x == 0 && moveDir.y == -1)
            {
                pieceMovementIsBlocked = board.board[to.rankNum - 1][to.fileNum - 1] != EMPTYSQUARE;
            }
        }
        break;
    case PieceName::bishop:
        Vector2 unitDir = Vector2((moveDir.x / abs(moveDir.x)), (moveDir.y / abs(moveDir.y)));
        int rankNumIterator = from.rankNum + unitDir.y;
        int fileNumIterator = from.fileNum + unitDir.x;
        for (int i = 0; i <= abs(moveDir.x) - 2; i++)
        {
            if (board.board[rankNumIterator - 1][fileNumIterator - 1] != EMPTYSQUARE)
            {
                pieceMovementIsBlocked = true;
                break;
            }
            rankNumIterator += unitDir.y;
            fileNumIterator += unitDir.x;
        }
        break;
    }
    return pieceMovementIsBlocked;
}