#ifndef NAMEDSCOPESTRATEGY_H
#define NAMEDSCOPESTRATEGY_H

#include <tuple>
#include <string>
#include <map>
#include <memory>

#include "../IndicesBuilder.h"

namespace Instil
{
    using std::get;
    using std::map;
    using std::shared_ptr;
    using std::string;

    class NamedScopeStrategy
    {
    private:
        template <typename T>
        class ScopedObjectMap
        {
        public:
            static std::map<string, std::shared_ptr<T>> objects;
        };

    private:
        template <class T, typename Tuple, int... Indices>
        static shared_ptr<T> ApplyImpl(string scopeName, const Tuple &x, IndicesType<Indices...>);

    public:
        template <class T, typename Tuple>
        static shared_ptr<T> Apply(string scopeName, const Tuple &x);
    };

    template <class T>
    std::map<string, std::shared_ptr<T>> NamedScopeStrategy::ScopedObjectMap<T>::objects{};

    template <class T, typename Tuple, int... Indices>
    shared_ptr<T> NamedScopeStrategy::ApplyImpl(string scopeName, const Tuple &x, IndicesType<Indices...>)
    {
        if (ScopedObjectMap<T>::objects.find(scopeName) == ScopedObjectMap<T>::objects.end())
        {
            ScopedObjectMap<T>::objects[scopeName] = std::make_shared<T>(get<Indices>(x)...);
        }

        return ScopedObjectMap<T>::objects[scopeName];
    }

    template <class T, typename Tuple>
    shared_ptr<T> NamedScopeStrategy::Apply(string scopeName, const Tuple &x)
    {
        return shared_ptr<T>(ApplyImpl<T>(scopeName, x, BuildIndices<Tuple>()));
    }

} // namespace Instil
#endif