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
    this->rank = static_cast<char>(rankNum + 48);
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
std::string Square::GetNotation()
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
std::vector<MoveFlag> Board::GetCastlingRights(PieceColors color) const
{
    if (color == PieceColors::white)
        return this->whiteCastlingRights;
    else if (color == PieceColors::black)
        return this->blackCastlingRights;
    else
    {
        std::string errorMsg = std::string("invalid color : ") + ChessLib::GetPieceColorStr(color);
        throw std::invalid_argument(errorMsg);
    }
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

    return this->GetPieceName(fileNum, rankNum) == EMPTYSQUARE;
}

bool Board::IsSquareEmpty(Square square) const
{
    return this->GetPieceName(square) == EMPTYSQUARE;
}

void Board::PlacePiece(char piece, int fileNum, int rankNum)
{
    board[8 - rankNum][fileNum - 1] = piece;
}
void Board::PlacePiece(char piece, Square square)
{
    this->PlacePiece(piece, square.fileNum, square.rankNum);
}

char Board::GetPieceName(int fileNum, int rankNum) const
{
    return board[8 - rankNum][fileNum - 1];
}

char Board::GetPieceName(Square square) const
{
    return this->GetPieceName(square.fileNum, square.rankNum);
}

PieceColors Board::GetPieceColor(int fileNum, int rankNum) const
{
    char piece = this->GetPieceName(fileNum, rankNum);

    return ChessLib::ToPieceColorEnum(piece);
}
PieceColors Board::GetPieceColor(Square square) const
{
    return this->GetPieceColor(square.fileNum, square.rankNum);
}

PieceName Board::GetPieceNameEnum(int fileNum, int rankNum) const
{
    return ChessLib::ToPieceNameEnum(this->GetPieceName(fileNum, rankNum));
}
PieceName Board::GetPieceNameEnum(Square square) const
{
    return ChessLib::ToPieceNameEnum(this->GetPieceName(square));
}
void Board::LoadPseudoBoard(const Board &board)
{
    memcpy(this->board, board.board, sizeof(char) * 8 * 8);
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
            char piece = fenPositions[rankItr - 1][fileItr - 1];
            this->PlacePiece(piece, fileItr, 8 - rankItr + 1);
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
    std::string fen = "";
    std::string fenPos = "";
    for (int i = 0; i++; i < 8)
    {
        fenPos += std::string(this->board[i]);
        if (i < 7)
            fenPos += "/";
    }
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

void Board::Move(std::string moveNotation, bool psuedoLegalMove)
{
    if (moveNotation.size() < 4)
    {
        throw std::invalid_argument("move size must be at least 4");
    }
    if (isdigit(moveNotation[0]) || !isdigit(moveNotation[1]) ||
        isdigit(moveNotation[2]) || !isdigit(moveNotation[3]))
    {
        throw std::invalid_argument("invalid move notation " + moveNotation);
    }
    Square from = Square(moveNotation[0], moveNotation[1]);
    Square to = Square(moveNotation[2], moveNotation[3]);

    PieceName newPromotedPiece = PieceName::null;
    //last char of a long algebraic notation is the piece to promote to
    if (moveNotation.size() == 5)
        newPromotedPiece = ChessLib::ToPieceNameEnum(moveNotation[4]);

    this->Move(from, to, psuedoLegalMove, newPromotedPiece);
}

void Board::Move(Square from, Square to, bool psuedoLegalMove, PieceName newPromotedPiece)
{

    char pieceToMove = this->GetPieceName(from);
    PieceName pieceName = ChessLib::ToPieceNameEnum(pieceToMove);
    PieceColors sideToMove = ChessLib::ToPieceColorEnum(pieceToMove);

    bool isMoveLegal = false;
    if (!psuedoLegalMove)
        isMoveLegal = Analyzer::IsMoveLegal(*this, from, to);
    else
        isMoveLegal = true;
    if (isMoveLegal)
    {

        MoveFlag moveFlag = Analyzer::GetMoveFlag(*this, from, to);
        switch (moveFlag)
        {
        case MoveFlag::normal:
        {
            this->PlacePiece(EMPTYSQUARE, from);
            this->PlacePiece(pieceToMove, to);

            //remove castling right
            if (ChessLib::ToPieceNameEnum(pieceToMove) == PieceName::king)
            {
                if (sideToMove == PieceColors::white)
                {
                    if (this->whiteCastlingRights.size() > 0)
                        this->whiteCastlingRights.clear();
                }
                else if (sideToMove == PieceColors::black)
                {
                    if (this->blackCastlingRights.size() > 0)
                        this->blackCastlingRights.clear();
                }
            }
            else if (ChessLib::ToPieceNameEnum(pieceToMove) == PieceName::rook)
            {
                //a rook or king move will remove the castling rights
                if (sideToMove == PieceColors::white)
                {
                    if (from.file == 'h' && from.rank == '1')
                    {
                        std::vector<MoveFlag>::iterator pos = std::find(this->whiteCastlingRights.begin(), this->whiteCastlingRights.end(), MoveFlag::shortCastle);
                        if (pos != this->whiteCastlingRights.end())
                            this->whiteCastlingRights.erase(pos);
                    }

                    if (from.file == 'a' && from.rank == '1')
                    {
                        std::vector<MoveFlag>::iterator pos = std::find(this->whiteCastlingRights.begin(), this->whiteCastlingRights.end(), MoveFlag::longCastle);
                        if (pos != this->whiteCastlingRights.end())
                            this->whiteCastlingRights.erase(pos);
                    }
                }
                else if (sideToMove == PieceColors::black)
                {
                    if (from.file == 'h' && from.rank == '8')
                    {
                        std::vector<MoveFlag>::iterator pos = std::find(this->blackCastlingRights.begin(), this->blackCastlingRights.end(), MoveFlag::shortCastle);
                        if (pos != this->blackCastlingRights.end())
                            this->blackCastlingRights.erase(pos);
                    }

                    if (from.file == 'a' && from.rank == '8')
                    {
                        std::vector<MoveFlag>::iterator pos = std::find(this->blackCastlingRights.begin(), this->blackCastlingRights.end(), MoveFlag::longCastle);
                        if (pos != this->blackCastlingRights.end())
                            this->blackCastlingRights.erase(pos);
                    }
                }
            }
            break;
        }
        case MoveFlag::promotion:
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
                this->whiteCastlingRights.clear();
            }
            else if (sideToMove == PieceColors::black)
            {
                this->PlacePiece(EMPTYSQUARE, from);
                this->PlacePiece('k', to);
                this->PlacePiece(EMPTYSQUARE, Square('h', '8'));
                this->PlacePiece('r', Square('f', '8'));
                this->blackCastlingRights.clear();
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
                this->whiteCastlingRights.clear();
            }
            else if (sideToMove == PieceColors::black)
            {
                this->PlacePiece(EMPTYSQUARE, from);
                this->PlacePiece('k', to);
                this->PlacePiece(EMPTYSQUARE, Square('a', '8'));
                this->PlacePiece('r', Square('d', '8'));
                this->blackCastlingRights.clear();
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
