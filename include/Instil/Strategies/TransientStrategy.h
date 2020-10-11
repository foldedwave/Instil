#ifndef TRANSIENTSTRATEGY_H
#define TRANSIENTSTRATEGY_H

#include <tuple>
#include <string>

#include "../IndicesBuilder.h"

namespace Instil
{
  using std::get;
  using std::shared_ptr;

  class TransientStrategy
  {
  private:
    template <class T, typename Tuple, int... Indices>
    static shared_ptr<T> ApplyImpl(const Tuple &x, IndicesType<Indices...>);

  public:
    template <class T, typename Tuple>
    static shared_ptr<T> Apply(const Tuple &x);
  };

  template <class T, typename Tuple, int... Indices>
  shared_ptr<T> TransientStrategy::ApplyImpl(const Tuple &x, IndicesType<Indices...>)
  {
    return make_shared<T>(get<Indices>(x)...);
  }

  template <class T, typename Tuple>
  shared_ptr<T> TransientStrategy::Apply(const Tuple &x)
  {
    return ApplyImpl<T>(x, BuildIndices<Tuple>());
  }
} // namespace Instil
#endif