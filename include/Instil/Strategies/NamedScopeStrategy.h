#ifndef NAMEDSCOPESTRATEGY_H
#define NAMEDSCOPESTRATEGY_H

#include <tuple>
#include <string>
#include <map>

#include "../TypeInfo.h"
#include "../IndicesBuilder.h"

using std::get;
using std::map;
using std::string;

class NamedScopeStrategy
{
private:
    static map<string, map<string, void *> *> *objectMapScopes;

    template <class T, typename Tuple, int... Indices>
    static T *ApplyImpl(string scopeName, const Tuple &x, IndicesType<Indices...>);

public:
    template <class T, typename Tuple>
    static T *Apply(string scopeName, const Tuple &x);
};

map<string, map<string, void *> *> *NamedScopeStrategy::objectMapScopes =
    new map<string, map<string, void *> *>();

template <class T, typename Tuple, int... Indices>
T *NamedScopeStrategy::ApplyImpl(string scopeName, const Tuple &x, IndicesType<Indices...>)
{
    map<string, void *> *oMap;

    if (objectMapScopes->find(scopeName) == objectMapScopes->end())
    {
        oMap = new map<string, void *>();
        (*objectMapScopes)[scopeName] = oMap;
    }
    else
    {
        oMap = objectMapScopes->at(scopeName);
    }

    auto typeName = TypeInfo<T>::name;
    if (oMap->find(typeName) == oMap->end())
    {
        auto obj = new T(get<Indices>(x)...);
        (*oMap)[typeName] = obj;
        return obj;
    }
    else
    {
        return (T *)(oMap->at(typeName));
    }
}

template <class T, typename Tuple>
T *NamedScopeStrategy::Apply(string scopeName, const Tuple &x)
{
    return ApplyImpl<T>(scopeName, x, BuildIndices<Tuple>());
}

#endif