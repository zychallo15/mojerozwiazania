//
// Created by michal on 05.03.18.
//

#include <string>
#include "ReverseString.h"


std::string reverse(std::string str)
{
    std::string koncowy;
    for(size_t i=str.size(); i>0; i--)
    {
        koncowy+=str[i-1];
    }
    return koncowy;
}