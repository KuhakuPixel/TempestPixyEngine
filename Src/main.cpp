#include <iostream>
#include <string>
#include "board.h"
#include "CharHelper.h"
#include "math.h"
void StartEngine()
{
    Board board = Board();

    //printf("%d\n", CharHelper::ToInt('f'));

    while (true)
    {
        std::string colorToMove = pieceColorStr[(int)board.currentTurn];
        printf("Side to move %s \n", colorToMove.c_str());
        board.DisplayBoard('w');
        std::string move = "";
        printf("Move : ");
        std::cin >> move;
        try
        {
            board.Move(move);
        }
        //ref: https://stackoverflow.com/questions/6755991/catching-stdexception-by-reference/6756040#6756040
        catch (const std::exception &e)
        {
            printf("%s \n", e.what());
        }
    }
}
int main(int argc, char *argv[])
{
    //printf("%c\n",CharHelper::FromAlphabetIndex(2,false));
    StartEngine();
    return 0;
}