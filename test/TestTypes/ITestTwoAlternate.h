#ifndef ITESTTWOALTERNATE_H
#define ITESTTWOALTERNATE_H

#include "ITestOne.h"

#include <memory>
#include <string>
#include <vector>

using std::shared_ptr;

class ITestTwoAlternate
{
public:
    virtual std::vector<shared_ptr<ITestOne>> GetOne() = 0;
    virtual std::string Call1() = 0;
    virtual std::string CallChild() = 0;
    virtual ~ITestTwoAlternate() {};
};

#endif