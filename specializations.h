#pragma once

#include <tuple>

namespace std
{
  template<typename T, size_t N>
  struct tuple_size<T[N]> : public std::integral_constant<size_t, N> {};
}

template <size_t I, typename T, size_t N>
T& get (T(&c)[N]) { return c[I]; }

template <size_t I, typename T, size_t N>
T get (T(&c)[N]) { return c[I]; }