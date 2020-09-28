#ifndef NAMEDSCOPESTRATEGY_H
#define NAMEDSCOPESTRATEGY_H

#include <tuple>
#include <string>
#include <map>
#include <memory>

#include "../TypeInfo.h"
#include "../IndicesBuilder.h"

using std::get;
using std::map;
using std::string;
using std::shared_ptr;

class NamedScopeStrategy
{
private:
    static map<string, map<string, shared_ptr<void>>> *objectMapScopes;

    template <class T, typename Tuple, int... Indices>
    static shared_ptr<T> ApplyImpl(string scopeName, const Tuple &x, IndicesType<Indices...>);

    static map<string, shared_ptr<void>>& GetScopeMap(string scopeName);

public:
    template <class T, typename Tuple>
    static shared_ptr<T> Apply(string scopeName, const Tuple &x);
};

map<string, map<string, shared_ptr<void>>> *NamedScopeStrategy::objectMapScopes =
    new map<string, map<string, shared_ptr<void>>>();

map<string, shared_ptr<void>>& NamedScopeStrategy::GetScopeMap(string scopeName)
{
    if (objectMapScopes->find(scopeName) == objectMapScopes->end())
    {
        (*objectMapScopes)[scopeName] = map<string, shared_ptr<void>>();
    }
    
    return (*objectMapScopes)[scopeName];
}

template <class T, typename Tuple, int... Indices>
shared_ptr<T> NamedScopeStrategy::ApplyImpl(string scopeName, const Tuple &x, IndicesType<Indices...>)
{
    map<string, shared_ptr<void>> & oMap = GetScopeMap(scopeName);

    auto typeName = TypeInfo<T>::name;
    if (oMap.find(typeName) == oMap.end())
    {
        auto obj = std::make_shared<T>(get<Indices>(x)...);
        oMap[typeName] = obj;
        return obj;
    }
    else
    {
        return std::static_pointer_cast<T>(oMap[typeName]);
    }
}

template <class T, typename Tuple>
shared_ptr<T> NamedScopeStrategy::Apply(string scopeName, const Tuple &x)
{
    return shared_ptr<T>(ApplyImpl<T>(scopeName, x, BuildIndices<Tuple>()));
}

#endif