#ifndef TEMPLATED_H
#define TEMPLATED_H

#include "Interfaces/ITemplated.h"

#include <string>

template <class T>
class Templated : public ITemplated<T>
{
public:
    Templated() {}

    std::string Call() override
    {
        return "Templated::Call()";
    }

    virtual ~Templated() {}

    const std::string Name = "Templated";
};

#endif