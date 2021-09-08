#include <string>
#include <iostream>
#include <ctype.h>
#include <stdexcept>
#include "CharHelper.h"
#include "math.h"
#define EMPTYSQUARE '-'

struct Square
{
    char file;
    char rank;
    int fileNum;
    int rankNum;
    Square(char file, char rank)
    {
        int fileNum = CharHelper::ToAlphabetIndex(file) + 1;
        int rankNum = CharHelper::ToInt(rank);
        if (fileNum > 0 && fileNum <= 8)
        {
            this->fileNum=fileNum;
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
    Square(char file, int rank) : Square(file, (char)rank)
    {
    }
};
struct Board
{
    char board[8][8] = {

        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE},
        {EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE},
        {EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE},
        {EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},

    };
    void LoadFromFen(std::string fen)
    {
    }
    ///w for white , b for black
    void DisplayBoard(char orientation = 'w')
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
    ///The move format is in long algebraic notation.
    ///A nullmove from the Engine to the GUI should be send as 0000.
    ///Examples:  e2e4, e7e5, e1g1 (white short castling), e7e8q (for promotion)
    void Move(std::string moveNotation)
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
        Square fromSquare=Square(moveNotation[0],moveNotation[1]);
        Square toSquare=Square(moveNotation[2],moveNotation[3]);
        char pieceToMove = board[fromSquare.rankNum-1][fromSquare.fileNum-1];
        printf("piece to move : %c\n", pieceToMove);
        printf("fromsquare , filenum %d ranknum %d \n",fromSquare.fileNum,fromSquare.rankNum);
          printf("toquare , filenum %d ranknum %d \n",toSquare.fileNum,toSquare.rankNum);
        board[toSquare.rankNum-1][toSquare.fileNum-1] = pieceToMove;
        board[fromSquare.rankNum-1][fromSquare.fileNum-1] = EMPTYSQUARE;
        //std::atoi()
    }
};