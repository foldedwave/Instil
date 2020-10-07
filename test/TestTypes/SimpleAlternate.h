#ifndef SIMPLEALTERNATE_H
#define SIMPLEALTERNATE_H

#include "Interfaces/ISimple.h"

#include <string>

class SimpleAlternate : public ISimple
{
public:
    SimpleAlternate();
    std::string Call() override;
    virtual ~SimpleAlternate();
};

#endif