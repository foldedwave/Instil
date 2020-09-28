#ifndef TESTTWO_H
#define TESTTWO_H

#include "ITestTwo.h"

#include "gmock/gmock.h"
#include <memory>

using std::shared_ptr;

class ITestOne;

class TestTwo : public ITestTwo
{
private:
    shared_ptr<ITestOne>_one;

public:
    TestTwo(shared_ptr<ITestOne> one);
    virtual shared_ptr<ITestOne> GetOne();
    virtual void Call2();
    virtual ~TestTwo();
};

#endif