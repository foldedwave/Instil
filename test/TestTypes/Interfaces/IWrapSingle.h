#ifndef IWRAPSINGLE_H
#define IWRAPSINGLE_H

#include "ISimple.h"

#include <memory>
#include <string>

using std::shared_ptr;

class IWrapSingle
{
public:
    virtual shared_ptr<ISimple> GetSingle() = 0;
    virtual std::string Call() = 0;
    virtual std::string CallChild() = 0;
    virtual ~IWrapSingle() {};
};

#endif