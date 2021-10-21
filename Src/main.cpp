#include <iostream>
#include <string>
#include "board.h"
#include "CharHelper.h"
#include "math.h"
#include "chessLib.h"
#include "evaluation.h"
#include "search.h"
void StartEngine()
{
    Board board = Board();

    // printf("%d\n", CharHelper::ToInt('f'));
    Evaluation evaluation = Evaluation();
    evaluation.InitializeKnightPeriphery0(-0.51);
    evaluation.InitializeKnightPeriphery1(-0.18);
    evaluation.InitializeKnightPeriphery2(+0.54);
    evaluation.InitializeKnightPeriphery3(+0.1);
    while (true)
    {
        if (board.GetCurrentTurn() == PieceColors::black)
            Search::SearchPosition(board, evaluation, 0, 4);
        printf("Current evaluation : %f\n", evaluation.Evaluate(board));
        std::string colorToMove = board.GetCurrentTurnStr();
        printf("Side to move %s \n", colorToMove.c_str());
        board.DisplayBoard('w');
        std::string move = "";
        printf("Move : ");
        std::cin >> move;
        try
        {
            board.Move(move);
        }
        // ref: https://stackoverflow.com/questions/6755991/catching-stdexception-by-reference/6756040#6756040
        catch (const std::exception &e)
        {
            printf("%s \n", e.what());
        }
    }
}
int main(int argc, char *argv[])
{
    // printf("%c\n",CharHelper::FromAlphabetIndex(2,false));
    StartEngine();

    return 0;
}