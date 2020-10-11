#include "WrapMultipleAsMap.h"

#include "Interfaces/ISimple.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::shared_ptr;

WrapMultipleAsMap::WrapMultipleAsMap(std::map<std::string, shared_ptr<ISimple>> one)
{
//     std::cout << "WrapMultipleAsMap::WrapMultipleAsMap" << std::endl;
    _one = one;
}

std::map<std::string, shared_ptr<ISimple>> WrapMultipleAsMap::GetAll()
{
    return _one;
}

std::string WrapMultipleAsMap::Call()
{
    return "WrapMultipleAsMap::Call()";
}

std::string WrapMultipleAsMap::CallChildren()
{
    std::string retval = "";

    for (auto o : _one)
    {
        retval = retval.append(o.second->Call()).append("/");
    }
    return retval;
}

WrapMultipleAsMap::~WrapMultipleAsMap()
{
    // std::cout << "WrapMultipleAsMap::~WrapMultipleAsMap" << std::endl;
}