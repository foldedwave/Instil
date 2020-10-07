#include "WrapSingle.h"

#include "Interfaces/ISimple.h"
#include <iostream>
#include <string>

using std::shared_ptr;

WrapSingle::WrapSingle(shared_ptr<ISimple> one)
{
//     std::cout << "WrapSingle::WrapSingle" << std::endl;
    _one = one;
}

shared_ptr<ISimple>WrapSingle::GetSingle()
{
    return _one;
}

std::string WrapSingle::Call()
{
    return "WrapSingle::Call()";
}

std::string WrapSingle::CallChild()
{
    return _one->Call();
}

WrapSingle::~WrapSingle()
{
    // std::cout << "WrapSingle::~WrapSingle" << std::endl;
}