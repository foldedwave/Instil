#include "TestOne.h"

#include <iostream>

void TestOne::Call1()
{
    std::cout << "Call1" << std::endl;
}

TestOne::TestOne()
{
    std::cout << "TestOne::TestOne" << std::endl;
}

TestOne::~TestOne()
{
    std::cout << "TestOne::~TestOne" << std::endl;
}