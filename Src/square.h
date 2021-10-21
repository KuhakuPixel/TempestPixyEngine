#pragma once
#include <string>
struct Square
{
    char file;
    char rank;
    int fileNum;
    int rankNum;
    Square(char file, char rank);
    Square(int fileNum, int rankNum);
    ///square size must be exactly 2
    ///for example :e2 ,h3 and ect
    Square(std::string square);
    std::string GetNotation();

    ///the first element of the tuple is the original square
    ///the second element of the tuple is the destination square
    static std::pair<Square, Square> GetMoveFromStr(std::string move);
};