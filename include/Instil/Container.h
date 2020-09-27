#ifndef CONTAINER_H
#define CONTAINER_H

#ifdef INSTIL_STDOUT
#include <iostream>
#endif
#include <functional>
#include <tuple>

#include "TypeInfo.h"
#include "Strategies/SingletonStrategy.h"
#include "Strategies/TransientStrategy.h"
#include "Strategies/NamedScopeStrategy.h"
#include "Builder.h"
#include "Scope.h"

using std::function;
using std::string;
using std::tuple;

template <typename... Arguments>
class Container;

// Specialization for retrieving from the container
template <class I>
class Container<I>
{
public:
    static function<I *(string)> build;
    static I *Get();
    static I *Get(string scope);
    static Scope scope;
};

template <class I>
function<I *(string)> Container<I>::build;

template <class I>
I *Container<I>::Get()
{
    return build("");
}

template <class I>
I *Container<I>::Get(string scope)
{
    return build(scope);
}

template <class I>
Scope Container<I>::scope;

// Specialization for registering classes without ctor arguments
template <class I, class T>
class Container<I, T>
{
public:
    const tuple<> empty = make_tuple<>();
    static I *Create()
    {
#ifdef STDOUT
        std::cout << "Container<I, T>::Create without args - " << TypeParseTraits<I>::name << std::endl;
#endif

        I *obj = Builder<I, T, decltype(empty)>::OutInitial();

        return obj;
    }

    static void Register(Scope scope)
    {
#ifdef STDOUT
        std::cout << "Container<I, T>::Register without args - " << TypeParseTraits<I>::name << std::endl;
#endif

        Container<I>::scope = scope;
        Builder<I, T, decltype(empty)>::Register();
    }
};

// Specialization for registering classes with ctor arguments
template <class I, class T, typename... Arguments>
class Container<I, T, Arguments...>
{
public:
    const tuple<> empty = make_tuple<>();
    static I *Create()
    {
#ifdef STDOUT
        std::cout << "Container<I, T, Arguments...>::Create with args - " << TypeParseTraits<I>::name << std::endl;
#endif
        I *obj = Builder<I, T, decltype(empty), Arguments...>::OutInitial();

        return obj;
    }

    static void Register(Scope scope)
    {
#ifdef STDOUT
        std::cout << "Container<I, T, Arguments...>::Register with args - " << TypeParseTraits<I>::name << std::endl;
#endif
        Container<I>::scope = scope;
        Builder<I, T, decltype(empty), Arguments...>::Register();
    }
};
#endif