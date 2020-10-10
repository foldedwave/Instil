#ifndef WRAPSINGLE_H
#define WRAPSINGLE_H

#include "Interfaces/IWrapSingle.h"

#include <string>
#include <memory>

using std::shared_ptr;

class ISimple;

class WrapSingle : public IWrapSingle
{
private:
    shared_ptr<ISimple>_one;

public:
    WrapSingle(shared_ptr<ISimple> one);
    virtual shared_ptr<ISimple> GetSingle();
    virtual std::string Call();
    virtual std::string CallChild();
    virtual ~WrapSingle();
    const std::string Name = "WrapSingle";
};

#endif