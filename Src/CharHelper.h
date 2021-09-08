#pragma once

class CharHelper
{
public:
    static int ToAlphabetIndex(char c);
    static char FromAlphabetIndex(int index,bool toUpper);
    static int ToInt(char c);
};