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
#include "stringHelper.h"
#include "chessLib.h"
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
Square::Square(int fileNum, int rankNum)
{
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
    this->rank = CharHelper::FromAlphabetIndex(rankNum - 1, false);
    this->file = static_cast<char>(fileNum);
}
void Board::ClearBoard()
{
    for (int rankItr = 1; rankItr <= 8; rankItr++)
    {
        for (int fileItr = 1; fileItr <= 8; fileItr++)
        {
            this->PlacePiece(EMPTYSQUARE, fileItr, rankItr);
        }
    }
}
PieceColors Board::GetCurrentTurn()
{
    return this->currentTurn;
}
std::string Board::GetCurrentTurnStr()
{
    return pieceColorStr[(int)this->GetCurrentTurn()];
}
std::string Square::GetBoardNotation()
{
    return std::string() + this->file + this->rank;
}

void Board::PlacePiece(char piece, int fileNum, int rankNum)
{
    board[8 - rankNum][fileNum - 1] = piece;
}
void Board::PlacePiece(char piece, Square square)
{
    this->PlacePiece(piece, square.fileNum, square.rankNum);
}

char Board::GetPieceNameFromBoard(int fileNum, int rankNum)
{
    return board[8 - rankNum][fileNum - 1];
}

char Board::GetPieceNameFromBoard(Square square)
{
    return this->GetPieceNameFromBoard(square.fileNum, square.rankNum);
}
PieceColors Board::GetPieceColorFromBoard(int fileNum, int rankNum)
{
    char piece = this->GetPieceNameFromBoard(fileNum, rankNum);

    return ChessLib::ToPieceColorEnum(piece);
}
PieceColors Board::GetPieceColorFromBoard(Square square)
{
    return this->GetPieceColorFromBoard(square.fileNum, square.rankNum);
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
    //example of a fen : "r1bqkbnr/pp2ppp1/2np3p/2p5/2B1P3/3PBN2/PPP2PPP/RN1QK2R b KQkq - 1 5"
    std::vector<std::string> fenSplitted = StringHelper::SplitString(fen, " ");

    std::string fenPos = ChessLib::ExpandFenPosition(fenSplitted[0], EMPTYSQUARE);
    std::vector<std::string> fenPositions = StringHelper::SplitString(fenPos, "/");
    std::string sideToMoveColor = fenSplitted[1];
    std::string castlingRightsStrings = fenSplitted[2];

    //load board
    this->ClearBoard();
    for (int rankItr = 1; rankItr <= 8; rankItr++)
    {
        for (int fileItr = 1; fileItr <= 8; fileItr++)
        {
            //need to inverse because the fen pos will start with the black pieces
            //and the black pieces start on the 8th rank
            this->PlacePiece(fenPositions[rankItr - 1][fileItr - 1], fileItr, 8 - rankItr + 1);
        }
    }
    //load side to move
    if (sideToMoveColor == "b")
        this->currentTurn = PieceColors::black;
    else if (sideToMoveColor == "w")
        this->currentTurn = PieceColors::white;
    else
        throw std::invalid_argument("Invalid fen when trying to load a board from fen");
}
std::string Board::ExportFen()
{
    return "";
}
void Board::DisplayBoard(char orientation)
{
    printf("===========================\n");
    printf("    A  B  C  D  E  F  G  H\n");
    printf("===========================\n");
    if (orientation == 'w')
    {
        for (int i = 0; i < 8; i++)
        {
            printf("%d  ", 8 - i);
            for (int j = 0; j < 8; j++)
            {
                printf(" %c ", board[i][j]);
            }

            printf("\n");
        }
    }
    else if (orientation == 'b')
    {
        for (int i = 0; i < 8; i++)
        {
            printf("%d  ", i + 1);
            for (int j = 0; j < 8; j++)
            {
                printf(" %c ", board[7 - i][j]);
            }

            printf("\n");
        }
    }
    printf("===========================");
    printf("\n    A  B  C  D  E  F  G  H\n");
    printf("===========================\n");
}
bool Board::IsMoveLegal(PieceColors sideToMove, Square from, Square to)
{

    PieceName pieceName = ChessLib::ToPieceNameEnum(this->GetPieceNameFromBoard(from));
    bool isMoveLegal = true;
    if (pieceName == PieceName::null)
        return false;

    //check if the current side move their own piece
    isMoveLegal &= (currentTurn == sideToMove);
    isMoveLegal &= Analyzer::DoesPieceMoveAccordingToRule(*this, pieceName, sideToMove, from, to);
    //check if the piece move to a square that is occupied by their own piece
    if (this->GetPieceNameFromBoard(to) != EMPTYSQUARE)
    {
        isMoveLegal &= !(this->GetPieceColorFromBoard(to) == currentTurn);
    }
    //check if something is blocking the movement
    isMoveLegal &= !(Analyzer::IsPieceMovementBlocked(*this, pieceName, sideToMove, from, to));
    return isMoveLegal;
}

bool Board::IsMoveLegal(PieceColors sideToMove, std::string moveNotation)
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
    return this->IsMoveLegal(sideToMove, fromSquare, toSquare);
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
    Square from = Square(moveNotation[0], moveNotation[1]);
    Square to = Square(moveNotation[2], moveNotation[3]);
    char pieceToMove = this->GetPieceNameFromBoard(from);
    PieceName pieceName = ChessLib::ToPieceNameEnum(pieceToMove);
    PieceColors sideToMove = ChessLib::ToPieceColorEnum(pieceToMove);
    if (IsMoveLegal(sideToMove, from, to) || allowIllegalMove)
    {
        MoveFlag moveFlag = this->GetMoveFlag(*this, pieceName, from, to);
        switch (moveFlag)
        {
        case MoveFlag::normal:
        {
            this->PlacePiece(EMPTYSQUARE, from);
            this->PlacePiece(pieceToMove, to);
            break;
        }
        case MoveFlag::shortCastle:
        {
            if (sideToMove == PieceColors::white)
            {
                this->PlacePiece(EMPTYSQUARE, from);
                this->PlacePiece('K', to);
                this->PlacePiece(EMPTYSQUARE, Square('h', '1'));
                this->PlacePiece('R', Square('f', '1'));
            }
            else if (sideToMove == PieceColors::black)
            {
                this->PlacePiece(EMPTYSQUARE, from);
                this->PlacePiece('k', to);
                this->PlacePiece(EMPTYSQUARE, Square('h', '8'));
                this->PlacePiece('r', Square('f', '8'));
            }
            break;
        }
        case MoveFlag::longCastle:
        {
            if (sideToMove == PieceColors::white)
            {
                this->PlacePiece(EMPTYSQUARE, from);
                this->PlacePiece('K', to);
                this->PlacePiece(EMPTYSQUARE, Square('a', '1'));
                this->PlacePiece('R', Square('d', '1'));
            }
            else if (sideToMove == PieceColors::black)
            {
                this->PlacePiece(EMPTYSQUARE, from);
                this->PlacePiece('k', to);
                this->PlacePiece(EMPTYSQUARE, Square('a', '8'));
                this->PlacePiece('r', Square('d', '8'));
            }
            break;
        }
        }

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
        throw std::invalid_argument("move is not legal,try again\n");
    }
}
