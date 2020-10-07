#ifndef WRAPMULTIPLE_H
#define WRAPMULTIPLE_H

#include "Interfaces/IWrapMultiple.h"

#include <string>
#include <memory>

using std::shared_ptr;

class ISimple;

class WrapMultiple : public IWrapMultiple
{
private:
    std::vector<shared_ptr<ISimple>> _one;

public:
    WrapMultiple(std::vector<shared_ptr<ISimple>> one);
    virtual std::vector<shared_ptr<ISimple>> GetAll();
    virtual std::string Call();
    virtual std::string CallChildren();
    virtual ~WrapMultiple();
};

#endif