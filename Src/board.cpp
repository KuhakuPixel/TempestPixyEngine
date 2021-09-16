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
        throw std::invalid_argument("invalid file value ,must be in between A and H (inclusive)\n");
    }
    if (rankNum > 0 && rankNum <= 8)
    {
        this->rankNum = rankNum;
    }
    else
    {
        throw std::invalid_argument("invalid rank value ,must be in between 1 and 8 (inclusive)\n");
    }
    this->file = file;
    this->rank = rank;
}
std::string Square::GetBoardNotation()
{
    return std::string() + this->file + this->rank;
}
void Board::PlaceOnBoard(char piece, Square square)
{
    board[square.rankNum - 1][square.fileNum - 1] = piece;
}
MoveFlag Board::GetMoveFlag(const Board &board, PieceName pieceName, Square from, Square to)
{
    MoveFlag moveFlag = MoveFlag::normal;
    std::string move = from.GetBoardNotation() + to.GetBoardNotation();
    if (pieceName == PieceName::king)
    {
        if (board.currentTurn == PieceColors::white)
        {
            if (move == "e1g1")
            {
                moveFlag = MoveFlag::shortCastle;
            }
            else if (move == "e1c1")
            {
                moveFlag = MoveFlag::longCastle;
            }
        }
        else if (board.currentTurn == PieceColors::black)
        {
            if (move == "e8g8")
            {
                moveFlag = MoveFlag::shortCastle;
            }
            else if (move == "e8c8")
            {
                moveFlag = MoveFlag::longCastle;
            }
        }
    }
    return moveFlag;
}
void Board::LoadBoard(char board[8][8])
{
    memcpy(this->board, board, sizeof(char) * 8 * 8);
}
void Board::LoadFromFen(std::string fen)
{
}
std::string Board::ExportFen()
{
    return "";
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
bool Board::IsMoveLegal(PieceName pieceName, PieceColors pieceColor, Square from, Square to)
{
    bool isMoveLegal = true;
    if (pieceName == PieceName::null)
        return false;

    //check if the current side move their own piece
    isMoveLegal &= (currentTurn == pieceColor);

    //check if piece 's move is according to the rule
    Vector2 moveDir = Vector2::Direction(Vector2(from.fileNum, from.rankNum), Vector2(to.fileNum, to.rankNum));
    printf("move dir x %d y %d\n", moveDir.x, moveDir.y);
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
            bool pawnCapture = moveDir.x == 1 && moveDir.y == 1;
            isMoveLegal &= pawnMoveOneSquare || pawnMoveTwoSquare || pawnCapture;
        }
        else if (pieceColor == PieceColors::black)
        {
            bool pawnMoveOneSquare = moveDir.y == -1 && moveDir.x == 0;
            bool pawnMoveTwoSquare = moveDir.y == -2 && from.rankNum == 7 && moveDir.x == 0;
            bool pawnCapture = moveDir.x == -1 && moveDir.y == -1;
            isMoveLegal &= pawnMoveOneSquare || pawnMoveTwoSquare || pawnCapture;
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

bool Board::IsMoveLegal(PieceName pieceName, PieceColors pieceColor, std::string moveNotation)
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
    return this->IsMoveLegal(pieceName, pieceColor, fromSquare, toSquare);
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
    PieceName pieceName = pieceAbbreviationsToPieceNameMapping.at(pieceToMove);
    PieceColors pieceColor = pieceAbbreviationsToPieceColorMapping.at(pieceToMove);
    if (IsMoveLegal(pieceName, pieceColor, fromSquare, toSquare) || allowIllegalMove)
    {
        MoveFlag moveFlag = this->GetMoveFlag(*this, pieceName, fromSquare, toSquare);
        switch (moveFlag)
        {
        case MoveFlag::normal:
        {
            this->PlaceOnBoard(EMPTYSQUARE, fromSquare);
            this->PlaceOnBoard(pieceToMove, toSquare);
            break;
        }
        case MoveFlag::shortCastle:
        {
            if (pieceColor == PieceColors::white)
            {
                this->PlaceOnBoard(EMPTYSQUARE, fromSquare);
                this->PlaceOnBoard('K', toSquare);
                this->PlaceOnBoard(EMPTYSQUARE, Square('h', '1'));
                this->PlaceOnBoard('R', Square('f', '1'));
            }
            else if (pieceColor == PieceColors::black)
            {
                this->PlaceOnBoard(EMPTYSQUARE, fromSquare);
                this->PlaceOnBoard('k', toSquare);
                this->PlaceOnBoard(EMPTYSQUARE, Square('h', '8'));
                this->PlaceOnBoard('r', Square('f', '8'));
            }
            break;
        }
        case MoveFlag::longCastle:
        {
            if (pieceColor == PieceColors::white)
            {
                this->PlaceOnBoard(EMPTYSQUARE, fromSquare);
                this->PlaceOnBoard('K', toSquare);
                this->PlaceOnBoard(EMPTYSQUARE, Square('a', '1'));
                this->PlaceOnBoard('R', Square('d', '1'));
            }
            else if (pieceColor == PieceColors::black)
            {
                this->PlaceOnBoard(EMPTYSQUARE, fromSquare);
                this->PlaceOnBoard('k', toSquare);
                this->PlaceOnBoard(EMPTYSQUARE, Square('a', '8'));
                this->PlaceOnBoard('r', Square('d', '8'));
            }
            break;
        }
        }
        printf("piece to move : %c\n", pieceToMove);

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
