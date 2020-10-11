#ifndef ITEMPLATED_H
#define ITEMPLATED_H

#include <string>

template<class T>
class ITemplated
{
public:
    T object;
    virtual std::string Call() = 0;
    virtual ~ITemplated() {};
};

#endif