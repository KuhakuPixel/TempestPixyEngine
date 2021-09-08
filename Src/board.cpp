#include <string>
#include <iostream>
#include <ctype.h>
#include <stdexcept>
#include "CharHelper.h"
#define EMPTYSQUARE '-'
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
                    printf(" %c ", board[7-i][j]);
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

        char pieceToMove = board[CharHelper::ToInt(moveNotation[1]) - 1][CharHelper::ToAlphabetIndex(moveNotation[0])];
        printf("piece to move : %c\n", pieceToMove);
        board[CharHelper::ToInt(moveNotation[3]) - 1][CharHelper::ToAlphabetIndex(moveNotation[2])] = pieceToMove;
        board[CharHelper::ToInt(moveNotation[1]) - 1][CharHelper::ToAlphabetIndex(moveNotation[0])] = EMPTYSQUARE;
        //std::atoi()
    }
};