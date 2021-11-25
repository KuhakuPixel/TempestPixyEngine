#include <iostream>
#include <string>
#include "board.h"
#include "CharHelper.h"
#include "math.h"
#include "chessLib.h"
#include "evaluation.h"
#include "search.h"
void StartEngine(std::string fenPosition)
{

    Board board = Board();
    board.LoadFromFen(fenPosition);
    // printf("%d\n", CharHelper::ToInt('f'));
    Evaluation evaluation = Evaluation();
    evaluation.InitializeKnightPeriphery0(-0.51);
    evaluation.InitializeKnightPeriphery1(-0.18);
    evaluation.InitializeKnightPeriphery2(+0.54);
    evaluation.InitializeKnightPeriphery3(+0.1);
    while (true)
    {
        if (board.GetCurrentTurn() == PieceColors::black)
        {
            std::string bestMove = "";
            Search::SearchPosition(board, evaluation, 0, 4, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), &bestMove);
            printf("Best move is %s\n", bestMove.c_str());
            board.Move(bestMove);
            continue;
        }
        //printf("Current evaluation : %f\n", evaluation.Evaluate(board));
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

void PlayAgainstSelf()
{

    Board board = Board();
    board.LoadFromFen("rnbqkb1r/pppp1ppp/5n2/4p3/4PP2/2N5/PPPP2PP/R1BQKBNR b KQkq - 0 3");
    std::string bestMove = "";
    Evaluation evaluation = Evaluation();
    evaluation.InitializeKnightPeriphery0(-0.51);
    evaluation.InitializeKnightPeriphery1(-0.18);
    evaluation.InitializeKnightPeriphery2(+0.54);
    evaluation.InitializeKnightPeriphery3(+0.1);
    while (true)
    {
        std::string colorToMove = board.GetCurrentTurnStr();
        printf("Side to move %s \n", colorToMove.c_str());
        printf("last move is :  %s\n", bestMove.c_str());
        board.DisplayBoard('w');
        //move engine

        Search::SearchPosition(board, evaluation, 0, 4, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), &bestMove);

        board.Move(bestMove);
        system("cls");
        //

        /*
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
        */
    }
}
int main(int argc, char *argv[])
{
    std::string fenPosition = "";
    printf("Fen position : ");
    std::getline(std::cin, fenPosition);
    printf("%s\n", fenPosition.c_str());
    StartEngine(fenPosition);
    return 0;
}