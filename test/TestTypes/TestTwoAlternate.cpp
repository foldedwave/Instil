#include "TestTwoAlternate.h"

#include "ITestOne.h"
#include <iostream>
#include <string>
#include <vector>

using std::shared_ptr;

TestTwoAlternate::TestTwoAlternate(std::vector<shared_ptr<ITestOne>> one)
{
//     std::cout << "TestTwoAlternate::TestTwoAlternate" << std::endl;
    _one = one;
}

std::vector<shared_ptr<ITestOne>> TestTwoAlternate::GetOne()
{
    return _one;
}

std::string TestTwoAlternate::Call1()
{
    return "TestTwoAlternate::Call1()";
}

std::string TestTwoAlternate::CallChild()
{
    std::string retval = "";

    for (auto o : _one)
    {
        retval = retval.append(o->Call1()).append("/");
    }
    return retval;
}

TestTwoAlternate::~TestTwoAlternate()
{
    // std::cout << "TestTwoAlternate::~TestTwoAlternate" << std::endl;
}