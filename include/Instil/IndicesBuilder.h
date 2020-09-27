#ifndef INDICESBUILDER_H
#define INDICESBUILDER_H

#include <tuple>

using std::tuple_size;

template <int... Indices>
struct IndicesType
{
    typedef IndicesType<Indices..., sizeof...(Indices)> next;
};

template <int Size>
struct IndicesBuilder
{
    typedef typename IndicesBuilder<Size - 1>::type::next type;
};

template <>
struct IndicesBuilder<0>
{
    typedef IndicesType<> type;
};

template <typename Tuple>
typename IndicesBuilder<tuple_size<typename std::decay<Tuple>::type>::value>::type
BuildIndices()
{
    return {};
}

#endif