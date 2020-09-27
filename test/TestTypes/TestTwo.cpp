#include "TestTwo.h"

#include "ITestOne.h"
#include <iostream>

TestTwo::TestTwo(ITestOne *one)
{
    _one = one;
}

ITestOne *TestTwo::GetOne()
{
    return _one;
}

void TestTwo::Call2()
{
    std::cout << "Call2" << std::endl;
    _one->Call1();
}