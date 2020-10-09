#ifndef BUILDER_H
#define BUILDER_H

#include <tuple>

#include "Strategies/SingletonStrategy.h"
#include "Strategies/TransientStrategy.h"
#include "Strategies/NamedScopeStrategy.h"
#include "Scope.h"

#include <tuple>
#include <utility>

using std::string;
using std::function;

#ifdef DEBUGINSTIL
#include <iostream>
#include "Unmangle.h"

#define LogVal(X)   std::cout << #X << " - " << X << std::endl;
#define Log(X)      std::cout << #X << " - " << unmangle(typeid(X).name()) << std::endl;
#define LogPack(X)  std::cout << #X << " - " << unmangle(typeid(std::declval<X>()).name()) << std::endl;
#endif

namespace Instil
{
    template <typename... Arguments>
    class Container;

    template <typename... Arguments>
    class Builder;

    // Specialization for when there are no arguments left for the ctor
    template <class T, class TupleArgs>
    class Builder<T, TupleArgs>
    {
    public:
        static function<T(Scope, string)> Register()
        {
#ifdef DEBUGINSTIL
            std::cout << "---------------------------------------------------" << std::endl;
            std::cout << "Builder<T, TupleArgs>::Register(registrationScope)" << std::endl;
            Log(T)
            Log(TupleArgs)
            std::cout << "---------------------------------------------------" << std::endl;
#endif

            return Builder<T, TupleArgs>::BuildInitial;
        }

        // Entry point when the ctor has no args
        static T BuildInitial(Scope scope, string scopeName)
        {
            return Build(scope, scopeName, std::make_tuple<>());
        }

        // Argument tuple is complete, pass in to relevant apply function
        static T Build(Scope scope, string scopeName, TupleArgs args)
        {
#ifdef DEBUGINSTIL
            std::cout << "---------------------------------------------------" << std::endl;
            std::cout << "Builder<T, TupleArgs>::Build(Scope scope, string scopeName, TupleArgs args)" << std::endl;
            Log(T)
            Log(TupleArgs)
            LogVal(scope)
            LogVal(scopeName)
            std::cout << "---------------------------------------------------" << std::endl;
#endif

            if (scope == Scope::Singleton)
            {
                 return SingletonStrategy::Apply<typename T::element_type>(args);
            }
            else if (scope == Scope::Transient)
            {
                return TransientStrategy::Apply<typename T::element_type>(args);
            }
            else if (scope == Scope::Named)
            {
                return NamedScopeStrategy::Apply<typename T::element_type>(scopeName, args);
            }
            else
            {
                return nullptr;
            }
        }
    };


    // Specialization for when there are arguments left to add to the ctor
    template <class T, class TupleArgs, class A, typename... Arguments>
    class Builder<T, TupleArgs, A, Arguments...>
    {
    public:
        static function<T(Scope, string)> Register()
        {
#ifdef DEBUGINSTIL
            std::cout << "---------------------------------------------------" << std::endl;
            std::cout << "Builder<T, TupleArgs, A, Arguments...>::Register(registrationScope)" << std::endl;
            Log(T)
            Log(TupleArgs)
            Log(A)
            std::cout << "---------------------------------------------------" << std::endl;
#endif
            return Builder<T, TupleArgs, A, Arguments...>::BuildInitial;
        }

        // Entry point for building a tuple of args
        static T BuildInitial(Scope scope, string scopeName)
        {
            return Build(scope, scopeName, std::make_tuple<>());
        }

        // Add the next argument to the tuple
        static T Build(Scope scope, string scopeName, TupleArgs args)
        {
            auto nextTuple = std::tuple_cat(args, std::make_tuple(Container<A>::Get(scopeName)));

            return Builder<T, decltype(nextTuple), Arguments...>::Build(scope, scopeName, nextTuple);
        }
    };

} // namespace Instil

#endif