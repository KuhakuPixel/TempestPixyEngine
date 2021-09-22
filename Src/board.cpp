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
#include <algorithm>
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
    this->rank = static_cast<char>(rankNum);
    this->file = CharHelper::FromAlphabetIndex(fileNum - 1, false);
}

Square::Square(std::string square)
{
    if (square.length() == 2)
    {
        char file = square[0];
        char rank = square[1];
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
    else
    {
        std::string errorMsg = std::string("square string 's length must be exactly 2") + "\n" +
                               "square : " + square;
        throw std::invalid_argument(errorMsg);
    }
}
std::string Square::GetBoardNotation()
{
    return std::string() + this->file + this->rank;
}

std::pair<Square, Square> Square::GetMoveFromStr(std::string move)
{
    if (move.size() < 4)
    {
        throw std::invalid_argument("move size must be at least 4");
    }
    if (isdigit(move[0]) || !isdigit(move[1]) ||
        isdigit(move[2]) || !isdigit(move[3]))
    {
        throw std::invalid_argument("invalid move notation: " + move);
    }
    Square from = Square(move[0], move[1]);
    Square to = Square(move[2], move[3]);
    return std::make_pair(Square(move[0], move[1]), Square(move[2], move[3]));
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
PieceColors Board::GetCurrentTurn() const
{
    return this->currentTurn;
}
std::string Board::GetCurrentTurnStr() const
{
    return ChessLib::GetPieceColorStr(this->GetCurrentTurn());
}

bool Board::IsSquareEmpty(int fileNum, int rankNum) const
{
    if (fileNum > 8 || fileNum < 1 || rankNum > 8 || rankNum < 1)
    {
        std::string errorMsg = std::string("invalid Square position\n") +
                               "fileNum:" + std::to_string(fileNum) + "\n" +
                               "rankNum:" + std::to_string(rankNum) + "\n";
        throw std::invalid_argument(errorMsg);
    }

    return this->GetPieceNameFromBoard(fileNum, rankNum) == EMPTYSQUARE;
}

bool Board::IsSquareEmpty(Square square) const
{
    return this->GetPieceNameFromBoard(square) == EMPTYSQUARE;
}

void Board::PlacePiece(char piece, int fileNum, int rankNum)
{
    board[8 - rankNum][fileNum - 1] = piece;
}
void Board::PlacePiece(char piece, Square square)
{
    this->PlacePiece(piece, square.fileNum, square.rankNum);
}

char Board::GetPieceNameFromBoard(int fileNum, int rankNum) const
{
    return board[8 - rankNum][fileNum - 1];
}

char Board::GetPieceNameFromBoard(Square square) const
{
    return this->GetPieceNameFromBoard(square.fileNum, square.rankNum);
}

PieceColors Board::GetPieceColorFromBoard(int fileNum, int rankNum) const
{
    char piece = this->GetPieceNameFromBoard(fileNum, rankNum);

    return ChessLib::ToPieceColorEnum(piece);
}
PieceColors Board::GetPieceColorFromBoard(Square square) const
{
    return this->GetPieceColorFromBoard(square.fileNum, square.rankNum);
}

PieceName Board::GetPieceNameEnumFromBoard(int fileNum, int rankNum) const
{
    return ChessLib::ToPieceNameEnum(this->GetPieceNameFromBoard(fileNum, rankNum));
}
PieceName Board::GetPieceNameEnumFromBoard(Square square) const
{
    return ChessLib::ToPieceNameEnum(this->GetPieceNameFromBoard(square));
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
    if (this->IsSquareEmpty(from))
        return false;
    bool isMoveLegal = true;
    PieceName pieceName = this->GetPieceNameEnumFromBoard(from);
    MoveFlag moveFlag = Analyzer::GetMoveFlag(*this, from, to);
    //check if the current side move their own piece
    isMoveLegal &= (this->currentTurn == sideToMove);
    if (Analyzer::DoesPieceMoveCorrectly(pieceName, sideToMove, from, to))
    {
        if (!Analyzer::IsPieceMovementBlocked(*this, from, to))
        {
            PieceColors waitingSide = ChessLib::InvertPieceColor(sideToMove);
            //makes sure pawn doesnt capture on an empty square
            if (pieceName == PieceName::pawn)
            {
                if (moveFlag == MoveFlag::pawnDiagonalMove)
                {
                    isMoveLegal &= (!this->IsSquareEmpty(to)) && (sideToMove != this->GetPieceColorFromBoard(to));
                }
            }
            else if (pieceName == PieceName::king)
            {
                std::vector<MoveFlag> castlingRights = playersToCastlingRightsMap.at(sideToMove);
                if (moveFlag == MoveFlag::longCastle)
                {
                    isMoveLegal &= std::find(castlingRights.begin(), castlingRights.end(), moveFlag) != castlingRights.end();
                    if (sideToMove == PieceColors::white)
                    {
                        bool canCastle = !Analyzer::IsSquareAttacked(
                            *this,
                            PieceColors::black,
                            {"e1", "d1", "c1"});
                        isMoveLegal &= canCastle;
                    }
                    else if (sideToMove == PieceColors::black)
                    {
                        bool canCastle = !Analyzer::IsSquareAttacked(
                            *this,
                            PieceColors::white,
                            {"e8", "d8", "c8"});
                        isMoveLegal &= canCastle;
                    }
                }
                else if (moveFlag == MoveFlag::shortCastle)
                {
                    isMoveLegal &= std::find(castlingRights.begin(), castlingRights.end(), moveFlag) != castlingRights.end();
                    if (sideToMove == PieceColors::white)
                    {
                        bool canCastle = !Analyzer::IsSquareAttacked(
                            *this,
                            PieceColors::black,
                            {"e1", "f1", "g1"});
                        isMoveLegal &= canCastle;
                    }
                    else if (sideToMove == PieceColors::black)
                    {
                        bool canCastle = !Analyzer::IsSquareAttacked(
                            *this,
                            PieceColors::white,
                            {"e8", "f8", "g8"});
                        isMoveLegal &= canCastle;
                    }
                }
                else
                {
                    isMoveLegal &= !Analyzer::IsSquareAttacked(*this, waitingSide, to);
                }
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        isMoveLegal &= false;
    }

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
        throw std::invalid_argument("invalid move notation : " + moveNotation);
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
        throw std::invalid_argument("invalid move notation : " + moveNotation);
    }
    Square from = Square(moveNotation[0], moveNotation[1]);
    Square to = Square(moveNotation[2], moveNotation[3]);
    char pieceToMove = this->GetPieceNameFromBoard(from);
    PieceName pieceName = ChessLib::ToPieceNameEnum(pieceToMove);
    PieceColors sideToMove = ChessLib::ToPieceColorEnum(pieceToMove);
    if (IsMoveLegal(sideToMove, from, to) || allowIllegalMove)
    {

        MoveFlag moveFlag = Analyzer::GetMoveFlag(*this, from, to);
        switch (moveFlag)
        {
        case MoveFlag::normal:
        {
            this->PlacePiece(EMPTYSQUARE, from);
            this->PlacePiece(pieceToMove, to);
            break;
        }
        case MoveFlag::pawnDiagonalMove:
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
                this->playersToCastlingRightsMap.at(PieceColors::white).clear();
            }
            else if (sideToMove == PieceColors::black)
            {
                this->PlacePiece(EMPTYSQUARE, from);
                this->PlacePiece('k', to);
                this->PlacePiece(EMPTYSQUARE, Square('h', '8'));
                this->PlacePiece('r', Square('f', '8'));
                this->playersToCastlingRightsMap.at(PieceColors::black).clear();
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
                this->playersToCastlingRightsMap.at(PieceColors::white).clear();
            }
            else if (sideToMove == PieceColors::black)
            {
                this->PlacePiece(EMPTYSQUARE, from);
                this->PlacePiece('k', to);
                this->PlacePiece(EMPTYSQUARE, Square('a', '8'));
                this->PlacePiece('r', Square('d', '8'));
                this->playersToCastlingRightsMap.at(PieceColors::black).clear();
            }
            break;
        }

        default:
        {
            throw std::invalid_argument("Invalid Moveflags");
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
