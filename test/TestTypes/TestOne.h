#ifndef TESTONE_H
#define TESTONE_H

#include "ITestOne.h"

#include <string>

class TestOne : public ITestOne
{
public:
    TestOne();
    std::string Call1() override;
    virtual ~TestOne();
};

#endif