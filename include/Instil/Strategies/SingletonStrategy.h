#ifndef APPLYSINGLETON_H
#define APPLYSINGLETON_H

#include <tuple>
#include <string>
#include <map>

#include "../TypeInfo.h"
#include "../IndicesBuilder.h"

using std::get;
using std::map;
using std::string;
using std::shared_ptr;
using std::make_shared;

class SingletonStrategy
{
private:
    static map<string, shared_ptr<void>> *objectMap;

    template <class T, typename Tuple, int... Indices>
    static shared_ptr<T> ApplyImpl(const Tuple &x, IndicesType<Indices...>);

public:
    template <class T, typename Tuple>
    static shared_ptr<T> Apply(const Tuple &x);
};

map<string, shared_ptr<void>> * SingletonStrategy::objectMap = new map<string, shared_ptr<void>>();

template <class T, typename Tuple, int... Indices>
shared_ptr<T> SingletonStrategy::ApplyImpl(const Tuple &x, IndicesType<Indices...>)
{
    auto typeName = TypeInfo<T>::name;
    if (objectMap->find(typeName) == objectMap->end())
    {
        auto obj = make_shared<T>(get<Indices>(x)...);
        (*objectMap)[typeName] = obj;
        return obj;
    }
    else
    {
        return std::static_pointer_cast<T>(objectMap->at(typeName));
    }
}

template <class T, typename Tuple>
shared_ptr<T> SingletonStrategy::Apply(const Tuple &x)
{
    return shared_ptr<T>(ApplyImpl<T>(x, BuildIndices<Tuple>()));
}

#endif