#ifndef ITESTTWO_H
#define ITESTTWO_H

#include "ITestOne.h"

class ITestTwo
{
public:
    virtual ITestOne *GetOne() = 0;
    virtual void Call2() = 0;
};

#endif