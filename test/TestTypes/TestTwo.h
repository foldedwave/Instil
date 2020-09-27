#ifndef TESTTWO_H
#define TESTTWO_H

#include "ITestTwo.h"

class ITestOne;

class TestTwo : public ITestTwo
{
private:
    ITestOne *_one;

public:
    TestTwo(ITestOne *one);
    virtual ITestOne *GetOne();
    virtual void Call2();
};

#endif