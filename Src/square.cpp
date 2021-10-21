#include "square.h"
#include "CharHelper.h"
#include <stdexcept>
Square::Square(char file, char rank)
{
    int fileNum = CharHelper::ToAlphabetIndex(file) + 1;
    int rankNum = CharHelper::ToInt(rank);
    if (fileNum > 0 && fileNum <= 8)
    {
        this->fileNum = fileNum;
    }
    else
    {
        throw std::invalid_argument("invalid file value when turning file and rank char to Square ,must be in between A and H (inclusive)\n");
    }
    if (rankNum > 0 && rankNum <= 8)
    {
        this->rankNum = rankNum;
    }
    else
    {
        throw std::invalid_argument("invalid rank value when turning file and rank char to Square ,must be in between 1 and 8 (inclusive)\n");
    }
    this->file = file;
    this->rank = rank;
}
Square::Square(int fileNum, int rankNum)
{
    if (fileNum > 0 && fileNum <= 8)
    {
        this->fileNum = fileNum;
    }
    else
    {
        throw std::invalid_argument("invalid file value when turning fileNum and ranNum to square ,must be in between A and H (inclusive)\n");
    }
    if (rankNum > 0 && rankNum <= 8)
    {
        this->rankNum = rankNum;
    }
    else
    {
        throw std::invalid_argument("invalid rank value when turning fileNum and ranNum to square ,must be in between 1 and 8 (inclusive)\n");
    }
    this->rank = static_cast<char>(rankNum + 48);
    this->file = CharHelper::FromAlphabetIndex(fileNum - 1, false);
}

Square::Square(std::string square)
{
    if (square.length() == 2)
    {
        char file = square[0];
        char rank = square[1];
        int fileNum = CharHelper::ToAlphabetIndex(file) + 1;
        int rankNum = CharHelper::ToInt(rank);
        if (fileNum > 0 && fileNum <= 8)
        {
            this->fileNum = fileNum;
        }
        else
        {
            throw std::invalid_argument("invalid file value when turning square string to Square,must be in between A and H (inclusive)\n");
        }
        if (rankNum > 0 && rankNum <= 8)
        {
            this->rankNum = rankNum;
        }
        else
        {
            throw std::invalid_argument("invalid rank value when turning square string to Square, ,must be in between 1 and 8 (inclusive)\n");
        }
        this->file = file;
        this->rank = rank;
    }
    else
    {
        std::string errorMsg = std::string("square string 's length must be exactly 2 when turning square string to Square,") + "\n" +
                               "square : " + square;
        throw std::invalid_argument(errorMsg);
    }
}
std::string Square::GetNotation()
{
    return std::string() + this->file + this->rank;
}

std::pair<Square, Square> Square::GetMoveFromStr(std::string move)
{
    if (move.size() < 4)
    {
        throw std::invalid_argument("move size must be at least 4");
    }
    if (isdigit(move[0]) || !isdigit(move[1]) ||
        isdigit(move[2]) || !isdigit(move[3]))
    {
        throw std::invalid_argument("invalid move notation: " + move);
    }
    Square from = Square(move[0], move[1]);
    Square to = Square(move[2], move[3]);
    return std::make_pair(Square(move[0], move[1]), Square(move[2], move[3]));
}