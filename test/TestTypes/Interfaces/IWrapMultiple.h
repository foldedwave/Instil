#ifndef IWRAPMULTIPLE_H
#define IWRAPMULTIPLE_H

#include "ISimple.h"

#include <memory>
#include <string>
#include <vector>

using std::shared_ptr;

class IWrapMultiple
{
public:
    virtual std::vector<shared_ptr<ISimple>> GetAll() = 0;
    virtual std::string Call() = 0;
    virtual std::string CallChildren() = 0;
    virtual ~IWrapMultiple() {};
};

#endif