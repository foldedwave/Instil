#ifndef WRAPMULTIPLEASMAP_H
#define WRAPMULTIPLEASMAP_H

#include "Interfaces/IWrapMultipleAsMap.h"

#include <string>
#include <memory>
#include <map>

using std::shared_ptr;

class ISimple;

class WrapMultipleAsMap : public IWrapMultipleAsMap
{
private:
    std::map<std::string, shared_ptr<ISimple>> _one;

public:
    WrapMultipleAsMap(std::map<std::string, shared_ptr<ISimple>> one);
    virtual std::map<std::string, shared_ptr<ISimple>> GetAll();
    virtual std::string Call();
    virtual std::string CallChildren();
    virtual ~WrapMultipleAsMap();
    const std::string Name = "WrapMultipleAsMap";
};

#endif