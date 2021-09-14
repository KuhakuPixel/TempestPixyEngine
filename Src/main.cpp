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
        board.Move(move);
    }
}
int main(int argc, char *argv[])
{
    //printf("%c\n",CharHelper::FromAlphabetIndex(2,false));
    StartEngine();
    return 0;
}