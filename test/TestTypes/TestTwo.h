#ifndef TESTTWO_H
#define TESTTWO_H

#include "ITestTwo.h"

#include <string>
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
    virtual std::string Call1();
    virtual std::string CallChild();
    virtual ~TestTwo();
};

#endif