#ifndef ITESTTWO_H
#define ITESTTWO_H

#include "ITestOne.h"

#include <memory>
#include <string>

using std::shared_ptr;

class ITestTwo
{
public:
    virtual shared_ptr<ITestOne> GetOne() = 0;
    virtual std::string Call1() = 0;
    virtual std::string CallChild() = 0;
    virtual ~ITestTwo() {};
};

#endif