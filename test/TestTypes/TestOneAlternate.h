#ifndef TESTONEALTERNATE_H
#define TESTONEALTERNATE_H

#include "ITestOne.h"

#include <string>

class TestOneAlternate : public ITestOne
{
public:
    TestOneAlternate();
    std::string Call1() override;
    virtual ~TestOneAlternate();
};

#endif