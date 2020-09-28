#include "TestTwo.h"

#include "ITestOne.h"
#include <iostream>

using std::shared_ptr;

TestTwo::TestTwo(shared_ptr<ITestOne>one)
{
    _one = one;
}

shared_ptr<ITestOne>TestTwo::GetOne()
{
    return _one;
}

void TestTwo::Call2()
{
    std::cout << "Call2" << std::endl;
    _one->Call1();
}

TestTwo::~TestTwo()
{
    
}