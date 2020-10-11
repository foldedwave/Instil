#ifndef CONTAINER_H
#define CONTAINER_H

#ifdef INSTIL_STDOUT
#include <iostream>
#endif
#include <functional>
#include <tuple>
#include <memory>

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
using std::shared_ptr;

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
        static vector<shared_ptr<I>> Get(string scope); // TODO implement scope
    };

    template <class I>
    vector<shared_ptr<I>> Container<vector<I>>::Get(string scope)
    {
        return Container<I>::GetAll();
    }

    // Specialisation for getting multiple instances registered with names
    template <class I>
    class Container<map<string, I>>
    {
    public:
        static map<string, shared_ptr<I>> Get(string scope);
    };

    template <class I>
    map<string, shared_ptr<I>> Container<map<string, I>>::Get(string scope)
    {
        return Container<I>::GetAllAsMap();
    }

    // Main registration specialisation
    template <class I>
    class Container<I>
    {
    private:
        struct BuilderInfo
        {
        public:
            BuilderInfo(string name, Scope scope, function<shared_ptr<I>(Scope, string)> builder) 
                : name(name), scope(scope), builder(builder){}

            string name = "";
            Scope scope = Scope::Undefined;
            function<shared_ptr<I>(Scope, string)> builder;
        };
        
    private:
        static vector<BuilderInfo> builders;
        static bool areAllNamed;

    private:
        static void Add(BuilderInfo builder);

    public:
        static shared_ptr<I> Get(string scopeName = "");
        static shared_ptr<I> GetNamed(string name, string scopeName = "");
        static vector<shared_ptr<I>> GetAll(string scopeName = "");
        static map<string, shared_ptr<I>> GetAllAsMap(string scopeName = "");

    public:
        template <typename... Arguments>
        class For;

        template <class T, typename... Arguments>
        class For<T, Arguments...>
        {
        public:
            static void Register(Scope scope, string name = "")
            {
#ifdef DEBUGINSTIL
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "Container<I>::For<T, Arguments...>::Register(scope)" << std::endl;
                Log(I)
                Log(T)
                LogPack(Arguments...)
                std::cout << "---------------------------------------------------" << std::endl;
#endif

                Container<I>::Add(Container<I>::BuilderInfo(name, scope, Builder<T, std::tuple<>, Arguments...>::Register()));    // TODO supply name of builder
            }
        };

        template <class T>
        class For<T>
        {
        private:
            static vector<pair<function<shared_ptr<I>(Scope, string)>, Scope>> builders;

        public:
            static void Register(Scope scope, string name = "")
            {
#ifdef DEBUGINSTIL
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "Container<I>::For<T>::Register(scope)" << std::endl;
                Log(I)
                Log(T)
                std::cout << "---------------------------------------------------" << std::endl;
#endif

                Container<I>::Add(Container<I>::BuilderInfo(name, scope, Builder<T, std::tuple<>>::Register()));  // TODO name of builder
            }
        };
    };

    template <class I>
    vector<typename Container<I>::BuilderInfo> Container<I>::builders{};

    template <class I>
    bool Container<I>::areAllNamed = true;

    template <class I> 
    void Container<I>::Add(BuilderInfo builder)
    {
        if(builder.name == "")
        {
            areAllNamed = false;
        }
        builders.push_back(builder);
    }

    template <class I>
    shared_ptr<I> Container<I>::Get(string scopeName)
    {
        return builders[0].builder(builders[0].scope, scopeName);
    }

    template <class I>
    shared_ptr<I> Container<I>::GetNamed(string name, string scopeName)
    {
        return builders[0].builder(builders[0].scope, scopeName);
    }

    template <class I>
    vector<shared_ptr<I>> Container<I>::GetAll(string scopeName)
    {
        vector<shared_ptr<I>> instances{};

        for (auto builderInfo : builders)
        {
            auto ptr = builderInfo.builder(builderInfo.scope, scopeName);  // TODO name of scope

            instances.push_back(ptr);
        }

        return instances;
    }

    template <class I>
    map<string, shared_ptr<I>> Container<I>::GetAllAsMap(string scopeName)
    {
        map<string, shared_ptr<I>> instances{};

        for (auto builderInfo : builders)
        {
            auto ptr = builderInfo.builder(builderInfo.scope, scopeName);  // TODO name of scope

            instances[builderInfo.name] = ptr;
        }

        return instances;
    }

} // namespace Instil
#endif