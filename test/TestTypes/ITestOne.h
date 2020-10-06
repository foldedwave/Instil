#ifndef ITESTONE_H
#define ITESTONE_H

#include <string>

class ITestOne
{
public:
    virtual std::string Call1() = 0;
    virtual ~ITestOne() {};
};

#endif