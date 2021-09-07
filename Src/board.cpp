#include <string>
#include <iostream>
#define EMPTYSQUARE '-'
struct Board
{
    char board[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE},
        {EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE},
        {EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE},
        {EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE},
        {EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE},
        {EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE, EMPTYSQUARE},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
    };
    void LoadFromFen(std::string fen)
    {
    }
    void DisplayBoard()
    {
        printf("    A  B  C  D  E  F  G  H\n\n");
        for (int i = 0; i < 8; i++)
        {
            printf("%d  ",i+1);
            for (int j = 0; j < 8; j++)
            {
                printf(" %c ",board[i][j]);
            }
            
            printf("\n");
        }

        printf("\n    A  B  C  D  E  F  G  H\n");
    }
};