#include "CharHelper.h"
#include <ctype.h>
#include <stdexcept>
int CharHelper::ToAlphabetIndex(char c){
    return toupper(c)-65;
}
int CharHelper::ToInt(char c){

    if(isdigit(c)){
        return c-48;
    }
    else{
        throw std::invalid_argument("char is not a digit");
    }
    
}
