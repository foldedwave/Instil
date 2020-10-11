#ifndef IWRAPMULTIPLEASMAP_H
#define IWRAPMULTIPLEASMAP_H

#include "ISimple.h"

#include <memory>
#include <string>
#include <map>

using std::shared_ptr;

class IWrapMultipleAsMap
{
public:
    virtual std::map<std::string, shared_ptr<ISimple>> GetAll() = 0;
    virtual std::string Call() = 0;
    virtual std::string CallChildren() = 0;
    virtual ~IWrapMultipleAsMap() {};
};

#endif