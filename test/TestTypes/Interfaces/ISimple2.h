#ifndef ISIMPLE2_H
#define ISIMPLE2_H

#include <string>

class ISimple2
{
public:
    virtual std::string Call() = 0;
    virtual ~ISimple2() {};
};

#endif