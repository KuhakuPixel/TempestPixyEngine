#include "board.h"
#include <string>
#include <iostream>
#include <ctype.h>
#include <stdexcept>
#include "CharHelper.h"
#include "math.h"
#include <cmath>
#include <map>
#include <string.h>
#include "analyzer.h"
#define EMPTYSQUARE '-'

Piece::Piece(PieceName pieceName, PieceColors pieceColor)
{
    this->pieceName = pieceName;
    this->pieceColor = pieceColor;
}
Square::Square(char file, char rank)
{
    int fileNum = CharHelper::ToAlphabetIndex(file) + 1;
    int rankNum = CharHelper::ToInt(rank);
    if (fileNum > 0 && fileNum <= 8)
    {
        this->fileNum = fileNum;
    }
    else
    {
        throw std::invalid_argument("invalid file value ,must be in between A and H (inclusive)");
    }
    if (rankNum > 0 && rankNum <= 8)
    {
        this->rankNum = rankNum;
    }
    else
    {
        throw std::invalid_argument("invalid rank value ,must be in between 1 and 8 (inclusive)");
    }
    this->file = file;
    this->rank = rank;
}
void Board::LoadBoard(char board[8][8])
{
    memcpy(this->board, board, sizeof(char) * 8 * 8);
}
void Board::LoadFromFen(std::string fen)
{
}
void Board::DisplayBoard(char orientation)
{
    printf("    A  B  C  D  E  F  G  H\n\n");
    if (orientation == 'b')
    {
        for (int i = 0; i < 8; i++)
        {
            printf("%d  ", i + 1);
            for (int j = 0; j < 8; j++)
            {
                printf(" %c ", board[i][j]);
            }

            printf("\n");
        }
    }
    else if (orientation == 'w')
    {
        for (int i = 0; i < 8; i++)
        {
            printf("%d  ", 8 - i);
            for (int j = 0; j < 8; j++)
            {
                printf(" %c ", board[7 - i][j]);
            }

            printf("\n");
        }
    }

    printf("\n    A  B  C  D  E  F  G  H\n");
}
bool Board::IsMoveLegal(char piece, Square from, Square to)
{
    bool isMoveLegal = true;
    if (piece == EMPTYSQUARE)
        return false;

    PieceName pieceName = pieceAbbreviationsToPieceNameMapping.at(piece);
    PieceColors pieceColor = pieceAbbreviationsToPieceColorMapping.at(piece);
    //check if the current side move their own piece
    isMoveLegal &= (currentTurn == pieceColor);

    //check if piece 's move is according to the rule
    Vector2 moveDir = Vector2::Direction(Vector2(from.fileNum, from.rankNum), Vector2(to.fileNum, to.rankNum));
    printf("move dir x %d y %d\n", moveDir.x, moveDir.y);
    int xAbs = std::abs(moveDir.x);
    int yAbs = std::abs(moveDir.y);

    switch (tolower(piece))
    {
    case 'n':
        isMoveLegal &= ((xAbs == 1 && yAbs == 2) ||
                        (xAbs == 2 && yAbs == 1));

        break;
    case 'r':
        isMoveLegal &= ((moveDir.x == 0 && yAbs > 0) || (xAbs > 0 && moveDir.y == 0));
        break;

    case 'b':
        isMoveLegal &= ((xAbs > 0 && yAbs > 0) && (xAbs == yAbs));

        break;
    case 'k':
        isMoveLegal &= ((xAbs == 1 && yAbs == 0) || (yAbs == 1 && xAbs == 0) || (xAbs == 1 && yAbs == 1));

        break;
    case 'q':
        isMoveLegal &= (((moveDir.x == 0 && yAbs > 0) || (xAbs > 0 && moveDir.y == 0)) ||
                        (xAbs > 0 && yAbs > 0) && (xAbs == yAbs));
    case 'p':
        if (pieceColor == PieceColors::white)
        {

            isMoveLegal &= ((moveDir.y == 1 || (moveDir.y == 2 && from.rankNum == 2)) || (moveDir.x == 1 && moveDir.y == 1));
        }
        else if (pieceColor == PieceColors::black)
        {
            isMoveLegal &= ((moveDir.y == -1 || (moveDir.y == -2 && from.rankNum == 7)) || (moveDir.x == -1 && moveDir.y == -1));
        }

        break;

    default:
        printf("piece is invalid \n");
        isMoveLegal &= false;
        break;
    }

    //check if the piece move to a square that is occupied by their own piece
    if (board[to.rankNum - 1][to.fileNum - 1] != EMPTYSQUARE)
    {
        isMoveLegal &= !(pieceAbbreviationsToPieceColorMapping.at(board[to.rankNum - 1][to.fileNum - 1]) == currentTurn);
    }
    //check if something is blocking the movement
    isMoveLegal &= !(Analyzer::IsPieceMovementBlocked(*this, pieceName, pieceColor, from, to));
    return isMoveLegal;
}
void Board::Move(std::string moveNotation, bool allowIllegalMove)
{
    if (moveNotation.size() < 4)
    {
        throw std::invalid_argument("move size must be at least 4");
    }
    if (isdigit(moveNotation[0]) || !isdigit(moveNotation[1]) ||
        isdigit(moveNotation[2]) || !isdigit(moveNotation[3]))
    {
        throw std::invalid_argument("invalid move notation");
    }
    Square fromSquare = Square(moveNotation[0], moveNotation[1]);
    Square toSquare = Square(moveNotation[2], moveNotation[3]);
    char pieceToMove = board[fromSquare.rankNum - 1][fromSquare.fileNum - 1];
    if (IsMoveLegal(pieceToMove, fromSquare, toSquare) || allowIllegalMove)
    {
        printf("piece to move : %c\n", pieceToMove);
        board[fromSquare.rankNum - 1][fromSquare.fileNum - 1] = EMPTYSQUARE;
        board[toSquare.rankNum - 1][toSquare.fileNum - 1] = pieceToMove;
        if (currentTurn == PieceColors::white)
        {
            this->currentTurn = PieceColors::black;
        }
        else
        {
            this->currentTurn = PieceColors::white;
        }
    }
    else
    {
        printf("move is not legal,try again\n");
    }
}
