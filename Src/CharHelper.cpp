#include "CharHelper.h"
#include <ctype.h>
#include <stdexcept>
int CharHelper::ToAlphabetIndex(char c)
{
    return toupper(c) - 65;
}
char CharHelper::FromAlphabetIndex(int index, bool toUpper)
{
    if (toUpper)
    {
        return char(index + 65);
    }
    else
    {

        return tolower(char(index + 65));
    }
}
int CharHelper::ToInt(char c)
{

    if (isdigit(c))
    {
        return c - 48;
    }
    else
    {
        throw std::invalid_argument("char is not a digit");
    }
}
