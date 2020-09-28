#ifndef ITESTTWO_H
#define ITESTTWO_H

#include "ITestOne.h"

#include <memory>

using std::shared_ptr;

class ITestTwo
{
public:
    virtual shared_ptr<ITestOne> GetOne() = 0;
    virtual void Call2() = 0;
    virtual ~ITestTwo() {};
};

#endif