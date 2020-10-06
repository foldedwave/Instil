#ifndef TESTTWOALTERNATE_H
#define TESTTWOALTERNATE_H

#include "ITestTwoAlternate.h"

#include <string>
#include <memory>

using std::shared_ptr;

class ITestOne;

class TestTwoAlternate : public ITestTwoAlternate
{
private:
    std::vector<shared_ptr<ITestOne>> _one;

public:
    TestTwoAlternate(std::vector<shared_ptr<ITestOne>> one);
    virtual std::vector<shared_ptr<ITestOne>> GetOne();
    virtual std::string Call1();
    virtual std::string CallChild();
    virtual ~TestTwoAlternate();
};

#endif