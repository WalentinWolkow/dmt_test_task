#include "customthread.h"

#include<iostream>

void CustomThreadOne::stepFunction()
{
    std::cerr << '.';
}

void CustomThreadTwo::stepFunction()
{
    std::cerr << ';';
}
