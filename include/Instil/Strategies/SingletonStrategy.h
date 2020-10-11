#ifndef APPLYSINGLETON_H
#define APPLYSINGLETON_H

#include <tuple>
#include <string>
#include <map>

#include "../IndicesBuilder.h"

namespace Instil
{

    using std::get;
    using std::make_shared;
    using std::map;
    using std::shared_ptr;
    using std::string;

    class SingletonStrategy
    {
    private:
        template <typename T>
        class ObjectMap
        {
        public:
            static bool populated;
            static std::shared_ptr<T> object;
        };

    private:
        template <class T, typename Tuple, int... Indices>
        static shared_ptr<T> ApplyImpl(const Tuple &x, IndicesType<Indices...>);

    public:
        template <class T, typename Tuple>
        static shared_ptr<T> Apply(const Tuple &x);
    };

    template <class T>
    bool SingletonStrategy::ObjectMap<T>::populated = false;

    template <class T>
    std::shared_ptr<T> SingletonStrategy::ObjectMap<T>::object{};

    template <class T, typename Tuple, int... Indices>
    shared_ptr<T> SingletonStrategy::ApplyImpl(const Tuple &x, IndicesType<Indices...>)
    {
        if (ObjectMap<T>::populated == false)
        {
            ObjectMap<T>::object = make_shared<T>(get<Indices>(x)...);
            ObjectMap<T>::populated = true;
        }

        return ObjectMap<T>::object;
    }

    template <class T, typename Tuple>
    shared_ptr<T> SingletonStrategy::Apply(const Tuple &x)
    {
        return ApplyImpl<T>(x, BuildIndices<Tuple>());
    }

} // namespace Instil
#endif