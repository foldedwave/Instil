#ifndef CONTAINER_H
#define CONTAINER_H

#ifdef INSTIL_STDOUT
#include <iostream>
#endif
#include <functional>
#include <tuple>

#include "Strategies/SingletonStrategy.h"
#include "Strategies/TransientStrategy.h"
#include "Strategies/NamedScopeStrategy.h"
#include "Builder.h"
#include "Scope.h"

using std::string;
using std::vector;
using std::pair;
using std::tuple;
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
    // Forward declaration
    template <typename... Arguments>
    class Container;

    // Specialisation for getting multiple instances
    template <class I>
    class Container<vector<I>>
    {
    public:
        static vector<I> Get(string scope); // TODO implement scope
    };

    template <class I>
    vector<I> Container<vector<I>>::Get(string scope)
    {
        return Container<I>::GetAll();
    }

    // Main registration specialisation
    template <class I>
    class Container<I>
    {
    private:
        static vector<pair<function<I(Scope, string)>, Scope>> builders;

    public:
        static void Add(pair<function<I(Scope, string)>, Scope> builder);
        static I Get();
        static I Get(string scope);
        static vector<I> GetAll();

    public:
        const tuple<> empty = std::make_tuple<>();


        template <typename... Arguments>
        class For;

        template <class T, typename... Arguments>
        class For<T, Arguments...>
        {
        public:
            static void Register(Scope scope)
            {
#ifdef DEBUGINSTIL
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "Container<I>::For<T, Arguments...>::Register(scope)" << std::endl;
                Log(I)
                Log(T)
                LogPack(Arguments...)
                std::cout << "---------------------------------------------------" << std::endl;
#endif

                Container<I>::Add(std::make_pair(Builder<T, decltype(empty), Arguments...>::Register(), scope));
            }
        };

        template <class T>
        class For<T>
        {
        public:
            static vector<pair<function<I(string)>, Scope>> builders;

            static void Register(Scope scope)
            {
#ifdef DEBUGINSTIL
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "Container<I>::For<T>::Register(scope)" << std::endl;
                Log(I)
                Log(T)
                std::cout << "---------------------------------------------------" << std::endl;
#endif

                Container<I>::Add(std::make_pair(Builder<T, decltype(empty)>::Register(), scope));
            }
        };
    };

    template <class I>
    vector<pair<function<I(Scope, string)>, Scope>> Container<I>::builders{};

    template <class I>
    void Container<I>::Add(pair<function<I(Scope, string)>, Scope> builder)
    {
        builders.push_back(builder);
    }

    template <class I>
    I Container<I>::Get()
    {
        return builders[0].first(builders[0].second, "");
    }

    template <class I>
    I Container<I>::Get(string scope)
    {
        return builders[0].first(builders[0].second, scope);
    }

    template <class I>
    vector<I> Container<I>::GetAll()
    {
        vector<I> instances{};

        for (auto builder : builders)
        {
            auto ptr = builder.first(builders[0].second, "");

            instances.push_back(ptr);
        }

        return instances;
    }

} // namespace Instil
#endif