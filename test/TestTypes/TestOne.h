#ifndef TESTONE_H
#define TESTONE_H

#include "ITestOne.h"

class TestOne : public ITestOne
{
public:
    TestOne() {}
    void Call1() override;
};

#endif