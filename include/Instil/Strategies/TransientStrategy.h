#ifndef TRANSIENTSTRATEGY_H
#define TRANSIENTSTRATEGY_H

#include <tuple>
#include <string>

#include "../TypeInfo.h"
#include "../IndicesBuilder.h"

using std::get;

class TransientStrategy
{
private:
  template <class T, typename Tuple, int... Indices>
  static T *ApplyImpl(const Tuple &x, IndicesType<Indices...>);

public:
  template <class T, typename Tuple>
  static T *Apply(const Tuple &x);
};

template <class T, typename Tuple, int... Indices>
T *TransientStrategy::ApplyImpl(const Tuple &x, IndicesType<Indices...>)
{
  return new T(get<Indices>(x)...);
}

template <class T, typename Tuple>
T *TransientStrategy::Apply(const Tuple &x)
{
  return ApplyImpl<T>(x, BuildIndices<Tuple>());
}

#endif