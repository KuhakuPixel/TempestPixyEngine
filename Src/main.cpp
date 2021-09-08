#include <iostream>
#include "board.cpp"
#include "CharHelper.h"
int main(int argc, char *argv[])
{
    Board board=Board();

    
    //printf("%d\n", CharHelper::ToInt('f'));
    
    while(true){
        board.DisplayBoard('w');
        std::string move="";
        printf("Move : ");
        std::cin>>move;
        board.Move(move);

    }
    return 0;
}