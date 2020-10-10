#include "WrapMultiple.h"

#include "Interfaces/ISimple.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::shared_ptr;

WrapMultiple::WrapMultiple(std::vector<shared_ptr<ISimple>> one)
{
//     std::cout << "WrapMultiple::WrapMultiple" << std::endl;
    _one = one;
}

std::vector<shared_ptr<ISimple>> WrapMultiple::GetAll()
{
    return _one;
}

std::string WrapMultiple::Call()
{
    return "WrapMultiple::Call()";
}

std::string WrapMultiple::CallChildren()
{
    std::string retval = "";

    for (auto o : _one)
    {
        retval = retval.append(o->Call()).append("/");
    }
    return retval;
}

WrapMultiple::~WrapMultiple()
{
    // std::cout << "WrapMultiple::~WrapMultiple" << std::endl;
}