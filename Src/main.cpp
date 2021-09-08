#include <iostream>
#include "board.cpp"
#include "CharHelper.h"
#include "math.h"
void StartEngine()
{
    Board board = Board();

    //printf("%d\n", CharHelper::ToInt('f'));

    while (true)
    {
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