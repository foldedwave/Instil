#include "TestOne.h"

#include <string>
#include <iostream>

std::string TestOne::Call1()
{
    return "TestOne::Call1()";
}

TestOne::TestOne()
{
    // std::cout << "TestOne::TestOne" << std::endl;
}

TestOne::~TestOne()
{
    // std::cout << "TestOne::~TestOne" << std::endl;
}