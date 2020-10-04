#ifndef BUILDER_H
#define BUILDER_H

#include <tuple>

#include "Strategies/SingletonStrategy.h"
#include "Strategies/TransientStrategy.h"
#include "Strategies/NamedScopeStrategy.h"
#include "Scope.h"

namespace Instil
{

    using std::make_tuple;
    using std::shared_ptr;
    using std::string;
    using std::tuple_cat;

    template <typename... Arguments>
    class Container;

    template <typename... Arguments>
    class Builder;

    // Specialization for when there are no arguments left for the ctor
    template <class I, class T, class TupleArgs>
    class Builder<I, T, TupleArgs>
    {
    public:
        static void Register()
        {
#ifdef STDOUT
            std::cout << "Display::Register Base Case, Completed for - " << TypeParseTraits<T>::name << std::endl;
#endif

            Container<I>::build = Builder<I, T, TupleArgs>::BuildInitial;
        }

        // Entry point when the ctor has no args
        static shared_ptr<I> BuildInitial(string scopeName)
        {
            return Build(scopeName, make_tuple<>());
        }

        // Argument tuple is complete, pass in to relevant apply function
        static shared_ptr<I> Build(string scopeName, TupleArgs args)
        {
#ifdef STDOUT
            std::cout << "Display::Out Base Case, Completed for - " << TypeParseTraits<T>::name << std::endl;
#endif
            // return make_new_from_tuple<T>(std::move(args));
            if (Container<I>::scope == Scope::Singleton)
            {
                return SingletonStrategy::Apply<T>(args);
            }
            else if (Container<I>::scope == Scope::Transient)
            {
                return TransientStrategy::Apply<T>(args);
            }
            else if (Container<I>::scope == Scope::Named)
            {
                return NamedScopeStrategy::Apply<T>(scopeName, args);
            }
            else
            {
                return nullptr;
            }
        }
    };

    // Specialization for when there are arguments left to add to the ctor
    template <class I, class T, class TupleArgs, class A, typename... Arguments>
    class Builder<I, T, TupleArgs, A, Arguments...>
    {
    public:
        static void Register()
        {
#ifdef STDOUT
            std::cout << "Display::Register Getting parameter - " << TypeParseTraits<A>::name << std::endl;
#endif
            Container<I>::build = Builder<I, T, TupleArgs, A, Arguments...>::BuildInitial;
        }

        // Entry point for building a tuple of args
        static shared_ptr<I> BuildInitial(string scopeName)
        {
            return Build(scopeName, make_tuple<>());
        }

        // Add the next argument to the tuple
        static shared_ptr<I> Build(string scopeName, TupleArgs args)
        {
#ifdef STDOUT
            std::cout << "Display::Out Getting parameter - " << TypeParseTraits<A>::name << std::endl;
#endif

            auto nextTuple = tuple_cat(args, make_tuple(Container<A>::build(scopeName)));

            return Builder<I, T, decltype(nextTuple), Arguments...>::Build(scopeName, nextTuple);
        }
    };

} // namespace Instil

#endif