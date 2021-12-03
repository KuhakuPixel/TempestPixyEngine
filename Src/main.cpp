#include <string.h>
#include <iostream>
#include <string>
#include "board.h"
#include "CharHelper.h"
#include "math.h"
#include "chessLib.h"
#include "evaluation.h"
#include "search.h"
#include "stringHelper.h"
/// Starts engine in uci mode
void StartEngineUci()
{
    std::string startFenPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    std::string command = "";
#pragma region Initializing Engine parameters
    Board board = Board();
    board.LoadFromFen(startFenPosition);
    // printf("%d\n", CharHelper::ToInt('f'));
    Evaluation evaluation = Evaluation();
    evaluation.InitializeKnightPeriphery0(-0.51);
    evaluation.InitializeKnightPeriphery1(-0.18);
    evaluation.InitializeKnightPeriphery2(+0.54);
    evaluation.InitializeKnightPeriphery3(+0.1);
#pragma endregion
    while (true)
    {
        std::getline(std::cin, command);

        if (command == "isready")
            printf("readyok\n");
        else if (command.find("position") == 0)
        {
            if (command.find("position fen") == 0)
            {
                std::string newFenPos = command.substr(strlen("position fen") + 1);
                board.LoadFromFen(newFenPos);
            }
            else if (command.find("position startpos moves") == 0)
            {
                // restart board
                board = Board();
                board.LoadFromFen(startFenPosition);
                // get the algebraic moves
                std::string movesStr = command.substr(strlen("position startpos moves") + 1);
                std::vector<std::string> moves = StringHelper::SplitString(movesStr, " ");
                // setup board
                for (int i = 0; i < moves.size(); i++)
                    board.Move(moves.at(i));
            }
        }
        else if (command.find("go") == 0)
        {
            std::string bestMove = "";
            Search::SearchPosition(board, evaluation, 0, 4, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), &bestMove);
            printf("bestmove %s\n", bestMove.c_str());
            // board.Move(bestMove);
        }
        else if (command == "quit")
            exit(0);
    }
}

void PlayAgainstSelf()
{

    Board board = Board();
    board.LoadFromFen("rnbqkb1r/pppp1ppp/5n2/4p3/4PP2/2N5/PPPP2PP/R1BQKBNR b KQkq - 0 3");

    Evaluation evaluation = Evaluation();
    evaluation.InitializeKnightPeriphery0(-0.51);
    evaluation.InitializeKnightPeriphery1(-0.18);
    evaluation.InitializeKnightPeriphery2(+0.54);
    evaluation.InitializeKnightPeriphery3(+0.1);
    while (true)
    {
        std::string colorToMove = board.GetCurrentTurnStr();
        std::string bestMove = "";
        printf("Side to move %s \n", colorToMove.c_str());
        printf("last move is :  %s\n", bestMove.c_str());
        board.DisplayBoard('w');
        // move engine

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
    printf("Tempest Pixy engine\n");
    while (true)
    {
        std::string command = "";
        std::cin >> command;
        if (command == "uci")
        {
            printf("id name Tempest-Pixy-Engine 1.0.0\n");
            printf("id author Kuhaku Pixel\n");
            printf("uciok\n");
            StartEngineUci();
        }
        else if (command == "isready")
        {
            printf("readyok\n");
        }
        else if (command == "quit")
            exit(0);
    }

    return 0;
}