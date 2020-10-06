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

namespace Instil
{

    using std::function;
    using std::shared_ptr;
    using std::string;
    using std::tuple;

    template <typename... Arguments>
    class Container;

    template <class I>
    class Container<std::vector<I>>
    {
        public:
            static std::vector<shared_ptr<I>> Get(string scope);    // TODO implement scope
    };

    template <class I>
    std::vector<shared_ptr<I>> Container<std::vector<I>>::Get(string scope)
    {
        return Container<I>::GetAll();
    }

    // Specialization for retrieving from the container
    template <class I>
    class Container<I>
    {
    private:
        static std::vector<function<shared_ptr<I>(string)>> builders;
    
    public:
        static void Add(function<std::shared_ptr<I>(string)> builder);
        static shared_ptr<I> Get();
        static shared_ptr<I> Get(string scope);
        static std::vector<shared_ptr<I>> GetAll();
        static Scope scope;
    };

    template <class I>
    std::vector<function<shared_ptr<I>(string)>> Container<I>::builders{};

    template <class I>
    void Container<I>::Add(function<std::shared_ptr<I>(string)> builder)
    {
        builders.push_back(builder);
    }
    
    template <class I>
    shared_ptr<I> Container<I>::Get()
    {
        return builders[0]("");
    }

    template <class I>
    shared_ptr<I> Container<I>::Get(string scope)
    {
        return builders[0](scope);
    }

    template <class I>
    std::vector<shared_ptr<I>> Container<I>::GetAll()
    {
        std::vector<shared_ptr<I>> instances{};

        for (auto builder : builders)
        {
            auto ptr = builder("");
            
            instances.push_back(ptr);
        }

        return instances;
    }

    template <class I>
    Scope Container<I>::scope;

    // Specialization for registering classes without ctor arguments
    template <class I, class T>
    class Container<I, T>
    {
    public:
        const tuple<> empty = make_tuple<>();
        static shared_ptr<I> Create()
        {
#ifdef STDOUT
            std::cout << "Container<I, T>::Create without args - " << TypeParseTraits<I>::name << std::endl;
#endif

            shared_ptr<I> obj = Builder<I, T, decltype(empty)>::OutInitial();

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
        static shared_ptr<I> Create()
        {
#ifdef STDOUT
            std::cout << "Container<I, T, Arguments...>::Create with args - " << TypeParseTraits<I>::name << std::endl;
#endif
            shared_ptr<I> obj = Builder<I, T, decltype(empty), Arguments...>::OutInitial();

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

} // namespace Instil
#endif