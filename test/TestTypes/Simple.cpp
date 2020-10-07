#include "Simple.h"

#include <string>
#include <iostream>

std::string Simple::Call()
{
    return "Simple::Call()";
}

Simple::Simple()
{
    // std::cout << "Simple::Simple" << std::endl;
}

Simple::~Simple()
{
    // std::cout << "Simple::~Simple" << std::endl;
}