#ifndef SIMPLE_H
#define SIMPLE_H

#include "Interfaces/ISimple.h"
#include "Interfaces/ISimple2.h"

#include <string>

class Simple : public ISimple, public ISimple2
{
public:
    Simple();
    std::string Call() override;
    virtual ~Simple();
    const std::string Name = "Simple";
};

#endif