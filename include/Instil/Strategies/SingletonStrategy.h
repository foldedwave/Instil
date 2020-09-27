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

class SingletonStrategy
{
private:
    static map<string, void *> *objectMap;

    template <class T, typename Tuple, int... Indices>
    static T *ApplyImpl(const Tuple &x, IndicesType<Indices...>);

public:
    template <class T, typename Tuple>
    static T *Apply(const Tuple &x);
};

map<string, void *> * SingletonStrategy::objectMap = new map<string, void *>();

template <class T, typename Tuple, int... Indices>
T *SingletonStrategy::ApplyImpl(const Tuple &x, IndicesType<Indices...>)
{
    auto typeName = TypeInfo<T>::name;
    if (objectMap->find(typeName) == objectMap->end())
    {
        auto obj = new T(get<Indices>(x)...);
        (*objectMap)[typeName] = obj;
        return obj;
    }
    else
    {
        return (T *)(objectMap->at(typeName));
    }
}

template <class T, typename Tuple>
T *SingletonStrategy::Apply(const Tuple &x)
{
    return ApplyImpl<T>(x, BuildIndices<Tuple>());
}

#endif