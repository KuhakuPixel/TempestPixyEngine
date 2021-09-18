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

                pieceMovementIsBlocked = board.GetPieceName(to) != EMPTYSQUARE;
            }
        }
        else if (pieceColor == PieceColors::black)
        {
            if (moveDir.x == 0 && moveDir.y == -1)
            {
                pieceMovementIsBlocked = board.GetPieceName(to) != EMPTYSQUARE;
            }
        }
        break;
    case PieceName::bishop:
    {
        Vector2 unitDir = Vector2((moveDir.x / abs(moveDir.x)), (moveDir.y / abs(moveDir.y)));
        int rankNumIterator = from.rankNum + unitDir.y;
        int fileNumIterator = from.fileNum + unitDir.x;
        for (int i = 0; i <= abs(moveDir.x) - 2; i++)
        {
            if (board.GetPieceName(fileNumIterator, rankNumIterator) != EMPTYSQUARE)
            {
                pieceMovementIsBlocked = true;
                break;
            }
            rankNumIterator += unitDir.y;
            fileNumIterator += unitDir.x;
        }
        break;
    }
    case PieceName::rook:
    {
        int unitDirX = moveDir.x == 0 ? 0 : (moveDir.x / abs(moveDir.x));
        int unitDirY = moveDir.y == 0 ? 0 : (moveDir.y / abs(moveDir.y));
        Vector2 unitDir = Vector2(unitDirX, unitDirY);

        int distanceSquare = 0;
        distanceSquare = moveDir.x != 0 ? abs(moveDir.x) : abs(moveDir.y);

        int rankNumIterator = from.rankNum + unitDir.y;
        int fileNumIterator = from.fileNum + unitDir.x;
        for (int i = 0; i <= distanceSquare - 2; i++)
        {
            if (board.GetPieceName(fileNumIterator, rankNumIterator) != EMPTYSQUARE)
            {
                pieceMovementIsBlocked = true;
                break;
            }
            rankNumIterator += unitDir.y;
            fileNumIterator += unitDir.x;
        }
        break;
    }
    case PieceName::queen:
    {
        int unitDirX = moveDir.x == 0 ? 0 : (moveDir.x / abs(moveDir.x));
        int unitDirY = moveDir.y == 0 ? 0 : (moveDir.y / abs(moveDir.y));
        Vector2 unitDir = Vector2(unitDirX, unitDirY);

        int distanceSquare = 0;
        distanceSquare = moveDir.x != 0 ? abs(moveDir.x) : abs(moveDir.y);
        int rankNumIterator = from.rankNum + unitDir.y;
        int fileNumIterator = from.fileNum + unitDir.x;
        for (int i = 0; i <= distanceSquare - 2; i++)
        {
            if (board.GetPieceName(fileNumIterator, rankNumIterator) != EMPTYSQUARE)
            {
                pieceMovementIsBlocked = true;
                break;
            }
            rankNumIterator += unitDir.y;
            fileNumIterator += unitDir.x;
        }
        break;
    }
    }

    return pieceMovementIsBlocked;
}
bool Analyzer::DoesPieceMoveAccordingToRule(Board board, PieceName pieceName, PieceColors pieceColor, Square from, Square to)
{
    bool isMoveLegal = true;
    if (pieceName == PieceName::null)
        return false;
    //check if piece 's move is according to the rule
    Vector2 moveDir = Vector2::Direction(Vector2(from.fileNum, from.rankNum), Vector2(to.fileNum, to.rankNum));
    //printf("move dir x %d y %d\n", moveDir.x, moveDir.y);
    int xAbs = std::abs(moveDir.x);
    int yAbs = std::abs(moveDir.y);
    switch (pieceName)
    {
    case PieceName::knight:
        isMoveLegal &= ((xAbs == 1 && yAbs == 2) ||
                        (xAbs == 2 && yAbs == 1));
        break;
    case PieceName::rook:
        isMoveLegal &= ((moveDir.x == 0 && yAbs > 0) || (xAbs > 0 && moveDir.y == 0));
        break;

    case PieceName::bishop:
        isMoveLegal &= ((xAbs > 0 && yAbs > 0) && (xAbs == yAbs));

        break;
    case PieceName::king:
    {
        bool isNormalKingMove = (xAbs == 1 && yAbs == 0) || (yAbs == 1 && xAbs == 0) || (xAbs == 1 && yAbs == 1);
        bool isCastlingMove = (xAbs == 2 && yAbs == 0);
        isMoveLegal &= isNormalKingMove || isCastlingMove;

        break;
    }

    case PieceName::queen:
    {
        bool rookMove = ((moveDir.x == 0 && yAbs > 0) || (xAbs > 0 && moveDir.y == 0));
        bool bishopMove = (xAbs > 0 && yAbs > 0) && (xAbs == yAbs);
        isMoveLegal &= rookMove || bishopMove;
        break;
    }

    case PieceName::pawn:

        if (pieceColor == PieceColors::white)
        {
            bool pawnMoveOneSquare = moveDir.y == 1 && moveDir.x == 0;
            bool pawnMoveTwoSquare = moveDir.y == 2 && from.rankNum == 2 && moveDir.x == 0;
            bool pawnCapture = xAbs == 1 && moveDir.y == 1 && (board.GetPieceColor(to) == PieceColors::black);
            isMoveLegal &= pawnMoveOneSquare || pawnMoveTwoSquare || pawnCapture;
        }
        else if (pieceColor == PieceColors::black)
        {
            bool pawnMoveOneSquare = moveDir.y == -1 && moveDir.x == 0;
            bool pawnMoveTwoSquare = moveDir.y == -2 && from.rankNum == 7 && moveDir.x == 0;
            bool pawnCapture = xAbs == 1 && moveDir.y == -1 && (board.GetPieceColor(to) == PieceColors::white);
            isMoveLegal &= pawnMoveOneSquare || pawnMoveTwoSquare || pawnCapture;
        }

        break;

    default:
        printf("piece is invalid \n");
        isMoveLegal &= false;
        break;
    }
    return isMoveLegal;
}
bool Analyzer::IsSquareUnderAttack(Board board, PieceColors enemyPieceColor, Square square)
{
    for (int rankItr = 1; rankItr <= 8; rankItr++)
    {
        for (int fileItr = 1; fileItr <= 8; fileItr++)
        {
            if (board.GetPieceColor(fileItr, rankItr) == enemyPieceColor)
            {
                //PieceName piece = board.GetPieceName(fileItr, rankItr);
                //return Analyzer::IsPieceMovementBlocked(board, );
            }
        }
    }

    return false;
}
