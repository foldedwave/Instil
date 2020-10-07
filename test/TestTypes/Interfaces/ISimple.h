#ifndef ISIMPLE_H
#define ISIMPLE_H

#include <string>

class ISimple
{
public:
    virtual std::string Call() = 0;
    virtual ~ISimple() {};
};

#endif