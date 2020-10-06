#include "TestTwo.h"

#include "ITestOne.h"
#include <iostream>
#include <string>

using std::shared_ptr;

TestTwo::TestTwo(shared_ptr<ITestOne>one)
{
//     std::cout << "TestTwo::TestTwo" << std::endl;
    _one = one;
}

shared_ptr<ITestOne>TestTwo::GetOne()
{
    return _one;
}

std::string TestTwo::Call1()
{
    return "TestTwo::Call1()";
}

std::string TestTwo::CallChild()
{
    return _one->Call1();
}

TestTwo::~TestTwo()
{
    // std::cout << "TestTwo::~TestTwo" << std::endl;
}